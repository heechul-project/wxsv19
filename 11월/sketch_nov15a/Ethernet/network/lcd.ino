// lcd

void paintAll(void) {
  switch (seqPaintAll) {
    case 0:
      paintCount();
      break;

    case 1:
      paintTime();
      break;
  }
}

void paintCount(void) {  // 5ms
  if (flagStartPaintCount == true) {
    digitalWrite(TFT_CS, HIGH);

    begin_time = micros();

    uint8_t thousands_digit;
    uint8_t hundreds_digit;
    uint8_t tens_digit;
    uint8_t ones_digit;

    thousands_digit = test_number / 1000;         // 천의 자릿수 계산
    hundreds_digit = (test_number % 1000) / 100;  // 백의 자릿수 계산
    tens_digit = (test_number % 100) / 10;        // 십의 자릿수 계산
    ones_digit = test_number % 10;                // 일의 자릿수 계산

    switch (seqPaintCount) {
      case 0:
        tft.resetViewport();
        tft.setViewport(0, 0, 26, 36);
        tft.fillScreen(TFT_BLACK);  // 1100us
        tft.setTextDatum(TL_DATUM);
        seqPaintCount = 1;
        break;

      case 1:
        tft.drawChar(3, 3, thousands_digit + 0x30, TFT_WHITE, TFT_BLACK, 4);  // 2900us
        seqPaintCount = 2;
        break;

      case 2:
        tft.setViewport(26, 0, 26, 36);
        tft.fillScreen(TFT_BLACK);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintCount = 3;
        break;

      case 3:
        tft.drawChar(3, 3, hundreds_digit + 0x30, TFT_GREEN, TFT_BLACK, 4);
        seqPaintCount = 4;
        break;

      case 4:
        tft.setViewport(52, 0, 26, 36);
        tft.fillScreen(TFT_BLACK);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintCount = 5;
        break;

      case 5:
        tft.drawChar(3, 3, tens_digit + 0x30, TFT_YELLOW, TFT_BLACK, 4);
        seqPaintCount = 6;
        break;

      case 6:
        tft.setViewport(78, 0, 26, 36);
        tft.fillScreen(TFT_BLACK);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintCount = 7;
        break;

      case 7:
        tft.drawChar(3, 3, ones_digit + 0x30, TFT_BLUE, TFT_BLACK, 4);
        seqPaintCount = 0;
        flagStartPaintCount = false;
        seqPaintAll = 1;
        break;
    }

    elapsed_time = micros() - begin_time;
    //Serial.println(elapsed_time);

    digitalWrite(TFT_CS, LOW);
  } else seqPaintAll = 1;
}

void paintTime(void) {  // 5ms
  if (flagStartPaintTime == true) {
    digitalWrite(TFT_CS, HIGH);

    begin_time = micros();

    switch (seqPaintTime) {
      case 0:
        tft.resetViewport();

        tft.setViewport(0, 300, 15, 20);
        tft.fillScreen(TFT_RED);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintTime = 1;
        break;

      case 1:
        tft.drawChar(1, 1, time[0], TFT_WHITE, TFT_RED, 2);
        seqPaintTime = 2;
        break;

      case 2:
        tft.setViewport(15, 300, 15, 20);
        tft.fillScreen(TFT_RED);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintTime = 3;
        break;

      case 3:
        tft.drawChar(1, 1, time[1], TFT_WHITE, TFT_RED, 2);
        seqPaintTime = 4;
        break;

      case 4:
        tft.setViewport(30, 300, 15, 20);
        tft.fillScreen(TFT_RED);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintTime = 5;
        break;

      case 5:
        tft.drawChar(1, 1, 0x3A, TFT_WHITE, TFT_RED, 2);
        seqPaintTime = 6;
        break;

      case 6:
        tft.setViewport(45, 300, 15, 20);
        tft.fillScreen(TFT_RED);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintTime = 7;
        break;

      case 7:
        tft.drawChar(1, 1, time[2], TFT_WHITE, TFT_RED, 2);
        seqPaintTime = 8;
        break;

      case 8:
        tft.setViewport(60, 300, 15, 20);
        tft.fillScreen(TFT_RED);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintTime = 9;
        break;

      case 9:
        tft.drawChar(1, 1, time[3], TFT_WHITE, TFT_RED, 2);
        seqPaintTime = 10;
        break;

      case 10:
        tft.setViewport(75, 300, 15, 20);
        tft.fillScreen(TFT_RED);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintTime = 11;
        break;

      case 11:
        tft.drawChar(1, 1, 0x3A, TFT_WHITE, TFT_RED, 2);
        seqPaintTime = 12;
        break;

      case 12:
        tft.setViewport(90, 300, 15, 20);
        tft.fillScreen(TFT_RED);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintTime = 13;
        break;

      case 13:
        tft.drawChar(1, 1, time[4], TFT_WHITE, TFT_RED, 2);
        seqPaintTime = 14;
        break;

      case 14:
        tft.setViewport(105, 300, 15, 20);
        tft.fillScreen(TFT_RED);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqPaintTime = 15;
        break;

      case 15:
        tft.drawChar(1, 1, time[5], TFT_WHITE, TFT_RED, 2);
        seqPaintTime = 0;
        flagStartPaintTime = false;
        seqPaintAll = 0;
        break;
    }

    elapsed_time = micros() - begin_time;
    //Serial.println(elapsed_time);

    digitalWrite(TFT_CS, LOW);
  } else seqPaintAll = 0;
}