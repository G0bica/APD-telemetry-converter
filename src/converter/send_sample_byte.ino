/*
  FrSky S.Port sensor test: answers the receiver's poll with a sample byte.

  The sample byte (0x23 = 35) is sent as temperature sensor T1 (app ID 0x0400),
  so it shows up on the radio as "Tmp1 = 35 °C".

  S.Port: 57600 baud, 8N1, INVERTED, half-duplex on ONE wire.
  The receiver sends 0x7E + <physical ID> about every 12 ms, cycling through all IDs.
  When it polls our ID we answer with one 8-byte data frame:
      0x10 | appId (2 bytes, LSB first) | value (4 bytes, LSB first) | CRC

  Wiring (Uno):
      S.Port signal --[1 kΩ]-- D3
      S.Port GND ------------- GND
      (S.Port + is the receiver's supply; power the Uno from USB while testing)
*/
#include <SoftwareSerial.h>

#define SPORT_PIN   3         // one pin for both RX and TX
#define SENSOR_ID   0x0D      // physical ID 14; change if another sensor already uses it
#define APP_ID      0x0400    // T1 temperature, value in °C

uint8_t sampleByte = 0x23;    // the value to send (35)

SoftwareSerial sport(SPORT_PIN, SPORT_PIN, true);   // RX, TX, inverted logic

// S.Port byte stuffing: 0x7E and 0x7D inside a frame are sent as 0x7D, byte ^ 0x20
void writeStuffed(uint8_t b) {
  if (b == 0x7E || b == 0x7D) {
    sport.write(0x7D);
    sport.write(b ^ 0x20);
  } else {
    sport.write(b);
  }
}

void sendFrame(uint16_t appId, uint32_t value) {
  uint8_t f[7] = {
    0x10,                                   // data frame
    (uint8_t)appId, (uint8_t)(appId >> 8),  // app ID, LSB first
    (uint8_t)value, (uint8_t)(value >> 8),  // value, LSB first
    (uint8_t)(value >> 16), (uint8_t)(value >> 24)
  };

  // CRC: sum of the 7 bytes with the carry folded back in, then 0xFF - sum
  uint16_t crc = 0;
  for (uint8_t i = 0; i < 7; i++) {
    crc += f[i];
    crc += crc >> 8;
    crc &= 0xFF;
  }
  crc = 0xFF - crc;

  sport.stopListening();          // don't receive our own transmission
  pinMode(SPORT_PIN, OUTPUT);     // take the line
  for (uint8_t i = 0; i < 7; i++) writeStuffed(f[i]);
  writeStuffed((uint8_t)crc);
  pinMode(SPORT_PIN, INPUT);      // release the line so the receiver can talk again
  sport.listen();
}

void setup() {
  sport.begin(57600);
  pinMode(SPORT_PIN, INPUT);      // listen by default, never drive the line idle
  Serial.begin(115200);           // USB debug
  Serial.println("S.Port sensor ready");
}

void loop() {
  static bool lastWasStart = false;

  while (sport.available()) {
    uint8_t b = sport.read();
    if (lastWasStart && b == SENSOR_ID) {
      sendFrame(APP_ID, sampleByte);   // reply immediately: the slot is only a few ms
    }
    lastWasStart = (b == 0x7E);
  }
}