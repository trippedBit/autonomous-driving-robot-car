"""
This script checks all Markdown files in the 'requirements' folder
and prints a list of files where the status is not "Finalized" or "Suspended".

Usage:
Run the script using Python: `python tools/list_pending_requirements.py`.

The script reads each Markdown file, searches for lines containing "Status: In specification",
and checks if the status is either "Finalized" or "Suspended". If a file has an incorrect
status, it's added to the list.

Output:
- The script prints the names of files with incorrect statuses.
- If all requirements have correct statuses, it outputs a message indicating so.
"""

import os

# Define the path to the requirements folder
FOLDER_PATH = 'requirements'

# Initialize an empty list to store filenames with incorrect statuses
incorrect_status_files = []

# Iterate over all files in the folder
for filename in os.listdir(FOLDER_PATH):
    # Construct the full file path
    file_path = os.path.join(FOLDER_PATH, filename)

    # Check if the file is a text file (assuming markdown format)
    if filename.endswith('.md'):
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()

            # Find the line containing the status
            for line in content.split('\n'):
                if '**Status**: In specification' in line:
                    # Check the status of the requirement
                    parts = line.split(':')
                    if len(parts) > 1:
                        status = parts[1].strip()

                        # If the status is not "Finalized" or "Suspended", add to the list
                        if status not in ['Finalized', 'Suspended']:
                            incorrect_status_files.append((filename, status))
                            break

# Print the list of files with incorrect statuses
if incorrect_status_files:
    print("Pending requirements or with invalid status:")
    for entry in incorrect_status_files:
        print(f"- {entry[0]}: {entry[1]}")
else:
    print("All requirements have correct statuses.")
