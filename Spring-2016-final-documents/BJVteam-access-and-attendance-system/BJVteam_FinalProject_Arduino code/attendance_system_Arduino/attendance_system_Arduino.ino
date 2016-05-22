#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String cardRead = "";
int count =0;
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0F, 0x4B, 0xD4
};
IPAddress ip(192, 168, 1, 183);
IPAddress server(192, 168, 1, 155);
EthernetClient client;
String dataTosend="";
int classHour=13;
int classMinutes=48;
boolean flaaag=false;

void setup(){
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  
 pinMode(6,OUTPUT); //led test
 pinMode(5,INPUT); // data 0 
 //pinMode(7,OUTPUT);
 pinMode(8,INPUT); // data 1
  //digitalWrite(7,HIGH);
   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 
  }
  
   Serial.println("connecting...");
  if (client.connect(server, 23)) {
    Serial.println("connected");
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
  delay(3000); // to let the card reader the time to initiate
  Serial.println("system initiated" );
  DateTime now = rtc.now();
}

void loop(){
  
   int data0 = digitalRead(5);
   int data1 = digitalRead(8);
   int b = -1;
   
   if(data0==0 || data1==0){
     
     if(data0==0){
       b=0; 
     } else if(data1==0){
       b=1; 
     }

     cardRead = cardRead + b;
     count = count +1;
   }
 
    
    if (cardRead.length()==35){
        DateTime now = rtc.now();    
        dataTosend="a "+cardRead+" "+now.year()+"/"+now.month()+"/"+now.day()+" "+daysOfTheWeek[now.dayOfTheWeek()]+" "+now.hour()+":"+now.minute()+"f";
        Serial.println(dataTosend);
        senddata(dataTosend);
        // put the send comand to the server here!!!!!!
        cardRead = "";
        Serial.println("writed in the file!");
        //senddata("s");
  }
 
  }

  
  
  
  


void senddata(String s){
client.print(s);

}


boolean getDATE(){
   //Serial.println("entrou na funcao");
DateTime now = rtc.now();
 //Serial.println("passou do now");
  if(now.hour()==classHour && now.minute()==(classMinutes+10)){
   //Serial.println("entrou no dia");
    if(now.dayOfTheWeek()==1 ||now.dayOfTheWeek()==3){
    //Serial.println("entrou na hora");
      return 1;
    Serial.println("email sended");

    //Serial.println("passou do delay");
    }
  }
  else{return 0;}
}
