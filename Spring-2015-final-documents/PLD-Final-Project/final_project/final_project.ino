#include <Serial.h>

const int switchPin = 7;
int switchState = 0;
char val;

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(8, OUTPUT);
  digitalWrite(switchPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  val = Serial.read();
  switchState = digitalRead(switchPin);
  Serial.println(digitalRead(switchPin));
  delay(200);
  if (switchState == LOW) {
    tone(10, 400, 2000);
    digitalWrite(8, HIGH);
    delay(4000);
    digitalWrite(8, LOW);
    delay(1000);
  }
  else if (val == 'A') {
    tone(10, 400, 2000);
    digitalWrite(8, HIGH);
    delay(4000);
    digitalWrite(8, LOW);
    delay(1000);
    val = 'a';
  }
}

