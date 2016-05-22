#include <Adafruit_TCS34725.h>
#include <LiquidCrystal.h>
#include <Wire.h>

// Initialise sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

//Initialise lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int button = 7;    // pin where the button is connected to
boolean state = 0;       // Initial button push state
boolean newState = 0;    // State of the button after being pushed/released
boolean hexEnable = 0;   // Toggle between RGB and Hex

void setup() {
  Serial.begin(9600);

  pinMode(button, INPUT);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  lcd.begin(16,2);
} // end void setup

void loop() {

  state = (digitalRead(button));
  delay(75);
  if (state == 0 && newState == 0){
    hexEnable = 0;
    newState = state;
    }
  else if(state == 1 && newState == 0){
      hexEnable = 1;
      newState = state;
  }
  else if(state == 0 && newState == 1){
    hexEnable = 1;
  }
  else if(state == 1 && newState == 1){
    hexEnable = 0;
    newState = 0;
  }
  
  uint16_t clearcol, red, green, blue;
//  tcs.setInterrupt(false);
  delay(100);
  tcs.getRawData(&red, &green, &blue, &clearcol);
//  tcs.setInterrupt(true);
    
 uint32_t sum = clearcol;
 float r, g, b;
 r = red; r /= sum; r *=255;
 g = green; g /=sum; g*=255;
 b = blue; b /=sum; b*= 255;

lcd.setCursor(0,0);
lcd.print("RED");
lcd.setCursor(4,0);
lcd.print("GREEN");
lcd.setCursor(10,0);
lcd.print("BLUE");

if (hexEnable == 0)
{
RGB(r,g,b);
}
else
{
hexMode(r,g,b);
}
} // end of void loop

void RGB(float r, float g, float b)
{
  lcd.setCursor(15,0);
  lcd.print(" ");
// Control statement for RED
if (r < 100) {
  lcd.setCursor(1,1);
  lcd.print((int)r);
  lcd.setCursor(0,1);
  lcd.print(" ");
}
else {
  lcd.setCursor(0,1);
  lcd.print((int) r);
}

// Control statement for GREEN
if (g < 100) {
  lcd.setCursor(6,1);
  lcd.print((int)g);
  lcd.setCursor(5,1);
  lcd.print(" ");
}
else {
  lcd.setCursor(5,1);
  lcd.print((int) g);
}

// Control statement for BLUE
if (b < 100) {
  lcd.setCursor(12,1);
  lcd.print((int)b);
  lcd.setCursor(11,1);
  lcd.print(" ");
}
else {
  lcd.setCursor(11,1);
  lcd.print((int) b);
}
}

void hexMode(float r, float g, float b)
{
lcd.setCursor(15,0);
lcd.print("X");
lcd.setCursor(0,1);
lcd.print(" ");
lcd.setCursor(1,1);
lcd.print((int)r, HEX);
lcd.setCursor(5,1);
lcd.print(" ");
lcd.setCursor(6,1); 
lcd.print((int)g, HEX);
lcd.setCursor(11,1);
lcd.print(" ");
lcd.setCursor(12,1); 
lcd.print((int)b, HEX); 
}
