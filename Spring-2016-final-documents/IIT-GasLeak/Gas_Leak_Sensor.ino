#include <SPI.h>
#include <WiFi.h>
#include <SD.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x46, 0x77};

// Enter the IP address for Arduino, as mentioned we will use 192.168.0.16
// Be careful to use , insetead of . when you enter the address here
IPAddress ip(192, 168, 1, 22);
EthernetServer server(80);
String ID = "";
String data = "";

/*
char ssid[] = "IIT-Console";      // your network SSID (name)
//char pass[] = "326125ad0d8e";   // your network password

int status = WL_IDLE_STATUS;

WiFiServer server(80);

char user[] = "root";
char password[] = "root";
*/

void setup() {
  Serial.begin(9600);

  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  /*
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present");
      // don't continue:
      while (true);
    }

    // attempt to connect to Wifi network:
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
      status = WiFi.begin(ssid/*, pass*/);

  // wait 10 seconds for connection:
  delay(10000);

}
server.begin();
// you're connected now, so print out the status:
printWifiStatus();

}


void loop() {
  //Serial.println("Before sending Web Page 1...");

  readFrame();
  displayWeb();

  ID = "";
  data = "";

  //Upload data after calling the funciton above.

}

void readFrame() {
  Serial.print("serial available: ");
  Serial.println(Serial.available());
  if (Serial.available() >= 23)
  {
    //0  12  92  //0  7D  33  A2  0  40  C6  75//  4E  EE // 99  1  1  0  0  8  3  FF  5C

    if (Serial.read() == 0x7E) {

      //Serial.print("length1: ");
      //Serial.print(Serial.read(), HEX);
      Serial.read();

      //Serial.print(" length2: ");
      //Serial.print(Serial.read(), HEX);
      //Serial.println();
      Serial.read();

      //Serial.print("Frametype: ");
      //Serial.print(Serial.read(), HEX);
      //Serial.println();
      //Serial.read();
      Serial.read();

      Serial.print("64bit address: ");
      for (int i = 0; i < 8; i++) {
        ID += Serial.read();

        //        Serial.print(Serial.read());
        //        Serial.print("  ");
      }
      Serial.println(ID);
      Serial.println();

      //Serial.print("Network address : ");
      //Serial.print(Serial.read(), HEX);
      //Serial.print(Serial.read(), HEX);
      //Serial.println();
      Serial.read();
      Serial.read();

      //Serial.print("Recive options: ");
      //Serial.print(Serial.read(), HEX);
      //Serial.println();
      Serial.read();

      //Serial.print("Digital MASK: ");
      //Serial.print(Serial.read(), HEX);
      //Serial.print(Serial.read(), HEX);
      //Serial.println();
      Serial.read();
      Serial.read();

      //Serial.print("Analog MASK: ");
      //Serial.print(Serial.read(), HEX);
      //Serial.println();
      Serial.read();

      //      Serial.print("Digital data: ");
      //      Serial.print(Serial.read(), HEX);
      //      Serial.print(Serial.read(), HEX);
      //      Serial.println();
      Serial.read();
      Serial.read();
      //String data;


      Serial.print("Analog data: ");
      data += Serial.read();
      data += Serial.read();
      //Serial.print(Serial.read(), DEC);
      //Serial.print(Serial.read(), DEC);
      Serial.print(data);
      Serial.println();

      //      Serial.print("Checksum: ");
      //      Serial.print(Serial.read(), HEX);
      //      Serial.println();
      Serial.read();
      Serial.println("------------------------new frame-----------------------");

    }
  }
}

void displayWeb() {
  if (ID != "" && data != "") {
    //upload data
    //WiFiClient client = server.available();
    EthernetClient client = server.available();
    if (client) {
      Serial.println("new client");
      // an http request ends with a blank line
      boolean currentLineIsBlank = true;
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.write(c);
          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the http request has ended,
          // so you can send a reply
          if (c == '\n' && currentLineIsBlank) {

            Serial.println("--> connection ok\n");

            client.print("GET /test3.php?data="); // This
            client.println(data); // And this is what we did in the testing section above. We are making a GET request just like we would from our browser but now with live data from the sensor
            client.println(" HTTP/1.1"); // Part of the GET request
            client.println("Host: localhost:8888");
            //client.println(server);
            client.println("Connection: close"); // Part of the GET request telling the server that we are over transmitting the message
            client.println(); // Empty line
            client.println(); // Empty line
            //client.stop();    // Closing connection to server
            Serial.println("--> finished transmission\n");
            Serial.println("Before sending Web Page...");
            delay(100);



            client.println("********IIT Gas leak detector********");
            client.println("\n");
            client.print("Gas Sensor n: ");
            client.println(ID);
            client.print("Gas amount: ");
            client.println(data);
            client.println("\n");
            client.println("No gas leak in the building!");
            client.println("*************************************");

            break;
          }
          if (c == '\n') {
            // you're starting a new line
            currentLineIsBlank = true;
          }
          else if (c != '\r') {
            // you've gotten a character on the current line
            currentLineIsBlank = false;
          }
        }
      }
      // give the web browser time to receive the data
      delay(1);

      // close the connection:
      client.stop();
      Serial.println("client disonnected");
    }
  }
  else {
    //error
  }
}

/*
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
*/

