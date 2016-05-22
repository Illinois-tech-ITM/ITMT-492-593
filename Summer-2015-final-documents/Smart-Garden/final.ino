// Final Project
// Intelligent Home Garden

// Author: Igor Ramon Alves Machado
// Start date: July 13, 2015
// Last version: July 21, 2015

//------------------- Plotly informations
// email:     final.project.iit@gmail.com
// User name: itmt495_homegarden
// Password:  itmt495#homegarden
//---------------------------------------

#include <SPI.h>
#include <Wire.h>
#include <SHT1x.h>
#include <rgb_lcd.h>

#include "DHT.h"
#include "RTClib.h"
#include "TimerOne.h"

// Actuators
#define water_pump 8
#define light 9

// Soil Sensor
#define dataPin 10
#define clockPin 11

// Light sensor
#define light_sensor A0

// Air Sensor
#define DHTPIN 13
#define DHTTYPE DHT22

// thresholds
#define light_threshold 600
#define watering_threshold 90

int turn = 0;

unsigned long time;

boolean pump_ON = false;
boolean light_ON = false; 
boolean watering_plant = false;

float soil_h;
float soil_c;
float soil_f;

float air_h;
float air_c;
float air_f;

rgb_lcd lcd;
RTC_DS1307 RTC;
DHT dht(DHTPIN, DHTTYPE);
SHT1x sht1x(dataPin, clockPin);

void date(DateTime now) {
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');  
  Serial.print(now.day(), DEC);
  Serial.print(' ');  
  Serial.print(now.hour(), DEC);
  Serial.print(':');  
  Serial.print(now.minute(), DEC);
  Serial.print(':');  
  Serial.println(now.second(), DEC);
  Serial.println();
}

void sensor_data(char *type, float humidity, float celsius, float fahrenheit) {
  Serial.print(type);  
  Serial.print(" humidity: ");  
  Serial.print(humidity);
  Serial.print(" %\t");  
  Serial.print(type);  
  Serial.print(" temperature: ");  
  Serial.print(celsius);
  Serial.print(" *C ");
  Serial.print(fahrenheit);
  Serial.println(" *F\t");
}

void check_light() {
  int lightReading = analogRead(light_sensor);
  
  Serial.print("Light: ");
  Serial.println(lightReading);
  
  if((light_ON == false) && (lightReading < light_threshold)) {
    Serial.println("Light ON ");
    digitalWrite(light, LOW);
    light_ON = true;    
  }
  
  else if((light_ON == true) && (lightReading > light_threshold)) {
    Serial.println("Light OFF ");
    digitalWrite(light, HIGH);
    light_ON = false;    
  }
}

void lcd_display() {
  if(turn == 4)
    turn = 0;
    
  lcd.clear();
  
  if(turn == 0) {
    lcd.setCursor(0,0);
    lcd.setPWM(REG_BLUE, 12);
    lcd.print("Soil Humidity: ");
    
    lcd.setCursor(0,1);
    lcd.print(soil_h);
    lcd.print("%");
  }
  
  if(turn == 1) {
    lcd.setCursor(0,0);
    lcd.setPWM(REG_BLUE, 12);
    lcd.print("Air Humidity: ");
    
    lcd.setCursor(0,1);
    lcd.print(air_h);
    lcd.print("%");
  }
  
  if(turn == 2) {
    lcd.setCursor(0,0);
    lcd.setPWM(REG_BLUE, 12);
    lcd.print("Soil Temperature: ");
    
    lcd.setCursor(0,1);
    lcd.print(soil_c);
    lcd.print("*C");
    
    lcd.print("/");
    lcd.print(soil_f);
    lcd.print("*F");
  }
  
  if(turn == 3) {
    lcd.setCursor(0,0);
    lcd.setPWM(REG_BLUE, 12);
    lcd.print("Air Temperature: ");
    
    lcd.setCursor(0,1);
    lcd.print(air_c);
    lcd.print("*C");
    
    lcd.print("/");
    lcd.print(air_f);
    lcd.print("*F");
  }
  
  turn++;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up");
  
  dht.begin();
  RTC.begin();
  Wire.begin();
  lcd.begin(16,2);
  
  pinMode(light, OUTPUT);
  pinMode(water_pump, OUTPUT);
  
  // Make sure the light and the water_pump is off. Light is off when HIGH
  digitalWrite(light, HIGH);
  digitalWrite(water_pump, LOW);
  
  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  Serial.println("RTC is running!");
}

void loop() {
  time = millis();  
  DateTime now = RTC.now();
  
  Serial.println("\nNew Cicle");
  date(now);
  
  // Read soil humidity
  soil_h = sht1x.readHumidity();  
  // Read soil temperature as Celsius
  soil_c = sht1x.readTemperatureC();  
  // Read soil temperature as Fahrenheit
  soil_f = sht1x.readTemperatureF();
      
  // Read air humidity
  air_h = dht.readHumidity();  
  // Read air temperature as Celsius (the default)
  air_c = dht.readTemperature();  
  // Read air temperature as Fahrenheit (isFahrenheit = true)
  air_f = dht.readTemperature(true);  
    
  if(isnan(air_h) || isnan(air_c) || isnan(air_f)) {
    Serial.println("\nFailed to read from DHT sensor!");
  }
    
  else {
    sensor_data("Air", air_h, air_c, air_f);    
  }
  
  if(soil_h > 0) {    
    sensor_data("Soil", soil_h, soil_c, soil_f);
    
    lcd.setCursor(1,0);
    lcd.setPWM(REG_BLUE, 12);
    lcd.print("Soil Humidity: ");
    
    lcd_display();
    
    if((now.hour() > 6) && (now.hour() < 21)) {
      check_light();
      
      if((soil_h < watering_threshold) && pump_ON == false) {
        Serial.println(" Pump ON ");
        pump_ON = true;
                 
        digitalWrite(water_pump, HIGH);
      }
      
      else if((soil_h > watering_threshold) && pump_ON == true) {
        Serial.println(" Pump OFF ");
        pump_ON = false;
        
        digitalWrite(water_pump, LOW); 
      }
    }
  }
  
  else
    Serial.println("Failed to read from soil sensor!");
    
  //delay of 5 seconds, not afected by the timer1 interrupt
  while(time + 5000 > millis());
}
