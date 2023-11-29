// switch

void check_SW_0(void) {
  if (digitalRead(sw_0.pin) == HIGH) {  // 버튼 누름
    if (sw_0.delay++ >= 10) {           // 5ms 마다 증가해서 누른채로 50ms지나면
      if (sw_0.flag == false) {
        sw_0.flag = true;

        uint8_t crc[2] = { 0x00, 0x00 };
        uint8_t pkt[12] = { 0x02, 0x31, 0x32, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x03, 0x00, 0x00 };

        uint16_t crc16 = CalcCRC(&pkt[0], 10);
        crc[1] = lowByte(crc16);
        crc[0] = highByte(crc16);
        pkt[10] = crc[0];
        pkt[11] = crc[1];

        SendPacket(pkt);
      }
    }
  } else  // 버튼 놓음, 또는 채터링시에도 변수 리셋
  {
    if (sw_0.flag == true) {
    }

    sw_0.delay = 0;
    sw_0.flag = false;
  }
}

void check_SW_1(void) {
  if (digitalRead(sw_1.pin) == HIGH) {  // 버튼 누름
    if (sw_1.delay++ >= 10) {           // 5ms 마다 증가해서 누른채로 50ms지나면
      if (sw_1.flag == false) {
        sw_1.flag = true;

        uint8_t crc[2] = { 0x00, 0x00 };
        uint8_t pkt[12] = { 0x02, 0x31, 0x32, 0x40, 0x40, 0x40, 0x40, 0x40, 0x41, 0x03, 0x00, 0x00 };

        uint16_t crc16 = CalcCRC(&pkt[0], 10);
        crc[1] = lowByte(crc16);
        crc[0] = highByte(crc16);
        pkt[10] = crc[0];
        pkt[11] = crc[1];

        SendPacket(pkt);
      }
    }
  } else  // 버튼 놓음, 또는 채터링시에도 변수 리셋
  {
    if (sw_1.flag == true) {
    }
    sw_1.delay = 0;
    sw_1.flag = false;
  }
}

void check_SW_2(void) {
  if (digitalRead(sw_2.pin) == HIGH) {  // 버튼 누름
    if (sw_2.delay++ >= 10) {           // 5ms 마다 증가해서 누른채로 50ms지나면
      if (sw_2.flag == false) {
        sw_2.flag = true;

        uint8_t crc[2] = { 0x00, 0x00 };
        uint8_t pkt[12] = { 0x02, 0x31, 0x32, 0x40, 0x40, 0x40, 0x40, 0x40, 0x42, 0x03, 0x00, 0x00 };

        uint16_t crc16 = CalcCRC(&pkt[0], 10);
        crc[1] = lowByte(crc16);
        crc[0] = highByte(crc16);
        pkt[10] = crc[0];
        pkt[11] = crc[1];

        SendPacket(pkt);
      }
    }
  } else  // 버튼 놓음, 또는 채터링시에도 변수 리셋
  {
    if (sw_2.flag == true) {
    }
    sw_2.delay = 0;
    sw_2.flag = false;
  }
}

void check_SW_3(void) {
  if (digitalRead(sw_3.pin) == HIGH) {  // 버튼 누름
    if (sw_3.delay++ >= 10) {           // 5ms 마다 증가해서 누른채로 50ms지나면
      if (sw_3.flag == false) {
        sw_3.flag = true;

        uint8_t crc[2] = { 0x00, 0x00 };
        uint8_t pkt[12] = { 0x02, 0x31, 0x32, 0x40, 0x40, 0x40, 0x40, 0x40, 0x43, 0x03, 0x00, 0x00 };

        uint16_t crc16 = CalcCRC(&pkt[0], 10);
        crc[1] = lowByte(crc16);
        crc[0] = highByte(crc16);
        pkt[10] = crc[0];
        pkt[11] = crc[1];

        SendPacket(pkt);
      }
    }
  } else  // 버튼 놓음, 또는 채터링시에도 변수 리셋
  {
    if (sw_3.flag == true) {
    }
    sw_3.delay = 0;
    sw_3.flag = false;
  }
}
