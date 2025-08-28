#include <esp_now.h>
#include <WiFi.h>

// Motor direction pins (safe for ESP-NOW)
#define IN1 18
#define IN2 19
#define IN3 22
#define IN4 23

// Motor enable pins (PWM speed control, safe)
#define ENA 25   // Left motor enable
#define ENB 26   // Right motor enable

int speed = 0;
int center = 90;     // midpoint for 12-bit ADC
int deadzone = 20;    // joystick tolerance

int centerX = 90;  // joystick center X
int centerY = 90;  // joystick center Y
int maxVal = 235;  // joystick max
int minVal = 0;    // joystick min

typedef struct {
  int x;
  int y;
} joystick_data;

joystick_data jsData;

void stop(){
  speed = 0;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(0, 0);
  ledcWrite(1, 0);

}

void forward(int speed){
  Serial.println("forward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(0, speed);
  ledcWrite(1, speed);
}

void backward(int speed){
  Serial.println("backward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //digitalWrite(ENA, HIGH);
  //digitalWrite(ENB, HIGH);
  ledcWrite(0, speed);
  ledcWrite(1, speed);
}

void turn_right(int speed){
  Serial.println("Right");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(0, speed);
  ledcWrite(1, speed);
}

void turn_left(int speed){
  Serial.println("Left");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(0, speed);
  ledcWrite(1, speed);
}

void moveCar(int x, int y) {
  // Stop by default
  stop();
  if (y > center + deadzone) { 
    // Forward
    speed = map(jsData.y, centerY, maxVal, 0, 255);  // Forward
    forward(speed);
  } 
  else if (y < center - deadzone) { 
    // Backward
    speed = map(jsData.y, centerY, minVal, 0, 255);  // Backward
    backward(speed);
  }

  else if (x > center + deadzone) { 
    // Right turn
    speed = map(jsData.x, centerX, maxVal, 0, 130);  // Right
    turn_right(speed);
  } 
  else if (x < center - deadzone) { 
    // Left turn
    speed = map(jsData.x, centerX, minVal, 0, 130);  // Left
    turn_left(speed);
  } 

}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&jsData, incomingData, sizeof(jsData));
  moveCar(jsData.x, jsData.y);
  Serial.print("X:");
  Serial.print(jsData.x);
  Serial.print(" Y:");
  Serial.print(jsData.y);
  Serial.print(" Speed:");
  Serial.print(speed);
  Serial.println();
  
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Setup PWM for ENA and ENB
  ledcAttachPin(ENA, 0);
  ledcSetup(0, 1000, 8);  // channel 0, 1kHz, 8-bit

  ledcAttachPin(ENB, 1);
  ledcSetup(1, 1000, 8);  // channel 1, 1kHz, 8-bit

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing here, joystick data handled in callback
}
