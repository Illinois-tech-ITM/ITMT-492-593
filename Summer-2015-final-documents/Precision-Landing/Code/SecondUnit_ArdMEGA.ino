#include <avr/io.h>
#include <avr/interrupt.h>
unsigned long time0 = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;

long updateTime = -99;

boolean update0 = true;
boolean update1 = true;
boolean update2 = true;
boolean update3 = true;

unsigned long front = 0;
unsigned long right = 0;
unsigned long back = 0;
unsigned long left = 0;

unsigned long thrFB = 250;
unsigned long thrRL = 500;

void setup() {
  cli();
  DDRB = B11110000; 
  Serial.begin(9600);
    EICRA = 0x00;
    EIMSK = 0x00;
    
    EICRA |= (1 << ISC00);    // set INT0 to trigger on RISING logic change
    EICRA |= (1 << ISC01);    // set INT0 to trigger on RISING logic change
    EIMSK |= (1 << INT0);     // Turns on INT0 (PORT 21 on Arduino MEGA 2560)
    
    
    EICRA |= (1 << ISC10);    // set INT1 to trigger on RISING logic change
    EICRA |= (1 << ISC11);    // set INT1 to trigger on RISING logic change
    EIMSK |= (1 << INT1);     // Turns on INT1 (PORT 20 on Arduino MEGA 2560)
    
    
    EICRA |= (1 << ISC20);    // set INT2 to trigger on RISING logic change
    EICRA |= (1 << ISC21);    // set INT2 to trigger on RISING logic change
    EIMSK |= (1 << INT2);     // Turns on INT2 (PORT 19 on Arduino MEGA 2560)
    
    EICRA |= (1 << ISC30);    // set INT3 to trigger on RISING logic change
    EICRA |= (1 << ISC31);    // set INT3 to trigger on RISING logic change
    EIMSK |= (1 << INT3);     // Turns on INT3  (PORT 18 on Arduino MEGA 2560)
    
    sei();
    //INT4 -> PORT2
    //INT5 -> PORT3
}

void loop() {
  if((updateTime + 1000) < millis()){// Wait 1000ms to allow a new time value within ISRs
    updateTime = millis();
    update0 = update1 = update2 = update3 = true;
    led();
    myPrint();
  }
  //Notice that the loop method is still running and can be used to control the drone without affecting the ISR. (noInterrupts() and interrupts() must be used in this case!)  
}

//One interrupt for each microphone
ISR (INT0_vect)
{
  if(update0) time0 = micros(); //Capture only the first rising on signal
  update0 = false;
}

ISR (INT1_vect)
{
  if(update1) time1 = micros(); //Capture only the first rising on signal
  update1 = false;
}

ISR (INT2_vect)
{
  if(update2) time2 = micros(); //Capture only the first rising on signal
  update2 = false;
}

ISR (INT3_vect)
{
  if(update3) time3 = micros(); //Capture only the first rising on signal
  update3 = false;
}

void myPrint(){//Check time values on Serial monitor
  Serial.print("Time 0: ");
  Serial.println(time0);
  Serial.print("Time 1: ");
  Serial.println(time1);
  Serial.print("Time 2: ");
  Serial.println(time2);
  Serial.print("Time 3: ");
  Serial.println(time3);
  Serial.println();
}

void led(){//One microphone for each side
  front = time0;    
  right = time3;
  back = time2;
  left = time1;
  
  Serial.print("ABS FB: ");
  Serial.println((max(front, back) - min(front, back)));
  Serial.print("ABS RL: ");
  Serial.println((max(right, left) - min(right, left)));
  
  if((max(front, back) - min(front, back)) < thrFB && (max(right, left) - min(right, left)) < thrRL){
    Serial.println("MIDDLE");
    PORTB = B11110000;//Turn on all LEDs (Digital PORTS 10, 11, 12 and 13)
  } 
  else{
    if(front < back && front < left && front < right){ 
      Serial.println("FRONT");
      PORTB = B00110000; //Turn on LEDs (Digital PORTS 10 and 11)
    }
    if(back < front && back < right && back < left){
      Serial.println("BACK");
      PORTB = B11000000;//Turn on LEDs (Digital PORTS 12 and 13)
    } 
    if(right < left && right < front && right < back){
      Serial.println("RIGHT");
      PORTB = B01010000;//Turn on LEDs (Digital PORTS 10 and 12)
    }
    if(left < right && left < front && left < back){
      Serial.println("LEFT");
      PORTB = B10100000;//Turn on LEDs (Digital PORTS 11 and 13)
    } 
  }
}

void led2(){//Two microphones for each side (not used in our approach, but it works as well)
  front = time0 + time3;    
  right = time2 + time3;
  back = time2 + time1;
  left = time0 + time1;

  if((max(front, back) - min(front, back)) < thrFB && (max(right, left) - min(right, left)) < thrRL){
    Serial.println("MIDDLE");
    PORTB = B11110000;
  } 
  else{
    if(front < back && front < left && front < right){ 
      Serial.println("FRONT");
      PORTB = B00110000;
    }
    if(back < front && back < right && back < left){
      Serial.println("BACK");
      PORTB = B11000000;
    } 
    if(right < left && right < front && right < back){
      Serial.println("RIGHT");
      PORTB = B01010000;
    }
    if(left < right && left < front && left < back){
      Serial.println("LEFT");
      PORTB = B10100000;
    }  
  }
}
