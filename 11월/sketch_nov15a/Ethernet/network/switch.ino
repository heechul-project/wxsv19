// switch

void check_SW_0(void) {
  if (digitalRead(sw_0.pin) == HIGH) {  // 버튼 누름
    if (sw_0.delay++ >= 10) {           // 5ms 마다 증가해서 누른채로 50ms지나면
      if (sw_0.flag == false) {
        sw_0.flag = true;

        Serial.println("sw_0");
        tone(BUZZER, 1000, 100);

        test_number++;
        if (flag_start_paint == false) flag_start_paint = true;
      }
    }
  } else  // 버튼 놓음, 또는 채터링시에도 변수 리셋
  {
    sw_0.delay = 0;
    sw_0.flag = false;
  }
}

void check_SW_1(void) {
  if (digitalRead(sw_1.pin) == HIGH) {  // 버튼 누름
    if (sw_1.delay++ >= 10) {           // 5ms 마다 증가해서 누른채로 50ms지나면
      if (sw_1.flag == false) {
        sw_1.flag = true;

        Serial.println("sw_1");
        tone(BUZZER, 1000, 100);

        test_number++;
        if (flag_start_paint == false) flag_start_paint = true;

      }
    }
  } else  // 버튼 놓음, 또는 채터링시에도 변수 리셋
  {
    sw_1.delay = 0;
    sw_1.flag = false;
  }
}

void check_SW_2(void) {
  if (digitalRead(sw_2.pin) == HIGH) {  // 버튼 누름
    if (sw_2.delay++ >= 10) {           // 5ms 마다 증가해서 누른채로 50ms지나면
      if (sw_2.flag == false) {
        sw_2.flag = true;

        Serial.println("sw_2");
        tone(BUZZER, 1000, 100);

        test_number--;
        if (flag_start_paint == false) flag_start_paint = true;
      }
    }
  } else  // 버튼 놓음, 또는 채터링시에도 변수 리셋
  {
    sw_2.delay = 0;
    sw_2.flag = false;
  }
}

void check_SW_3(void) {
  if (digitalRead(sw_3.pin) == HIGH) {  // 버튼 누름
    if (sw_3.delay++ >= 10) {           // 5ms 마다 증가해서 누른채로 50ms지나면
      if (sw_3.flag == false) {
        sw_3.flag = true;

        Serial.println("sw_3");
        tone(BUZZER, 1000, 100);

        test_number++;
        if (flag_start_paint == false) flag_start_paint = true;
      }
    }
  } else  // 버튼 놓음, 또는 채터링시에도 변수 리셋
  {
    sw_3.delay = 0;
    sw_3.flag = false;
  }
}