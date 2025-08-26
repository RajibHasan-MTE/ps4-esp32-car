#include <PS4Controller.h>

// Motor Pins (no ENA/ENB)
#define IN1 18
#define IN2 19
#define IN3 22    
int offset = 5;
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
    int speed = PS4.LStickY();  // Forward/Backward
    int turn  = PS4.LStickX();  // Left/Right
    /*
    // Forward / Backward
    if(speed > 20) forward();
    else if(speed < -20) backward();
    // Left / Right steering
    else if(turn > 20) turnRight();
    else if(turn < -20) turnLeft();
    else stopCar();
    */
    // Forward / Backward movement
    if(speed > (20 - offset)) forward();
    else if(speed < -(20 - offset)) backward();

    // Left / Right steering
    else if(turn > (20 - offset)) turnRight();
    else if(turn < -(20 - offset)) turnLeft();

    // Stop if inside dead zone
    else stopCar();
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
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
