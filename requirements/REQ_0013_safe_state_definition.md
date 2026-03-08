**ID**: REQ_0013

**Status**: In specification

**Type**: Functional

**Description**:<br>
Safe-state is at the end of the setup() function when
- all needed self-checks are passed
- motor pins ([motor pin definition](REQ_0002_motor_pin_definitions.md)) are set as expected:
  - forward pin shall be set to LOW
  - backward pin shall be set to LOW