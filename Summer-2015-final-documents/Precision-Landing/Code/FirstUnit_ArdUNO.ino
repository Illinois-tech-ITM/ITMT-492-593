//Threshold for the microphone signal. This code works with a 8 bits precision (0 to 255).
int thr0 = 170;
int thr1 = 170;
int thr2 = 170;
int thr3 = 170;

void setup(){
  Serial.begin(9600);
  DDRD = DDRD | B11111100;//PORTD (Digital ports 0 - 7). 1 for enable output. B76543210. Take care with bits 0 and 1 (RX and TX respectively)
  
  cli();//disable interrupts for setting variables
 
  //clear ADCSRA and ADCSRB registers
  ADCSRA = 0x00;
  ADCSRB = 0x00;
  
  ADMUX |= (1 << REFS0); //set reference voltage. AREF pin must be connected to 3.3v or 5V pin depending on the maximum voltage of inputs
  ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read highest 8 bits from ADCH register only
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 16mHz/32=500kHz
  //ADCSRA |= (1 << ADATE); //enabble auto trigger. For this code, ADATE must be 0 in order to guarantee ADIF with 1 (convertion complete)
  ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN); //enable ADC
  ADCSRA |= (1 << ADSC); //start ADC measurements 
  
  sei();//enable interrupts
}

ISR(ADC_vect) {//when new ADC value ready
  //ADMUX has MUX3, MUX2, MUX1 and MUX0 bits in order to control the input signal coming from analog ports. 0000 for A0, 0001 for A1, 0010 for A2 and 0011 for A3
  PORTD = B00000000;//Turn off all PORTD
  ADCSRA |= (1 << ADSC);//Start analog port
  while (!(ADCSRA & (1 << ADIF))){}//Wait for the signal. This bit is 1 when the conversion is complete
  if(ADCH > thr0){//Testing if A0 signal is bigger than threshold
    PORTD = B00100000;
  }
  ADMUX = ADMUX | (1<<MUX0); //Changing for A1
    ADCSRA |= (1 << ADSC);//Start analog port
    while (!(ADCSRA & (1 << ADIF))){}
  if(ADCH > thr1){
    PORTD = B01000000;
  }
  ADMUX =  ADMUX | (1<<MUX1);//Changing for A3
    ADCSRA |= (1 << ADSC);//Start analog port
    while (!(ADCSRA & (1 << ADIF))){}
  if(ADCH > thr2){
    PORTD = B10000000;
  }
  ADMUX = ADMUX & ~(1<<MUX0);//Changing for A2  
  ADCSRA |= (1 << ADSC);//Start analog port
    while (!(ADCSRA & (1 << ADIF))){}
  if(ADCH > thr3){
    PORTD = B00010000;
  }
  ADMUX = ADMUX & ~(1<<MUX1);//Changing for A0
  ADCSRA |= (1 << ADSC);//Start analog port in order to keep the ISR working and reading the first A0 signal and so on.
  //This code runs in a loop because analog ports continuosly receive a new signal coming from the microphones.  
}

void loop(){//loop method is empty because the interrupt runs when a new ADC value is ready (every time)
}
