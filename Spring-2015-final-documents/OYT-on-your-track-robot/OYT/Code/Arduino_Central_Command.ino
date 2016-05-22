// ----------------------------------------------------
// Illinois Institute of Technology
// ITMT 492 - Embedded Systems
//
// Students: Igor de Sousa Dantas,
// 			 Leonardo Pavanatto Soares,
// 			 Nicolas Ribeiro Vieira,
// 			 Pedro Henrique de Brito Souza,
// 			 Rodrigo Moreno Garcia.
//
// Instructors: Dr Daniel Tomal,
// 			   Jeremy Hajek.
//
// Project: O.Y.T. - The Track Guided Robot
// File: Arduino Central Command
// Last Modified: May 5, 2015
// ----------------------------------------------------
int i = 0;
void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
}

boolean flag = true;
void loop(){
  if(Serial.available()){
    Serial1.write(Serial.read());
    delay(600);
  }  
  
  if(Serial1.available()){
    Serial.println(Serial1.read());
  }
}
