**ID**: TEST_0009

**REQ**: REQ_0015

**Description**: Verify resulting PWM is limited to range 0-255 (default factors).

| Step # | Action | Expected result |
|--------|--------|-----------------|
| 1 | A1: Include configuration. | V1: No expected result. |
| 2 | A2: Execute steps 3 to 8 for motor with factor 0.9 | V2: No expected result. |
| 3 | A3: Call setVelocityPWM with PWM == -1 | V3: Returned value == 0.0. |
| 4 | A4: Call setVelocityPWM with PWM == 0 | V4: Returned value == 0.0. |
| 5 | A5: Call setVelocityPWM with PWM == 1 | V5: Returned value == 0.9. |
| 6 | A6: Call setVelocityPWM with PWM == 283 | V6: Returned value == 254.7. |
| 7 | A7: Call setVelocityPWM with PWM == 284 | V7: Returned value == 255.0. |