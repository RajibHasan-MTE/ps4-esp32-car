#include <PS4Controller.h>

// Motor Pins (no ENA/ENB)
#define IN1 18
#define IN2 19
#define IN3 22    
#define IN4 23
int offset = 10;
int threshold = 50;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  // Motor pins as output
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  // Initialize PS4 Controller (replace with your ESP32 MAC or leave blank)
  //PS4.begin("xx:xx:xx:xx:xx:xx");
  PS4.begin();
  Serial.println("PS4 Controller Ready");
  delay(1000);
  
}

void loop() {
  if(PS4.isConnected()){
    digitalWrite(LED_BUILTIN, HIGH);

    int speed = PS4.LStickY();
    int turn  = PS4.LStickX();
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.print("  trun: ");
    Serial.println(turn);


    if(abs(speed) < threshold) speed = 0;
    if(abs(turn) < threshold) turn = 0;
    
    if(speed > threshold) forward();
    else if(speed < -threshold) backward();
    else if(turn > threshold) turnRight();
    else if(turn < -threshold) turnLeft();
    else stopCar();
  } 
  else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("PS4 Disconnected! Reconnecting...");
    PS4.begin(); // Try to reconnect
    delay(1000);
  }

  delay(5);
}


// Motor Control Functions
void forward(){
  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW);
  Serial.println("Forward");

}

void backward(){
  digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH);
  Serial.println("backward");
}

void turnLeft(){
  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH);
}

void turnRight(){
  digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW);
}

void stopCar(){
  digitalWrite(IN1,LOW); digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW); digitalWrite(IN4,LOW);
}
