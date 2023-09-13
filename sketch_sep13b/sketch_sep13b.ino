#include <avr/wdt.h>
bool run_once = false;
bool seq1, seq2 = false;
uint16_t count1, count2 = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("reset");

  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);

  // cli();
  // set_timer_1KHz();
  // sei();

  wdt_enable(WDTO_15MS);

  analogWrite(10, 1);
}

void loop(){
  wdt_reset();

  if(run_once == true){
    run_once = false;
    
    digitalWrite(13, HIGH);

    proc_LED1();
    proc_LED2();

    digitalWrite(13, LOW);
  }
  
}

ISR(TIMER1_COMPA_vect) {
  run_once = true;
}

void set_timer_1KHz() {
  //set timer1 interrupt at 1KHz
  TCCR1A = 0;  // set entire TCCR1A register to 0
  TCCR1B = 0;  // same for TCCR1B
  TCNT1 = 0;   //initialize counter value to 0
  // set compare match register for 1KHz increments
  OCR1A = 249;  // = (16*10^6) / (1000*64) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 and CS10 bits for 64 prescaler
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void proc_LED1(void){
  if(seq1 == true) digitalWrite(9, HIGH);
  else digitalWrite(9, LOW);

  if(count1++ >= 1000){
    count1 = 0;
    seq1 = !seq1;
  }
}

void proc_LED2(void){
  if(seq2 == true) digitalWrite(10, HIGH);
  else digitalWrite(10, LOW);

  if(count2++ >= 2000){
    count2 = 0;
    seq2 = !seq2;
  }
}