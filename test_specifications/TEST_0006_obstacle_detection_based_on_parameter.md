**ID**: TEST_0006

**REQ**: REQ_0019

**Description**: Verify obstacle detection based on parameter.

| Step # | Action | Expected result |
|--------|--------|-----------------|
| 1 | A1: Include configuration. | V1: No expected result. |
| 2 | A2: Set obstacle distance to 500. | V2: Obstacle not detected. |
| 3 | A3: Set obstacle distance to 301. | V3: Obstacle not detected. |
| 4 | A4: Set obstacle distance to 299. | V4: Obstacle detected. |
| 5 | A5: Set obstacle distance to 300. | V5: Obstacle detected. |