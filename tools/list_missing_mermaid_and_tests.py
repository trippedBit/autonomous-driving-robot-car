"""
This script checks all Markdown files in the 'requirements' folder
and verifies that each requirement is properly covered by its corresponding
mermaid diagram and test file. It skips non-functional requirements.

The script performs the following steps:
1. Iterates over all files in the 'requirements' folder.
2. Checks if a file name matches the pattern "REQ_abcd_....md", where abcd is a four-digit number.
3. Skips non-functional requirements identified by '**Type**: Non-Functional'.
4. Extracts the requirement number from the filename.
5. Constructs the paths for the mermaid diagram and test files.
6. Checks if the mermaid file exists and contains "**REQ**: REQ_abcd".
7. Checks if any test file contains "**REQ**: REQ_abcd" on line 3.
8. Determines the reason for not covering the requirement and prints a list of missing requirements.

Usage:
- Ensure that the 'requirements' folder contains files with filenames starting with "REQ_abcd" and ending with ".md".
- Ensure that the 'test_specifications' folder contains files starting with "TEST_", followed by any four-digit number, and ending with ".md".

This script helps identify requirements that are missing their corresponding mermaid diagrams or tests.
"""

import os

# Define the paths to the requirements and test folders
REQUIREMENTS_PATH = 'requirements'
TEST_SPECIFICATIONS_PATH = 'test_specifications'

# Initialize an empty list to store files where requirements are not properly covered
missing_requirements = []

# Iterate over all files in the requirements folder
for filename in os.listdir(REQUIREMENTS_PATH):
    # Check if the file name matches the pattern "REQ_abcd_more_text.md"
    if filename.startswith('REQ_') and filename.endswith('.md'):
        with open(os.path.join(REQUIREMENTS_PATH, filename), 'r', encoding='utf-8') as file:
            content = file.read()
            if '**Type**: Non-Functional' in content:
                # Skip non-functional requirements
                continue

        requirement_number = filename.split('.')[0][4:8]

        # Construct the paths for the mermaid diagram and test files
        mermaid_path = os.path.join(TEST_SPECIFICATIONS_PATH, f"REQ_{requirement_number}_mermaid.md")
        test_path = os.path.join(TEST_SPECIFICATIONS_PATH, f"test_{requirement_number}.md")

        # Check if the mermaid file exists and contains "**REQ**: REQ_abcd"
        mermaid_present = False
        if os.path.exists(mermaid_path):
            with open(mermaid_path, 'r', encoding='utf-8') as mermaid_file:
                lines = mermaid_file.readlines()
                if len(lines) >= 1 and '**REQ**: REQ_' + requirement_number in lines[0].strip():
                    mermaid_present = True

        # Check if the test file exists and contains "**REQ**: REQ_abcd" on line 3
        test_present = False
        for test_filenname in os.listdir(TEST_SPECIFICATIONS_PATH):
            if test_filenname.startswith("TEST_") and test_filenname.endswith('.md'):
                with open(os.path.join(TEST_SPECIFICATIONS_PATH, test_filenname), 'r', encoding='utf-8') as test_file:
                    lines = test_file.readlines()
                    if len(lines) >= 3 and '**REQ**: REQ_' + requirement_number in lines[2].strip():
                        test_present = True
                        break

        # Determine the reason for not covering the requirement
        if not mermaid_present and not test_present:
            missing_requirements.append(f"- {filename}\n  - no mermaid or test found")
        elif not mermaid_present:
            missing_requirements.append(f"- {filename}\n  - no mermaid with matching name found")
        elif not test_present:
            missing_requirements.append(f"- {filename}\n  - mermaid with matching name found, but requirement not mentioned in line 1")

# Print the list of requirements that are not properly covered
if missing_requirements:
    print("\nRequirements that are not properly covered:")
    for req in missing_requirements:
        print(req)
else:
    print("All requirements are properly covered.")
