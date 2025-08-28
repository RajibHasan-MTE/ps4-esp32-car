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


void forward(){
  Serial.println("Forward");
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  
}

void backward(){
  Serial.println("Backward");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);

  
    
}

void right(){
  Serial.println("Right");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void left(){
  Serial.println("Left");
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}


void stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveCar(int x, int y) {
  int center = 1601;   // midpoint for 12-bit ADC
  int deadzone = 500;  // tolerance
  Serial.print("X: ");
  Serial.print(x);
  Serial.print("Y: ");
  Serial.println(y);
  

  // Stop by default
  stop();

  if (y > center + deadzone) { 
    right();
  } 
  if (y < center - deadzone) { 
    left();
  } 

 if (x > center + deadzone) { 
    forward();
    
  } 
  else if (x < center - deadzone) { 
    backward();
  }
}

// ✅ Updated callback signature for ESP32 Arduino core v3.x
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  if (len == sizeof(jsData)) {
    memcpy(&jsData, incomingData, sizeof(jsData));
    moveCar(jsData.x, jsData.y);
    delay(50);
  }
}

void setup() {
  Serial.begin(9600);

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
  delay(10);
}

void loop() {
  // Nothing, control is via callback
}
