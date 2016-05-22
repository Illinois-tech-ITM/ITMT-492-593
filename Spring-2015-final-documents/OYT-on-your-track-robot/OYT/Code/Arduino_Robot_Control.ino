// ----------------------------------------------------
// Illinois Institute of Technology
// ITMT 492 - Embedded Systems
//
// Students: Igor de Sousa Dantas,
//           Leonardo Pavanatto Soares,
//           Nicolas Ribeiro Vieira,
//           Pedro Henrique de Brito Souza,
//           Rodrigo Moreno Garcia.
//
// Instructors: Dr Daniel Tomal,
//         Jeremy Hajek.
//
// Project: O.Y.T. - The Track Guided Robot
// File: Arduino Robot Control
// Last Modified: May 5, 2015
// ----------------------------------------------------

// ----------------------------------------------------
//  Constants
// ----------------------------------------------------
 
//Define UHT Sensoring - Libraries
#include "DHT.h"
//DHT PIN
#define DHTPIN 12
//DHT Type
#define DHTTYPE DHT22
//Set  up the Library
DHT dht(DHTPIN, DHTTYPE);

// Define the Ultrasonic Pin
  const int pingPin=11;
  
//Define motors
 const int rMotor = 9;
 const int lMotor = 6;
// Define sensors
   const int sensors[8]={A7 , A6, A5, A4, A3 , A2 , A1 , A0};
// Define leds
 const int led[4]={2 , 3 , 4 , 5};

// Define the threshold to determine if its black or white
 const int threshold = 45;
 int rSpeed = 0;
 int lSpeed = 0;


 int time=0;
 boolean stuckflag=false;
 
 byte humidity, temperatureC, temperatureF;
 
 const int base = 28;
 const float samples = 10;

 int state = 0;
 
// ----------------------------------------------------
// Code
// ----------------------------------------------------
 void setup()
 {
    Serial.begin(9600);
    pinMode(rMotor, OUTPUT);
    pinMode(lMotor, OUTPUT);
    for(int i = 0; i < 4; i++)
        pinMode(led[i], OUTPUT);
    for(int i = 0; i < 8; i++)
        pinMode(sensors[i], INPUT);
    dht.begin();
}
int color(int value)
{
    float avg = 0;
    for(int i = 0; i < samples; i++)
        avg = avg + analogRead(value);
    if((float)(avg/samples) <= threshold) return 1;  // its black
    else return 0;                                   // its white
}
void line()
{
    rSpeed = base;
    lSpeed = base*1.2;
}
void left(int value){
    rSpeed = value;
}
void right(int value){
    lSpeed = value*1.2;
}
boolean isBlack(int num)
{
    if(color(sensors[num]) == 1) return true;
    else return false;
}

void running()
{
    int ultrasonicRange=checkRangeCM();
    
    if(ultrasonicRange<10){left(0);  right(0);}
    else if(not ((isBlack(0)) || (isBlack(1)) || (isBlack(2)) || (isBlack(3)) || (isBlack(4)) || (isBlack(5)) || (isBlack(6)) || (isBlack(7))))
    {
      int current_time=(millis()/1000);
      if(!stuckflag){ //uses flag logic to lock the robot after 2 seconds of only white readings.
          time=(millis()/1000);
          stuckflag=true;
      }
      else if(current_time>(time+2)){
          state=2;
          stuckflag=false;
          return;
      }
    }
    else if((isBlack(0)) && (isBlack(7)))
    {
        state = 0;
        stuckflag=false;
        analogWrite(lMotor, 0);
        analogWrite(rMotor, 0);
        uhtReadings();
        return;
    }
    else
    {
        stuckflag=false;
          
        // Line
        if((isBlack(3)) && (isBlack(4))) line();
        else if(isBlack(3)) {left(27); right(20);}
        else if(isBlack(4)) {left(20); right(27);}

        // Left
        if(isBlack(6)) {left(0); right(50); }
        else if(isBlack(5)) {left(0); right(40);}
        
        // Right
        if(isBlack(1)) {left(50); right(0);}
        else if(isBlack(2)) {left(40); right(0);}
    }
    
    analogWrite(lMotor, lSpeed);
    analogWrite(rMotor, rSpeed);
}

void reading()
{
    int aux;
    if(Serial.available() > 0)
    {
        aux = (Serial.read() - 48);
        if((aux == 1) || (aux == 0)) state = aux;
        digitalWrite(led[3], HIGH);
    }
}

void showState()
{  
    for(int i = 0; i < 3; i++)
    {
        if(i != state) digitalWrite(led[i], LOW);
        else digitalWrite(led[i], HIGH);
    }
}

int checkRangeCM()
{
    long duration;
    //Define the ping output
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    //Read the ping response from the same pin
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);  
    return duration/29/2;
}

void uhtReadings()
{
  
  //Humidity Reading
  humidity = dht.readHumidity();
  // Temperature Reading (CELSIUS)
  temperatureC = dht.readTemperature();  
  // Temperature Reading (Fahrenheit)
  //temperatureF = dht.readTemperature(true);
  //Send the Data through the Xbee
  sendSensorData();
  //Sets the flag to true, so the robot goes to the next checkpoint
  delay(300);
}

void sendSensorData()
{
  Serial.println(humidity, DEC);
  delay(1000);
  Serial.println(temperatureC, DEC);
  delay(1000);
}

void loop()
{
   if(state == 1) 
      running();
    else
    {
      analogWrite(lMotor, 0);
      analogWrite(rMotor, 0);
    }
    reading();
    showState();
}
