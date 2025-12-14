**ID**: TEST_0007

**REQ**: REQ_0015

**Description**: Verify parameters LEFT_MOTOR_PWM_FACTOR and RIGHT_MOTOR_PWM_FACTOR are defined in configuration.

| Step # | Action | Expected result |
|--------|--------|-----------------|
| 1 | A1: Include configuration. | V1: No expected result. |
| 2 | A2: Verify variable LEFT_MOTOR_PWM_FACTOR exists. | V2: Variable exists with default value 1.0. |
| 3 | A3: Verify variable RIGHT_MOTOR_PWM_FACTOR exists. | V3: Variable exists with default value 0.9. |