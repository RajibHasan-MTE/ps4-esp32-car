ESP32 PS4 RC Car 🚗🎮

Control an RC Car with an ESP32 using a PS4 (DualShock 4) controller over Bluetooth (BLE). This project is beginner-friendly and explains everything step-by-step, from library setup to pairing and coding.

🔧 Hardware Requirements

ESP32 Development Board (WROOM-32 or similar)

L298N / L293D motor driver module

2x DC motors with wheels (or a 4-wheel chassis)

PS4 (DualShock 4) wireless controller

Power supply (Li-ion battery / 9V battery pack)

Jumper wires

⚡ Wiring (ESP32 → Motor Driver)
#define IN1 18   // Motor A forward
#define IN2 19   // Motor A backward
#define IN3 22   // Motor B forward
#define IN4 23   // Motor B backward

ESP32 Pin	Motor Driver Pin
18	IN1
19	IN2
22	IN3
23	IN4
5V	VCC
GND	GND

(Adjust ENA/ENB jumpers depending on your driver board – most modules keep them permanently enabled.)

📦 Library Installation

1. Download the ps4controller library (ps4controller.zip) from this repository.

2. Open Arduino IDE → Sketch → Include Library → Add .ZIP Library.

3. Select the downloaded ps4controller.zip.

4. The library is now installed.

🎮 PS4 Controller Setup (Pairing with ESP32)

1. Get ESP32 MAC Address (Bluetooth)

- Upload the PS4_get_MAC.ino example (included in the ps4controller library).

- Open Serial Monitor → Note down the ESP32 Bluetooth MAC Address (e.g., 01:02:03:04:05:06).

2. Pair PS4 Controller with ESP32

-Connect your PS4 controller to a PC (Windows/Linux) via USB.

- Use a tool like SixaxisPairTool (Windows) or sixpair (Linux).

- Enter the ESP32 MAC Address you copied earlier.

- Disconnect the USB.

3. Connect wirelessly

- Press the PS button on the PS4 controller.

- The controller will now connect directly to your ESP32.

🚀 Example Code (Minimal RC Car Control)
#include <ps4controller.h>

#define IN1 18
#define IN2 19
#define IN3 22
#define IN4 23

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);
  PS4.begin("01:02:03:04:05:06"); // Replace with your ESP32 MAC Address
  Serial.println("Ready to connect PS4 controller...");
}

void loop() {
  if (PS4.isConnected()) {
    if (PS4.LStickY() < -50) {        // Forward
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (PS4.LStickY() > 50) {  // Backward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else if (PS4.LStickX() < -50) { // Left
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (PS4.LStickX() > 50) {  // Right
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else {                          // Stop
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
  }
}

📖 How It Works

ESP32 acts as a Bluetooth host and connects to the PS4 controller.

Joystick values (LStickX, LStickY) are read continuously.

Depending on stick movement → corresponding motor pins are set HIGH/LOW.

Simple logic: Forward, Backward, Left, Right, Stop.

✅ Next Improvements

Add PWM motor speed control.

Map buttons for headlights, horn, or extra features.

Use analog triggers (L2/R2) for speed throttle.

Upgrade to 4WD chassis with suspension.

⚡ Enjoy your PS4 ESP32 RC Car Project! 🚗