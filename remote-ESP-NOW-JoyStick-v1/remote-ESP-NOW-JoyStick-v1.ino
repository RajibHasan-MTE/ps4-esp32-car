#include <esp_now.h>
#include <WiFi.h>

// Structure to send joystick values
typedef struct {
  int x;
  int y;
} joystick_data;

joystick_data jsData;

// 🔹 Replace with your car ESP32's MAC address
uint8_t carAddress[] = {0xC0, 0x5D, 0x89, 0xAF, 0xD7, 0xDA};

void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);

  // Init WiFi as STA
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnSent);

  // Register peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, carAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Read joystick on safe ADC1 pins
  jsData.x = analogRead(34);  
  jsData.y = analogRead(35);

  // Send joystick data
  esp_now_send(carAddress, (uint8_t *) &jsData, sizeof(jsData));

  delay(50); // send every 50ms
}
