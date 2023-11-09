#include "STM32TimerInterrupt.h"
#include <TFT_eSPI.h>
#include <SPI.h>
//#include <IWatchdog.h>

// system
#define BUILTIN_LED PC13  // A.L
STM32Timer ITimer(TIM1);
uint32_t begin_time = 0;
uint32_t finish_time = 0;
uint32_t elapsed_time = 0;
uint32_t max_elapsed_time = 0;
uint8_t count100us = 0;

// buzzer
#define BUZZER PA8

// TFT LCD
#define TFT_RESET PB8
#define TFT_CS PA4  // NSS1
TFT_eSPI tft = TFT_eSPI();


void TimerHandler()  // 100us
{
  count100us++;
}

void setup() {
  // put your setup code here, to run once:
  //IWatchdog.begin(2000000);  // 2000ms

  begin_time = micros();

  tone(BUZZER, 500, 500);

  Serial.begin(115200);
  while (!Serial)
    ;

  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);  // OFF

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);  // OFF

  pinMode(TFT_RESET, OUTPUT);
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TFT_RESET, HIGH);  // 리셋 A.L

  ITimer.attachInterruptInterval(100, TimerHandler);  // 100us

  elapsed_time = micros() - begin_time;
  Serial.println("setup elapsed time: " + String(elapsed_time) + "us");

  begin_time = micros();

  tft.init();
  tft.fillScreen(TFT_RED);
  tft.setRotation(0);

  tft.setViewport(0, 0, 26, 36);
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(TL_DATUM);
  tft.drawChar(3, 3, 'A', TFT_WHITE, TFT_BLACK, 4);


  elapsed_time = micros() - begin_time;
  Serial.println("TFT LCD elapsed time: " + String(elapsed_time) + "us");

  //IWatchdog.reload();
  //IWatchdog.begin(50000);  // 50ms
}

void loop() {
  // put your main code here, to run repeatedly:

  if (count100us >= 50) {  // 5ms
    count100us = 0;

    begin_time = micros();

    digitalWrite(BUILTIN_LED, LOW);  // ON
    // 사용자 코드 시작 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




    // 사용자 코드 끝 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    elapsed_time = micros() - begin_time;
    if (elapsed_time > max_elapsed_time) {
      max_elapsed_time = elapsed_time;
      Serial.println("max elapsed time: " + String(max_elapsed_time) + "us");
    }

    digitalWrite(BUILTIN_LED, HIGH);  // OFF
  }

  //IWatchdog.reload();
}
