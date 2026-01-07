# Bluetooth-Smart-Door-Lock
Arduino-based smart door lock controlled via Bluetooth with LCD feedback, servo lock, and security alarm.

A secure smart door lock system built with Arduino Uno, controlled via Bluetooth (HC-05/HC-06 module). Features include:
- Servo motor for locking/unlocking
- 16x2 LCD display for status feedback
- LED indicators (Red: Locked, Green: Unlocked)
- Buzzer for beeps and alarm on failed attempts
- Security: Locks automatically after 10 seconds, alarm after 3 wrong attempts

## Hardware Components
- Arduino Uno
- SG90 Servo Motor
- HC-05 or HC-06 Bluetooth Module
- 16x2 LCD Display (with I2C optional for fewer pins)
- Red & Green LEDs
- Buzzer
- Jumper wires, breadboard, power supply

## Wiring Diagram
## Circuit Photos
<!-- Add real photos of your setup -->
<!-- Add your Fritzing diagram or photo here -->
![Wiring Diagram](schematics/wiring.png)
<img width="64" height="48" alt="image" src="https://github.com/user-attachments/assets/711f36ad-36b2-4300-8aa3-1558755dbd14" />
<img width="29" height="64" alt="image" src="https://github.com/user-attachments/assets/cef1a076-a337-4711-bce2-0bb9a83e30ca" />
<img width="46" height="64" alt="image" src="https://github.com/user-attachments/assets/4cddd867-eb9d-4301-84b1-000c16b86a6b" />

## How It Works
- Send an integer value via Bluetooth (e.g., from a phone app like "Bluetooth Serial Terminal").
- Threshold value: ≥65 unlocks the door.
- Wrong value: Increments failed attempts, beeps.
- After 3 failures: Triggers loud alarm.
- Auto-relocks after 10-second countdown.

## Installation & Usage
1. Wire the components as per the diagram.
2. Upload the code `Bluetooth_Smart_Lock.ino` using Arduino IDE.
3. Pair your phone with the HC-05 (default password: 1234 or 0000).
4. Use a serial Bluetooth app to send numbers (try 65 to unlock).

## Code Explanation
- Uses `SoftwareSerial` for Bluetooth communication.
- `Servo` library controls the lock mechanism.
- `LiquidCrystal` for display messages.
- Custom functions for lock/unlock with countdown and alarm.

## Future Improvements
- Add keypad or RFID for multiple auth methods.
- Integrate with mobile app (MIT App Inventor).
- Add WiFi (ESP8266) for remote control.

## License
MIT License — feel free to use and modify!

Made for academic project by WeiXiang, 2025.
