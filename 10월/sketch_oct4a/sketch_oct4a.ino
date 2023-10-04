// 채트링 현상 : 버튼을 누를 때 LOW~HIGH 를 아주 짧은시간동안 빠르게 왔다갔다해서 난리가 나는 현상 ^^
#include <avr/wdt.h>

uint32_t count_push = 0;

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT);
  wdt_enable(WDTO_15MS);
}

void loop() {
  wdt_reset();
  if(digitalRead(2)==HIGH){
    count_push++;
  }
  else{
    if(count_push != 0){
      Serial.println(String(count_push)); // 30000~50000 등 기하급수적으로 느는 count 의 값은 전부 채트링 현상 때문!!!!!
    }
    count_push = 0;
  }
}
