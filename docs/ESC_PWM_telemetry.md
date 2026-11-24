# ESC PWM telemetry protocol

Format : 10 bajtov, vsak bajt ima 0 - start bit in  1 - stop bit, torej 10 bitov na bajt podatkov <br>
Bajti so organizirani LSB first, torej 11000000b = 3d 

## Baud rate calculation ( 115200 )

V intervalu 800 μs je bilo poslanih ≈ 93 bitov, torej ≈8.6022 μs na bit, kar je baud rate 116249, probably 115200

## Data format

