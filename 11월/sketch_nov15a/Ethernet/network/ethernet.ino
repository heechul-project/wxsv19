#include "STM32TimerInterrupt.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include <IWatchdog.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

// system
#define BUILTIN_LED PC13  // A.L
STM32Timer ITimer(TIM1);
uint32_t begin_time = 0;
uint32_t finish_time = 0;
uint32_t elapsed_time = 0;
uint32_t max_elapsed_time = 0;
uint8_t count100us = 0;

// ethernet
#define W5500_RESET PB7
#define W5500_CS PB6  // nSS
unsigned int localPort = 8888;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  // 이게 중복되면 시간을 받아오지 못함
IPAddress timeServer(129, 6, 15, 28);  // 예: time.nist.gov NTP 서버
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];
EthernetUDP Udp;
bool ethernet_connected = false;

// time
String formattedTime = "";
char time[6];
uint8_t seqGetTime = 0;
uint16_t delayGetTime = 0;

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

// TFT LCD
#define TFT_RESET PB8
#define TFT_CS PA4  // NSS1
TFT_eSPI tft = TFT_eSPI();

bool flagStartPaintCount = false;
bool flag_start_paint = false;
uint8_t seqRefreshTFT = 0;
uint8_t seqPaintCount = 0;
uint16_t delayPaintCount = 0;

bool flagStartPaintTime = false;
uint8_t seqPaintTime = 0;

uint8_t seqPaintAll = 0;

//
uint16_t test_number = 0;


void TimerHandler()  // 100us
{
  count100us++;
}

void setup() {
  // put your setup code here, to run once:
  //IWatchdog.begin(20000000);  // 10s

  begin_time = micros();

  tone(BUZZER, 500, 500);

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

  // JTAG-DP 비활성화 및 SW-DP 활성화
  AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

  pinMode(W5500_CS, OUTPUT);
  pinMode(W5500_RESET, OUTPUT);
  digitalWrite(W5500_RESET, LOW);   // 리셋 A.L
  digitalWrite(W5500_RESET, HIGH);  // 리셋 A.L

  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);  // OFF

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);  // OFF

  pinMode(TFT_RESET, OUTPUT);
  digitalWrite(TFT_RESET, HIGH);  // 리셋 A.L
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TFT_CS, LOW);

  ITimer.attachInterruptInterval(100, TimerHandler);  // 100us

  elapsed_time = micros() - begin_time;
  //Serial.println("setup elapsed time: " + String(elapsed_time) + "us");

  begin_time = micros();

  tft.init();
  tft.fillScreen(TFT_RED);
  tft.setRotation(0);  // 381313us

  IWatchdog.reload();

  Ethernet.init(W5500_CS);  // Most Arduino shields
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {  // 실패
    Serial.println("Failed to configure Ethernet using DHCP");

    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }

    ethernet_connected = false;
  } else {  // 성공
    ethernet_connected = true;

    // print your local IP address:
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());

    Udp.begin(localPort);
  }

  elapsed_time = micros() - begin_time;
  Serial.println("TFT LCD elapsed time: " + String(elapsed_time) + "us");
  elapsed_time = 0;

  flagStartPaintCount = true;

  IWatchdog.reload();
  IWatchdog.begin(50000);  // 500ms
}

void loop() {
  // put your main code here, to run repeatedly:
  if (count100us >= 50) {  // 5ms
    count100us = 0;

    begin_time = micros();

    digitalWrite(BUILTIN_LED, LOW);  // ON
    // 사용자 코드 시작 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    getCurrentTime();
    paintAll();

    check_SW_0();
    check_SW_1();
    check_SW_2();
    check_SW_3();

    // 사용자 코드 끝 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    elapsed_time = micros() - begin_time;
    if (elapsed_time > max_elapsed_time) {
      max_elapsed_time = elapsed_time;
      Serial.println("max elapsed time: " + String(max_elapsed_time) + "us");
    }

    digitalWrite(BUILTIN_LED, HIGH);  // OFF
  }

  IWatchdog.reload();
}
