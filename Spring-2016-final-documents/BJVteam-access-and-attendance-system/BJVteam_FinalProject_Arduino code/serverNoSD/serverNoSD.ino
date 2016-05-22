
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Ethernet.h>
#define time 1000


//mac 
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0F, 0x47, 0x79
};


boolean fl=false;
  String Log="";
IPAddress ip(192,168,1, 155);
File myFile;
String stri ="";

String RECORDS="01100111001100000101111010100100011-PereiraPinto/BrunoAugusto@10100111001100000101000000011110000-Saldivar/Joseph@00100111001100000110001101001110010-Zivkovic/Vladimir@00100111001100000101011001111100011-Siron/Craig@";
String AtendanceLOG="";
String TEACHER="11100111001100000101111010100100100"; //joao id


// telnet defaults to port 23
EthernetServer server(23);
//EthernetClient clientPush(80);
boolean alreadyConnected = false; // whether or not the client was connected previously

//email part
byte server2[] = { 200, 147, 99, 132 };; // io do servidor do AOL
EthernetClient client2;


void setup() {
  // initialize the ethernet device
  Ethernet.begin(mac, ip);
  // start listening for clients
  server.begin();
  //pinMode(53,OUTPUT);
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  delay(9000);
}  

void loop() {
  // wait for a new client:
  EthernetClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clead out the input buffer:
      //client.flush();    
      Serial.println("We have a new client");
      
      alreadyConnected = true;
    } 

    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client.read();
        stri= stri+thisChar;
    }
    //read until the final of the string
    if(stri.endsWith("f")){
            //seting a String to get the id
            String idreciv="";
            for(int n=2;n<37;n++){
            idreciv=idreciv+stri.charAt(n);
            
            }
      Serial.println(idreciv);
      
        
      //check for attendance system 
      if(stri.startsWith("a")){
        // open the file and look for the name of the student
       Serial.println("entrou no atendence");
       int indexBeg= RECORDS.indexOf(idreciv);
       String Name="";
       if(indexBeg!=-1){
       indexBeg=indexBeg+36;
       int indexEnd=RECORDS.indexOf("@",indexBeg);
       for(indexBeg;indexBeg<indexEnd;indexBeg++){
       
       Name=Name+RECORDS.charAt(indexBeg);
       }
     }
     //in the case of the name is not in the record save the id information
     else if(idreciv.equals(TEACHER)){
     //mandar o email
           Log=AtendanceLOG;
      //code to send email 
                 fl=true;
               stri="";
     
     }
     else if(indexBeg==-1){
         Name=idreciv;
       }
       
        String date="";
        for(int i=37;i<stri.indexOf("f");i++){
        date=date+stri.charAt(i);
        }
        AtendanceLOG+=Name+" "+date+"\n";
        stri="";
        
      }
      //check for door lock System 
      else if (stri.startsWith("d")){
            
       
            if(RECORDS.indexOf(idreciv)!=-1){
             Serial.println("cardRead is: "+idreciv);
             Serial.println("access granted");
             server.write(2); 
             stri="";
            }else if(idreciv.length()==35){
             
            Serial.println("cardRead is: "+idreciv);
            Serial.println("access negated");
            server.write(1);
            stri="";
            
            }
      }

    }
    else if(stri.length()==65){
      Serial.println("reading error");
    }
  
  }
  
  if(fl==true){
  envia(Log);
  Log="";
  fl=false;
  
  }
  
  
  
  
}



void envia(String ddd)
{
  
Serial.println(ddd);

delay(time);
Serial.println("conecting...");
boolean fla=client2.connect(server2, 587);
Serial.println(fla);
if (fla) 
{
  
Serial.println("conected!");
Serial.println("sending email...");
Serial.println();
client2.println("EHLO localhost");
recebe();
delay(time);
client2.println("AUTH LOGIN");
recebe();
delay(time);
client2.println("YXJkdWlub2lpdDJAYm9sLmNvbS5icg=="); //  login in 64 base : http://base64-encoder-online.waraxe.us/
recebe();
delay(time);
client2.println("SU5PdGVzdElOTw=="); // Senha in 64 base : http://base64-encoder-online.waraxe.us/
recebe();
delay(time);
client2.println("mail from: <arduinoiit2@bol.com.br>"); //sender
recebe();
delay(time);
client2.println("rcpt to: <bpereira@hawk.iit.edu>"); // reciver
recebe();
delay(time);
client2.println("data");
recebe();
delay(time);
client2.println("Subject: Attendance Log"); 
recebe();
delay(time);
client2.println(ddd); // scope of the email
recebe();
delay(time);
client2.println("."); // end of email.
recebe();
delay(time);
client2.println();
recebe();
delay(time);
Serial.println("email sended!");
delay(time);
if (client2.connected()) // Desconect.
{
Serial.println();
Serial.println("desconecting...");
client2.stop();
Serial.println();
Serial.println();
}



}
else
{
Serial.println("connection failed");
}

}

void recebe()
{

while (client2.available())
{
char c = client2.read();
Serial.print(c);
}
}

