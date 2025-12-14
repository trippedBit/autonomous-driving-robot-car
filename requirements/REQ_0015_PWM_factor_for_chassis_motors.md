**ID**: REQ_0015

**Status**: Finalized

**Type**: Functional

**Description**:<br>
To ensure robot can drive straight forward, a configurable factor for both PWM signals shall be available. This is usefull in case different motors are used or in case same PWM leads to different revolutions on both sides.<br>
The factor itself shall not be limit in any way.<br>
The resulting PWM shall be limited to the range 0-255.

Example:
- Calculated base PWM value is 175.
- Factor for left motor is 1.
- Factor for right motor is 2.
- Resulting PWM for left motor: 175 * 1 = 175
- Resulting PWM for right motor: 175 * 2 = 350, limited to 255