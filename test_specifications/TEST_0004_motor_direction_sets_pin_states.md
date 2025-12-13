**ID**: TEST_0004

**REQ**: REQ_0002

**Description**: Verify motor directions sets proper direction pin states.

| Step # | Action | Expected result |
|--------|--------|-----------------|
| 1 | A1: Include configuration. | V1: No expected result. |
| 2 | A2: Perform following steps for motor 1 and motor 2. | V2: No expected result. |
| 3 | A3: Set motor direction INVALID. | V3: Motor's FORWARD pin state is \<tbd\>.<br>Motor's BACKWARD pin state is \<tbd\>. |
| 4 | A4: Set motor direction ERROR. | V4: Motor's FORWARD pin state is \<tbd\>.<br>Motor's BACKWARD pin state is \<tbd\>. |
| 5 | A5: Set motor direction STOP. | V5: Motor's FORWARD pin state is \<tbd\>.<br>Motor's BACKWARD pin state is \<tbd\>. |
| 6 | A6: Set motor direction FORWARD. | V6: Motor's FORWARD pin state is HIGH.<br>Motor's BACKWARD pin state is LOW. |
| 7 | A7: Set motor direction BACKWARD. | V7: Motor's FORWARD pin state is LOW.<br>Motor's BACKWARD pin state is HIGH. |