**ID**: TEST_0011

**REQ**: REQ_0011

**Description**: Verify version information exists and format is correct.

| Step # | Action | Expected result |
|--------|--------|-----------------|
| 1 | A1: Include VERSION.h. | V1: No expected result. |
| 2 | A2: Verify VERSION exists and is of type const char *. | V2: Variable exists and is of type const char *. |
| 3 | A3: Split VERSION using "." as delimiter. | V3: Result is a list of three elements. |
| 4 | A4: Perform the following steps for each list element. | V4: No expected result. |
| 5 | A5: Verify element is a string representation of an integer. | V5: Element is a string representation of an integer. |
| 6 | A6: Verify element's integer value >= 0. | V6: element's integer value >= 0. |