# Assembly information
This document refers to the [BOM](../BOM/BOM.d), e.g.
```
Solder cable [12] to motor [1].
```
means, that the cable from [BOM](../BOM/BOM.d) list entry 12 shall be soldered to the motor from list entry 1.

## Step by step guide

### ESP32 preparation
1. Solder headers [8] to ESP32 [2].

### Cable preparation
1. Attach ferrule [6] to cable [7].
2. Attach ferrule [13] to cable [12].
3. Attach ferrule [15] to cable [14].
4. Attach ferrule [17] to cable [16].
5. Attach ferrule [19] to cable [18].

### Motor power supply
1. Motor 1 [1]<br>
1.1. Solder cable [12] to one of the motor's pins.<br>
1.2. Solder cable [14] to the motor's other pin.
2. Motor 2 [1]<br>
2.1. Solder cable [16] to one of the motor's pins.<br>
2.2. Solder cable [18] to the motor's other pin.
3. Connect cable [12] to LN298N [5] OUT1.
4. Connect cable [14] to LN298N [5] OUT2.
5. Connect cable [16] to LN298N [5] OUT3.
6. Connect cable [18] to LN298N [5] OUT4.

### Robot assembly
1. Assemble the robot chassis kit [1].
2. Connect ESP32 [2] PWM pin with L298N [5] ENA pin using cable [9].
3. Connect ESP32 [2] motor control pin 1 with L298N [5] IN1 pin using cable [10].
4. Connect ESP32 [2] motor control pin 2 with L298N [5] IN2 pin using cable [10].
5. Insert battery [4] into case [3].
6. Connect case [3] positive cable with L298N [5] +12V terminal.
7. Connect case [3] negative cable with LN298N [5] GND terminal.