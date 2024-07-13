# ESP32_PIR_Buzzer_LED_WebServer

This project demonstrates the integration of an ESP32 with a PIR sensor, buzzer, and LED, coupled with a web server for real-time motion detection monitoring. The PIR sensor detects motion and triggers the buzzer and LED to alert. The ESP32 also hosts a web server, providing a user interface to display the motion detection status. This setup is ideal for basic security or automation systems.

## Key Features
- **PIR Motion Sensor**: Detects movement and triggers alerts.
- **Buzzer**: Provides an audible alert when motion is detected.
- **LED**: Provides a visual alert when motion is detected.
- **Web Server**: Hosted on the ESP32 to display real-time motion detection status.

## Components Used
- ESP32
- PIR Sensor
- Buzzer
- LED
- Resistors

## Schematic
### LED Connection:
1. Connect the positive leg (anode) of the LED to pin 25 on the ESP32.
2. Connect the negative leg (cathode) of the LED to a 220-ohm resistor.
3. Connect the other end of the resistor to the ground (GND) on the ESP32.

## Setup Instructions
1. Connect the PIR sensor to pin 33 of the ESP32.
2. Connect the buzzer to pin 27 of the ESP32.
3. Connect the LED (with a 220-ohm resistor) to pin 25 of the ESP32.
4. Upload the provided Arduino sketch to the ESP32.
5. Connect to the ESP32's WiFi access point named `ESP32_AP`.
6. Access the web server at the displayed IP address in your serial monitor.

## Usage
When motion is detected by the PIR sensor:
- The buzzer will sound for 1 second.
- The LED will light up for 3 seconds.
- The web server will update to display the motion detection status, refreshing every 5 seconds.
