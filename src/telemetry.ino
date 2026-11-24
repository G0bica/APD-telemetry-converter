#include <Arduino.h>
#include <eagle_soc.h>

#define INPUT_PIN 14       // D5
#define SAMPLE_COUNT 1000
#define SAMPLE_RATE_US 1

uint8_t buffer[SAMPLE_COUNT / 8];

void setup() {
    Serial.begin(921600);
    pinMode(INPUT_PIN, INPUT);

    delay(500);
}

void loop() {
    // Wait for idle HIGH
    while (digitalRead(INPUT_PIN) == LOW) {}

    // Detect falling edge
    while (digitalRead(INPUT_PIN) == HIGH) {}

    // Capture
    memset(buffer, 0, sizeof(buffer));

    noInterrupts();

    for (int i = 0; i < SAMPLE_COUNT; i++) {
        if (GPIO_REG_READ(GPIO_IN_ADDRESS) & (1UL << INPUT_PIN)) {
            buffer[i >> 3] |= (1 << (i & 7));
        }

        // Approximate timing only!
        delayMicroseconds(SAMPLE_RATE_US);
    }

    interrupts();

    for (int i = 0; i < sizeof(buffer); i++) {
      if (buffer[i] < 0x10) Serial.print("0");
      Serial.print(buffer[i], HEX);
      Serial.print(" ");

    if ((i + 1) % 10 == 0) {
        Serial.println();
    }
}
}