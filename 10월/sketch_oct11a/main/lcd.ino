// lcd

void refresh_TFT(void) {  // 5ms
  if (flag_start_paint == true) {
    //start = micros();

    uint8_t thousands_digit;
    static uint8_t last_thousands_digit;
    uint8_t hundreds_digit;
    static uint8_t last_hundreds_digit;
    uint8_t tens_digit;
    static uint8_t last_tens_digit;
    uint8_t ones_digit;
    static uint8_t last_one_digit;

    thousands_digit = test_number / 1000;         // 천의 자릿수 계산
    hundreds_digit = (test_number % 1000) / 100;  // 백의 자릿수 계산
    tens_digit = (test_number % 100) / 10;        // 십의 자릿수 계산
    ones_digit = test_number % 10;                // 일의 자릿수 계산

    switch (seqRefreshTFT) {
      case 0:
        tft.setViewport(0, 0, 26, 36);
        //tft.fillScreen(TFT_BLACK);  // 1090us
        tft.setTextDatum(TL_DATUM);
        tft.drawChar(3, 3, last_thousands_digit + 0x30, TFT_BLACK, TFT_BLACK, 4);  // 2900us
        seqRefreshTFT = 1;
        break;

      case 1:
        tft.drawChar(3, 3, thousands_digit + 0x30, TFT_WHITE, TFT_BLACK, 4);  // 2900us
        last_thousands_digit = thousands_digit;
        seqRefreshTFT = 2;
        break;

      case 2:
        tft.setViewport(26, 0, 26, 36);
        //tft.fillScreen(TFT_BLACK);  // 1090us
        tft.setTextDatum(TL_DATUM);
        tft.drawChar(3, 3, last_hundreds_digit + 0x30, TFT_BLACK, TFT_BLACK, 4);  // 2900us
        seqRefreshTFT = 3;
        break;

      case 3:
        tft.drawChar(3, 3, hundreds_digit + 0x30, TFT_GREEN, TFT_BLACK, 4);  // 2900us
        last_hundreds_digit = hundreds_digit;
        seqRefreshTFT = 4;
        break;

      case 4:
        tft.setViewport(52, 0, 26, 36);
        //tft.fillScreen(TFT_BLACK);  // 1090us
        tft.setTextDatum(TL_DATUM);
        tft.drawChar(3, 3, last_tens_digit + 0x30, TFT_BLACK, TFT_BLACK, 4);  // 2900us
        seqRefreshTFT = 5;
        break;

      case 5:
        tft.drawChar(3, 3, tens_digit + 0x30, TFT_YELLOW, TFT_BLACK, 4);  // 2900us
        last_tens_digit = tens_digit;
        seqRefreshTFT = 6;

        break;

      case 6:
        tft.setViewport(78, 0, 26, 36);
        //tft.fillScreen(TFT_BLACK);  // 1090us
        tft.setTextDatum(TL_DATUM);
        tft.drawChar(3, 3, last_one_digit + 0x30, TFT_BLACK, TFT_BLACK, 4);  // 2900us
        seqRefreshTFT = 7;
        break;

      case 7:
        tft.drawChar(3, 3, ones_digit + 0x30, TFT_BLUE, TFT_BLACK, 4);  // 2900us
        last_one_digit = ones_digit;
        seqRefreshTFT = 0;

        flag_start_paint = false;
        break;
    }
  }
}