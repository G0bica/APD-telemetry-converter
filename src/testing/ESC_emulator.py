"""
PC version of the Arduino ESC emulator sketch:
sends the same 10 bytes at 115200 8N1 once per second, waits for the
Arduino's reply line and prints it to the terminal.

Install:  pip install pyserial
Run:      python esc_emulator.py        (set PORT below first)
"""
import time, math, random

import serial  # pyserial

def randomize() :

    for i in range(10) :
        rand = random.random()

        if rand < 0.2 :
            BYTES[i] += 1

        elif rand < 0.4 and BYTES[i] > 0 :
            BYTES[i] -= 1
    
    

PORT = "COM3"  # Windows: "COM5"   Linux: "/dev/ttyACM0"   macOS: "/dev/cu.usbmodem..."
PERIOD = 1.0   # seconds between packets, like delay(1000)

BYTES = bytearray([0x23, 0x0B, 0x5A, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0xB7])  # sample data

# setup(): Serial.begin(115200, SERIAL_8N1)
# timeout = how long readline() waits for the Arduino's answer
ser = serial.Serial(PORT, 115200, bytesize=8, parity="N", stopbits=1, timeout=PERIOD)
time.sleep(2)            # opening the port resets the Uno; wait until it is running
ser.reset_input_buffer()  # throw away anything printed during the reset

# loop()
while True:
    start = time.monotonic()
    ser.write(BYTES)                     # Serial.write(bytes, sizeof(bytes))

    line = ser.readline()                # wait for one line ending in '\n' (println)
    if line:
        print("Arduino:", line.decode(errors="replace").rstrip())
    else:
        print("(no response)")

    # keep a steady 1 s period, however long the reply took
    remaining = PERIOD - (time.monotonic() - start)
    if remaining > 0:
        time.sleep(remaining)
    
    randomize()