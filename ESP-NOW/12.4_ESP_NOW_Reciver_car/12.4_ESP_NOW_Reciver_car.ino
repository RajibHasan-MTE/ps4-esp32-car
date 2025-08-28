#include <esp_now.h>
#include <WiFi.h>

// Motor pins
#define IN1 18
#define IN2 19
#define IN3 22
#define IN4 23

typedef struct {
  int x;
  int y;
} joystick_data;

joystick_data jsData;

void moveCar(int x, int y) {
  int center = 2048; // midpoint for 12-bit ADC
  int deadzone = 300; // tolerance

  // Stop by default
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  if (y > center + deadzone) { 
    // Forward
    Serial.println("Forward" );
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } 
  else if (y < center - deadzone) { 
    // Backward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } 
  else if (x > center + deadzone) { 
    // Right
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } 
  else if (x < center - deadzone) { 
    // Left
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&jsData, incomingData, sizeof(jsData));
  moveCar(jsData.x, jsData.y);
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing, control is via callback
}