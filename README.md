# Streetlight Control System - README
This repository contains the code for a streetlight control system that utilizes various sensors and conditions to intelligently manage streetlight illumination. The system incorporates an Arduino board, ultrasonic distance sensors, a light-dependent resistor (LDR), and passive infrared (PIR) motion sensors.

## Team Members
 
## Table of Contents
Description
Setup
Usage
Contributions
License

### Description
The purpose of this project is to create an energy-efficient streetlight control system that adjusts the illumination based on the presence of pedestrians, ambient light conditions, and the time of day. The system uses ultrasonic distance sensors, PIR motion sensors, and an LDR to determine when to turn on and off the streetlights.

### Setup
To set up the system, follow these steps:

Connect the required hardware components to the Arduino board as specified in the pin configuration section of the code.
Upload the provided code (streetlight_control.ino) to the Arduino board using the Arduino IDE or a compatible programming tool.
Ensure that the required libraries (Wire.h and RTClib.h) are properly installed in the Arduino IDE.
Adjust any configuration parameters in the code, such as the ultrasonic threshold and the LDR reading for turning on the lights.
Connect the Arduino board to a power source.

### Usage
The system operates as follows:

During daylight (LDR reading below a certain threshold), all streetlights are turned off regardless of motion or distance sensor readings.
After sunset (LDR reading above a certain threshold), the streetlights will turn on if:
The current time is after 10:00 PM.
Motion is detected by any of the PIR sensors.
The ultrasonic distance sensors detect an object within a specific range.
The system ensures energy efficiency by considering ambient light conditions and the presence of pedestrians before illuminating the streetlights.

### Contributions
Contributions to this project are welcome. If you want to contribute, please follow these steps:

Fork this repository to your own GitHub account.
Clone the forked repository to your local machine.
Create a new branch for your feature or bug fix.
Make your changes and commit them with clear commit messages.
Push your changes to your forked repository.
Submit a pull request to the main branch of this repository.

### License
This project is licensed under the MIT License. You are free to use, modify, and distribute the code as long as the original license terms are included. See the LICENSE file for more details.
