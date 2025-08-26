# RFID_attendance_system
An Arduino-based attendance system that uses RFID cards to log presence based on a minimum time duration.

This project implements a smart attendance system using an Arduino, an MFRC522 RFID reader, and an LCD screen. Instead of simply logging a scan, this system requires a user to be "checked in" for a minimum duration before they are marked as present. A user scans their card to start a timer and scans it again to stop it. If the elapsed time meets the required threshold, they are marked "Present"; otherwise, they are marked "Absent".

Features:
This project's key features include its timer-based attendance logic, which prevents quick, invalid check-ins by ensuring a minimum duration is met. It provides clear user feedback through a 16x2 Liquid Crystal Display, showing status messages like "Timer started," "Marked present," or "Marked absent." The system also gives auditory feedback using a buzzer to confirm successful card scans. For debugging and logging, it sends detailed status updates, including the scanned card's unique ID and timer information, to the Serial Monitor.

Hardware Requirements:
To build this project, you will need an Arduino UNO or a compatible board, an MFRC522 RFID reader module with RFID cards/tags, and a 16x2 I2C Liquid Crystal Display. You will also need a 5V buzzer for sound notifications, a breadboard, and the necessary jumper wires to connect all the components.

Getting Started:
Follow these instructions to assemble and run the project.

1. Wiring:
The wiring for this project involves connecting the RFID module and the LCD to the Arduino. The MFRC522 module connects via the SPI protocol: SDA (SS) to Pin 10, SCK to Pin 13, MOSI to Pin 11, MISO to Pin 12, and RST to Pin 9. The LiquidCrystal LCD is connected to Arduino pins 2, 3, 4, 5, 6, and 7. Finally, the buzzer's positive pin is connected to analog pin A0, and its negative pin is connected to GND.

2. Installation:
The installation process begins by connecting the Arduino to your computer. Once connected, open the Arduino IDE and ensure you have installed the necessary libraries for MFRC522 and LiquidCrystal. Copy the entire rfidattendencesystem.ino sketch and paste it into the editor. From the Tools menu, select the correct Board and Port for your Arduino. Finally, click the Upload button to transfer the code to the board. You can then power the device and open the Serial Monitor to see the system status.

How It Works:
The system waits for an RFID card to be scanned. When a registered card is scanned for the first time, a timer is started, and the LCD and a buzzer confirm the action. The system then waits for the same card to be scanned a second time. Upon the second scan, the timer is stopped, and the total elapsed time is calculated. If this duration is greater than or equal to the preset threshold (10 seconds in the code), the user is marked as "Present". If the time is less than the threshold, they are marked as "Absent". The result is displayed on the LCD screen, and the system resets to wait for the next card scan.

License:
This project is open source. Feel free to use, modify, and distribute it.
