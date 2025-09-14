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

## License

This project is licensed under the terms specified in the repository.