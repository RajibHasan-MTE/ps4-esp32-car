# PS4 BLE Car Controller 🚗🎮

This project allows you to control a car with a **PS4 controller** using an **ESP32** over Bluetooth (BLE).  
It supports **forward, backward, left, and right movement**, and includes a configurable **dead-zone offset** for smoother control.

---

## ✨ Features
- Connects PS4 Controller via BLE
- Forward / Backward control with speed threshold
- Left / Right steering
- Dead-zone offset for fine-tuning sensitivity
- Simple and lightweight Arduino code

---

## 🛠 Hardware Requirements
- ESP32 Development Board (e.g., ESP32 WROOM-32)
- Motor driver (e.g., L298N / L293D / BTS7960)
- DC motors with wheels
- PS4 Controller (DualShock 4)

---

## 📂 Code Example

```cpp
#include <PS4Controller.h>

int offset = 4;  // adjustable offset value

void loop() {
    int speed = PS4.LStickY();  // Example for forward/backward
    int turn  = PS4.LStickX();  // Example for left/right steering

    // Forward / Backward movement
    if(speed > (20 - offset)) forward();
    else if(speed < -(20 - offset)) backward();

    // Left / Right steering
    else if(turn > (20 - offset)) turnRight();
    else if(turn < -(20 - offset)) turnLeft();

    // Stop if inside dead zone
    else stopCar();
}


📚 Required Library

PS4-esp32 library
👉 Download here

To install:

Open Arduino IDE

Go to Sketch → Include Library → Add .ZIP Library

Select the downloaded PS4-esp32 library zip file


🚀 Getting Started

Clone this repository:

git clone https://github.com/YOUR_USERNAME/ps4-ble-car-controller.git


Open the ps4_car.ino file in Arduino IDE / PlatformIO

Install the required library

Upload code to ESP32

Pair your PS4 controller by pressing PS + Share buttons together

📄 License

This project is licensed under the MIT License – see the LICENSE
 file for details.

👨‍💻 Author

Rajib Hasan
Mechatronics & Embedded Systems Enthusiast


---

👉 Would you like me to also add a **PlatformIO configuration (`platformio.ini`)** for easy build and 