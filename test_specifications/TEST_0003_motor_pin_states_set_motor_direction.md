**ID**: TEST_0003

**REQ**: REQ_0002

**Description**: Verify motor pin states set proper motor direction.

| Step # | Action | Expected result |
|--------|--------|-----------------|
| 1 | A1: Include configuration. | V1: No expected result. |
| 2 | A2: Perform following steps for motor 1 and motor 2. | V2: No expected result. |
| 3 | A3: Set motor's FORWARD pin LOW.<br>Set motor's BACKWARD pin LOW | V3: Motor direction is \<tbd\>. |
| 4 | A4: Set motor's FORWARD pin HIGH.<br>Set motor's BACKWARD pin LOW | V4: Motor direction is FORWARD. |
| 5 | A5: Set motor's FORWARD pin LOW.<br>Set motor's BACKWARD pin HIGH | V5: Motor direction is BACKWARD. |
| 6 | A6: Set motor's FORWARD pin HIGH.<br>Set motor's BACKWARD pin HIGH | V6: Motor direction is \<tbd\>. |