# 🚗🤏 Bluetooth Gripper Car

A small car that drives around and grabs things. 

https://github.com/user-attachments/assets/9a33a207-14f3-4bfd-b49c-0c5b8e3c3656

## What it does
- **Drives** forward, backward, left, and right, controlled from your phone over Bluetooth
- **Grabs stuff** with a servo-powered gripper at the front

## How it works
1. You press a button on the app
2. The app sends a command over Bluetooth
3. The ESP32 receives it and tells the motors or gripper what to do

## Hardware
- ESP32 
- L298N motor driver 
- 2 DC motors + wheels + 1 free wheel
- 1 servo for the gripper 
- 2 x 3.7V Batteries 

| Button | Action |
|--------|--------|
| ⬆️ | Forward |
| ⬇️ | Backward |
| ⬅️ | Left |
| ➡️ | Right |
| ✊ | Grip |
| ✋ | Release |

## Future upgrades
- Add a current sensor to the servo to detect when it grips an object
- Use a PCB to neaten the wiring

---
Built by Anton, Faiz, Nico🤖
