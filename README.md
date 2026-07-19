# Autonomous Driving Robot Car

## Project Overview

This project aims to transform an existing car chassis into an autonomous driving robot model by integrating an ESP32 microcontroller. The goal is to develop a self-driving system capable of navigating its environment independently, leveraging modern embedded technologies and robust software engineering practices.

## Key Features

- **ESP32 Integration:** The ESP32 serves as the central control unit, handling sensor data, motor control, and communication.
- **Modular Design:** The system is designed for flexibility and scalability, allowing easy addition of new features and sensors.
- **Autonomous Navigation:** Algorithms enable the robot car to perceive its surroundings and make driving decisions without human intervention.

## Development Process

- **Requirements Management:** All functional and non-functional requirements are tracked and managed as GitHub Issues.
- **Custom Codebase:** The software developed is based on existing libraries. The logic, e.g. when to use which function, is developed in this project.
- **Testing & Quality Assurance:**  
  - **CMake** is used for build automation.
  - **Catch2** provides a framework for unit testing.
  - **gcov** and **gcovr** are utilized for code coverage analysis, ensuring reliability and maintainability.

## Getting Started

1. Clone the repository.
2. Get all needed parts. Please refer to the [BOM](BOM/BOM.md).
3. Build the robot car. Please refer to the [assembly information](assembly_information/assembly_information.md).
4. Compile the ino-file and flash it.
5. Enjoy.

## Getting Started For Developers
By following these steps, you can ensure that your development environment is set up correctly and that your code adheres to the specified requirements.

### Setting Up Development Environment

#### Prerequisites

1. **MSYS2**: Install MSYS2 from [msys2.org](https://www.msys2.org/).
2. **CMake**:
   - Install CMake in MSYS2 by running the following commands in your terminal:
     ```bash
     pacman -S mingw-w64-x86_64-cmake
     pacman -S mingw-w64-x86_64-ninja
     pacman -S mingw-w64-ucrt-x86_64-gcc
     ```
3. **gcovr**:
   - Create a virtual Python 3.13 environment and install `gcovr` using pip:
     ```bash
     python3 -m venv env
     source env/bin/activate  # On Windows use `env\Scripts\activate`
     pip install -r requirements.txt
     ```

#### Development Tasks
The following predefined tasks are part of of .vscode/tasks.json:
- **Clean tests build directory**
- **Build tests**: Builds the tests using CMakeLists.txt
- **Run tests**: Executes ./build/tests.exe
- **Run tests with coverage**: Builds and executes tests with coverage
- **Update coverage report**: Uses Python module `gcovr` to update coverage reports based on latest test results.
- **Run tests, update coverage report but DO NOT reopen results**: Cleans the test build directory, runs tests with coverage, updates coverage report
- **Compile for ESP32**: Uses `arduino-cli` to compile the code an ESP32 target
- **Upload to ESP32**: Uses `arduino-cli`to upload the compiled code to an ESP32. The task uses a fixed COM port `COM3`. Either ensure this matches your configuration or update the COM port properly.
- **Copy VERSION.h**: Copies `VERSION.h` from ./src/VERSION.h to ./build/esp32.esp32.esp32/VERSION.h
- **Compile and Upload for ESP32**: Executes both tasks in a sequence
- **Calculate firmware MD5**: Uses Powershell to calculate latest *.ino.bin's MD5 checksum.
- **Compile and calculate MD5**: Compiles the code for a ESP32 target, calculates its MD5 checksum and copies `VERSION.h`

#### Self-Developed Code Requirements

- **Requirements Linking**: Self-written code shall be based on requirements and linked in comments using the following format:
```markdown
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/1
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/2
```
- **Code coverage**:
  - Every code change shall be done within its own feature branch.
  - Pull requests shall have coverage report(s) attached showing 100% coverage.
  - Deviations shall be justified.

## License

This project is licensed under the terms specified in the repository.