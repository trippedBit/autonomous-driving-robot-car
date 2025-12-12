**ID**: TEST_0001

**REQ**: REQ_0001

**Description**: Verify motor direction switches from STOP state to another state earliest 10s and latest 12 seconds after boot.

| Step # | Action | Expected result |
|--------|--------|-----------------|
| 1 | Verify motor direction after boot. | V0: Direction is STOP. |
| 2 | A1: Set motor direction FORWARD. | V1: Motor direction is still STOP. |
| 3 | A2: Wait until 9.900ms after boot. | V2: Motor direction is still STOP. |
| 4 | A3: Wait until 10.000ms after boot. | V3: Motor direction is still STOP. |
| 5 | A4: Set motor direction FORWARD. | V4: Motor direction is FORWARD. |