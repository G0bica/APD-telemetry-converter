uint8_t bytes[10] = {0x13, 0x41, 0x10, 0xAA, 0xFF, 0xFE, 0xAB, 0x11, 0xAF, 0xA1}; // sample data


void setup() {
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  
  Serial.write(bytes, sizeof(bytes));

  delay(1000);



}
