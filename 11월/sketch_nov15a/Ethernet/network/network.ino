// network

String getFormattedTime(unsigned long epoch) {
  int hours, minutes, seconds;
  epoch += 32400;         // UTC 시간에서 대한민국 시간으로 변경합니다. (9시간 추가)
  epoch = epoch % 86400;  // 일 초에 대한 나머지를 계산합니다.
  hours = epoch / 3600;
  minutes = (epoch % 3600) / 60;
  seconds = epoch % 60;

  String formattedTime = (hours < 10 ? "0" : "") + String(hours) + (minutes < 10 ? "0" : "") + String(minutes) + (seconds < 10 ? "0" : "") + String(seconds);
  return formattedTime;
}

char getCharFromString(String formattedTime, int position) {
  if (position >= 0 && position < formattedTime.length()) {
    return formattedTime.charAt(position);
  } else {
    return '\0';  // 유효하지 않은 위치일 경우 null 문자를 반환합니다.
  }
}

void sendNTPpacket(IPAddress& address) {
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;
  packetBuffer[1] = 0;
  packetBuffer[2] = 6;
  packetBuffer[3] = 0xEC;
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;

  Udp.beginPacket(address, 123);
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

void getCurrentTime(void) {
  if (ethernet_connected == true) {
    switch (seqGetTime) {
      case 0:
        digitalWrite(W5500_CS, LOW);
        delay(10);

        sendNTPpacket(timeServer);  // 568us
        digitalWrite(W5500_CS, HIGH);
        delayGetTime = 0;
        seqGetTime = 1;
        break;

      case 1:
        if (Udp.parsePacket()) {  // 수신 됨
          Udp.read(packetBuffer, NTP_PACKET_SIZE);
          unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
          unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
          unsigned long epoch = highWord << 16 | lowWord;
          epoch -= 2208988800L;  // 1970년 1월 1일부터 시간을 계산하기 위한 공식
          formattedTime = getFormattedTime(epoch);

          time[0] = getCharFromString(formattedTime, 0);
          time[1] = getCharFromString(formattedTime, 1);
          time[2] = getCharFromString(formattedTime, 2);
          time[3] = getCharFromString(formattedTime, 3);
          time[4] = getCharFromString(formattedTime, 4);
          time[5] = getCharFromString(formattedTime, 5);

          //Serial.println(formattedTime);

          seqPaintTime = 0;
          flagStartPaintTime = true;

        } else {  // 받은 패킷 없음
        }
        delayGetTime = 0;
        seqGetTime = 2;
        break;

      case 2:
        if (delayGetTime++ > 200) {
          delayGetTime = 0;
          seqGetTime = 0;
        }
        break;
    }
  } else {
    digitalWrite(W5500_CS, HIGH);
  }
}