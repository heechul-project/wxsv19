// main.ino

#include "STM32TimerInterrupt.h"
#include <IWatchdog.h>

// system
#define BUILTIN_LED PC13  // A.L
STM32Timer ITimer(TIM1);

// switch
#define SW_0_PIN PB5
#define SW_1_PIN PB4
#define SW_2_PIN PB3
#define SW_3_PIN PA15

struct SW {
  uint8_t pin;
  bool flag;
  uint8_t delay;
};

SW sw_0;
SW sw_1;
SW sw_2;
SW sw_3;

//
uint8_t count100us = 0;


void TimerHandler()  // 100us
{
  count100us++;
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial)
    ;

  sw_0.pin = SW_0_PIN;
  sw_1.pin = SW_1_PIN;
  sw_2.pin = SW_2_PIN;
  sw_3.pin = SW_3_PIN;

  pinMode(sw_0.pin, INPUT);
  pinMode(sw_1.pin, INPUT);
  pinMode(sw_2.pin, INPUT);
  pinMode(sw_3.pin, INPUT);

  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);  // OFF

  ITimer.attachInterruptInterval(100, TimerHandler);  // 100us

  IWatchdog.reload();
  IWatchdog.begin(50000);  // 50ms
}

void loop() {
  // put your main code here, to run repeatedly:

  if (count100us >= 50) {  // 5ms
    count100us = 0;

    digitalWrite(BUILTIN_LED, LOW);  // ON
    // 사용자 코드 시작 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    check_SW_0();
    check_SW_1();
    check_SW_2();
    check_SW_3();

    // 사용자 코드 끝 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    digitalWrite(BUILTIN_LED, HIGH);  // OFF
  }

  IWatchdog.reload();
}
