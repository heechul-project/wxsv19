void paint_TFT_2(void) {  // 5ms
  if (flag_start_paint == true) {
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

    switch (seqRefreshTFT) {
      case 0:
        tft.setViewport(0, 0, 26, 36);
        tft.fillScreen(TFT_BLACK);  // 1100us
        tft.setTextDatum(TL_DATUM);
        seqRefreshTFT = 1;
        break;

      case 1:
        tft.drawChar(3, 3, thousands_digit + 0x30, TFT_WHITE, TFT_BLACK, 4);  // 2900us
        seqRefreshTFT = 2;
        break;

      case 2:
        tft.setViewport(26, 0, 26, 36);
        tft.fillScreen(TFT_BLACK);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqRefreshTFT = 3;
        break;

      case 3:
        tft.drawChar(3, 3, hundreds_digit + 0x30, TFT_GREEN, TFT_BLACK, 4);
        seqRefreshTFT = 4;
        break;

      case 4:
        tft.setViewport(52, 0, 26, 36);
        tft.fillScreen(TFT_BLACK);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqRefreshTFT = 5;
        break;

      case 5:
        tft.drawChar(3, 3, tens_digit + 0x30, TFT_YELLOW, TFT_BLACK, 4);
        seqRefreshTFT = 6;
        break;

      case 6:
        tft.setViewport(78, 0, 26, 36);
        tft.fillScreen(TFT_BLACK);  // 1090us
        tft.setTextDatum(TL_DATUM);
        seqRefreshTFT = 7;
        break;

      case 7:
        tft.drawChar(3, 3, ones_digit + 0x30, TFT_BLUE, TFT_BLACK, 4);
        seqRefreshTFT = 0;

        flag_start_paint = false;
        break;
    }

    elapsed_time = micros() - begin_time;
    Serial.println(elapsed_time);

    digitalWrite(TFT_CS, LOW);
  }
}