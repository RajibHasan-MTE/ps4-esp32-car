#include "WiFi.h"
// 24:6F:28:94:EF:94
void setup(){

  Serial.begin(115200);

  //put ESP32 into station mode
  WiFi.mode(WIFI_MODE_STA);
  delay(100);
  
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop(){}