**ID**: TEST_0017

**REQ**: REQ_0005

**Description**: Verify that the BOM table correctly lists all required components in the specified order.

| Step # | Action | Expected result |
|--------|--------|-----------------|
| 1 | A0: Read the BOM table from the repository. | V0: The table is successfully loaded with headings 'Unique part number', 'Part name', 'Amount', and 'Usage description'. |
| 2 | A1: Get the first row of the table. | V1: The first row contains the expected column headers in the correct order. |
| - | Repeat steps 3-6 for each subsequent row in the table | - |
| 3 | A2: Check if the row contains a unique part number. | V2: The row contains a unique part number. |
| 4 | A3: Check if the row contains a part name. | V3: The row contains a part name. |
| 5 | A4: Check if the row contains an amount set. | V4: The row contains an amount set. |
| 6 | A5: Check if the row contains a usage description. | V5: The row contains a usage description. |
| 7 | A6: Check that there was at least one entry in the table. | V6: The unique part number is greater than or equal to 1. |
