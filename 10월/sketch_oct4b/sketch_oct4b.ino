// 채트링 현상 : 버튼을 누를 때 LOW~HIGH 를 아주 짧은시간동안 빠르게 왔다갔다해서 난리가 나는 현상 ^^ 
// 채트링 현상을 잡아봅시다!!!

#include <avr/wdt.h>

uint32_t count = 0;
bool run_once = false;

bool f_bt0 = false;
bool f_bt1 = false;

uint32_t d_bt0 = 0;
uint32_t d_bt1 = 0;

uint32_t c_bt0 = 0;
uint32_t c_bt1 = 0;


void setup() {
  Serial.begin(115200);
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
  
  cli();
  set_timer_10KHz();
  sei();

  wdt_enable(WDTO_15MS);
}

void loop() {
  wdt_reset();

  if(run_once == true){
    run_once = false;

    digitalWrite(13, HIGH);

    check_btn_0();
    check_btn_1();

    digitalWrite(13, LOW);
  }
}

ISR(TIMER1_COMPA_vect){
  if(count++ >= 20){
    count = 1;

    run_once = true;
  }
}

void set_timer_10KHz() {
  //set timer1 interrupt at 10KHz
  TCCR1A = 0;  // set entire TCCR1A register to 0
  TCCR1B = 0;  // same for TCCR1B
  TCNT1 = 0;   //initialize counter value to 0
  // set compare match register for 10KHz increments
  OCR1A = 199;  // = (16*10^6) / (10000*8) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 and CS10 bits for 8 prescaler
  TCCR1B |= (1 << CS11);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void check_btn_0(void){
  if(digitalRead(2) == HIGH){
    if(d_bt0++ >= 20){
      if(f_bt0 == false){
        f_bt0 = true;

        c_bt0++;
        Serial.println("count : " + String(c_bt0));
      }
    }
  }
  else{
    d_bt0 = 0;
    f_bt0 = false;
  }
}

void check_btn_1(void){
  if(digitalRead(3) == HIGH){
    if(d_bt1++ >= 20){
      if(f_bt1 == false){
        f_bt1 = true;

        c_bt1++;
        Serial.println("count : " + String(c_bt1));
      }
    }
  }
  else{
    d_bt1 = 0;
    f_bt1 = false;
  }
}