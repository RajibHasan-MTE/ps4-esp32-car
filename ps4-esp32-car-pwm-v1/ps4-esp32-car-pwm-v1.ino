#include <PS4Controller.h>

// Motor Pins
#define IN1 18
#define IN2 19
#define IN3 22    
#define IN4 23

const int threshold = 20; // deadzone threshold

// PWM channels for ESP32
const int pwmFreq = 1000;
const int pwmResolution = 8; // 0-255
const int ch1 = 0;
const int ch2 = 1;
const int ch3 = 2;
const int ch4 = 3;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Setup motor pins for PWM
  ledcSetup(ch1, pwmFreq, pwmResolution);
  ledcSetup(ch2, pwmFreq, pwmResolution);
  ledcSetup(ch3, pwmFreq, pwmResolution);
  ledcSetup(ch4, pwmFreq, pwmResolution);

  ledcAttachPin(IN1, ch1);
  ledcAttachPin(IN2, ch2);
  ledcAttachPin(IN3, ch3);
  ledcAttachPin(IN4, ch4);

  stopCar();

  PS4.begin();
  Serial.println("PS4 Controller Ready");
}

void loop() {
  if(!PS4.isConnected()) {
    static unsigned long lastAttempt = 0;
    if(millis() - lastAttempt > 2000) {
      Serial.println("Trying to reconnect PS4...");
      PS4.begin();
      lastAttempt = millis();
    }
    digitalWrite(LED_BUILTIN, millis() % 500 < 250);
    stopCar();
    return;
  }

  digitalWrite(LED_BUILTIN, HIGH);

  // Read joystick values
  int speed = PS4.LStickY(); // -127 to 127
  int turn  = PS4.LStickX(); // -127 to 127
  if(abs(speed) < threshold) speed = 0;
  if(abs(turn) < threshold) turn = 0;

  int pwmSpeed = map(abs(speed), 0, 128, 0, 255);
  int pwmTurn  = map(abs(turn), 0, 128, 0, 255);
  /* 
  Serial.print("Speed: ");
  Serial.print(pwmSpeed);
  Serial.print("  trun: ");
  Serial.println(pwmTurn);
  */
  
  // Arrow button overrides joystick
  if(PS4.Up()) forward(255);
  else if(PS4.Down()) backward(255);
  else if(PS4.Left()) turnLeft(255);
  else if(PS4.Right()) turnRight(255);
  else {
    // Joystick movement if no arrow key pressed
    if(speed > 0) forward(pwmSpeed);
    else if(speed < 0) backward(pwmSpeed);
    else if(turn > 0) turnRight(pwmTurn);
    else if(turn < 0) turnLeft(pwmTurn);
    else stopCar();
  }

  delay(5);
}

// Motor control with PWM
void forward(int pwm){
  ledcWrite(ch1, pwm); ledcWrite(ch2, 0);
  ledcWrite(ch3, pwm); ledcWrite(ch4, 0);
}

void backward(int pwm){
  ledcWrite(ch1, 0); ledcWrite(ch2, pwm);
  ledcWrite(ch3, 0); ledcWrite(ch4, pwm);
}

void turnLeft(int pwm){
  ledcWrite(ch1, pwm); ledcWrite(ch2, 0);
  ledcWrite(ch3, 0);   ledcWrite(ch4, pwm);
}

void turnRight(int pwm){
  ledcWrite(ch1, 0);   ledcWrite(ch2, pwm);
  ledcWrite(ch3, pwm); ledcWrite(ch4, 0);
}

void stopCar(){
  ledcWrite(ch1, 0); ledcWrite(ch2, 0);
  ledcWrite(ch3, 0); ledcWrite(ch4, 0);
}
