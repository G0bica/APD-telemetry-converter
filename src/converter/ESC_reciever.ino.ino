struct Telemetry {
  int8_t   tempC;
  float    volts;
  float    amps;
  uint16_t mAh;
  uint32_t erpm;
};

uint8_t buffer[10];
Telemetry telem;

void transmit() {

  // TODO

}

void print(){
  Serial.print("Temp: ");        Serial.print(telem.tempC);    Serial.print(" C   ");
  Serial.print("Voltage: ");     Serial.print(telem.volts, 2); Serial.print(" V   ");
  Serial.print("Current: ");     Serial.print(telem.amps, 2);  Serial.print(" A   ");
  Serial.print("Consumption: "); Serial.print(telem.mAh);      Serial.print(" mAh   ");
  Serial.print("eRPM: ");        Serial.println(telem.erpm);
}

bool decode(const uint8_t *buf, Telemetry *t) {
  t->tempC = (int8_t)buf[0];
  t->volts = ((buf[1] << 8) | buf[2]) / 100.0;     // bytes: high byte first
  t->amps  = ((buf[3] << 8) | buf[4]) / 100.0;
  t->mAh   =  (buf[5] << 8) | buf[6];
  t->erpm  = (uint32_t)((buf[7] << 8) | buf[8]) * 100;
  return true;
}

void setup() {
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  if (Serial.readBytes(buffer, 10) == 10) {
    if (decode(buffer, &telem)) {
      print();
      // transmit()
    }
  }
}