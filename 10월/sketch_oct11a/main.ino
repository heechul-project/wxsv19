#include <STM32TimerInterrupt.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <IWatchdog.h>

// system
#define BUILTIN_LED PC13  // A.L
STM32Timer ITimer(TIM1);
uint32_t start = 0;
uint32_t loop_time = 0;
uint32_t max_loop_time = 0;
uint8_t count100us = 0;

// buzzer
#define BUZZER PA8

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

uint16_t test_number;

// network
#define W5500_RESET PB7
#define W5500_CS    PB6  // nSS

// TFT LCD
#define TFT_RESET PB8
#define TFT_CS    PA4 // NSS1
TFT_eSPI tft = TFT_eSPI();
bool flag_start_paint = false;
uint8_t seqRefreshTFT = 0;
uint16_t delayRefreshTFT = 0;


void TimerHandler()  // 100us
{
  count100us++;
}

void setup() {
  // put your setup code here, to run once:
  start = micros();

  tone(BUZZER, 500, 500);

  IWatchdog.begin(500000);  // 500ms

  Serial.begin(115200);
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

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);  // OFF

  pinMode(W5500_CS, OUTPUT);
  pinMode(W5500_RESET, OUTPUT);

  pinMode(TFT_RESET, OUTPUT);
  pinMode(TFT_CS, OUTPUT);

  tft.init();
  tft.fillScreen(TFT_RED);
  tft.setRotation(0);

  digitalWrite(W5500_RESET, LOW);  // 리셋 A.L
  digitalWrite(TFT_RESET, HIGH);   // 리셋 A.L

  ITimer.attachInterruptInterval(100, TimerHandler);  // 100us

  loop_time = micros() - start;
  Serial.println("setup time: " + String(loop_time) + "us");

  IWatchdog.reload();
  IWatchdog.begin(50000);  // 50ms
}

void loop() {
  // put your main code here, to run repeatedly:

  if (count100us >= 50) {  // 5ms
    count100us = 0;

    start = micros();

    digitalWrite(BUILTIN_LED, LOW);  // ON
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    refresh_TFT();

    check_SW_0();
    check_SW_1();
    check_SW_2();
    check_SW_3();


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    loop_time = micros() - start;
    if (loop_time > max_loop_time) {
      max_loop_time = loop_time;
      Serial.println("max loop time: " + String(max_loop_time) + "us");
    }

    digitalWrite(BUILTIN_LED, HIGH);  // OFF
  }

  IWatchdog.reload();
}


