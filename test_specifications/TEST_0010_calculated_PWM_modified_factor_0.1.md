**ID**: TEST_0010

**REQ**: REQ_0015

**Description**: Verify resulting PWM is limited to range 0-255 (modified factor 0.1).

| Step # | Action | Expected result |
|--------|--------|-----------------|
| 1 | A1: Include configuration. | V1: No expected result. |
| 2 | A2: Execute steps 3 to 8 for motor with factor 0.1 | V2: No expected result. |
| 3 | A3: Call setVelocityPWM with PWM == -1 | V3: Returned value == 0.0. |
| 4 | A4: Call setVelocityPWM with PWM == 0 | V4: Returned value == 0.0. |
| 5 | A5: Call setVelocityPWM with PWM == 1 | V5: Returned value == 0.1. |
| 6 | A6: Call setVelocityPWM with PWM == 2549 | V6: Returned value == 254.9. |
| 7 | A7: Call setVelocityPWM with PWM == 2550 | V7: Returned value == 255.0. |
| 8 | A8: Call setVelocityPWM with PWM == 2551 | V8: Returned value == 255.0. |