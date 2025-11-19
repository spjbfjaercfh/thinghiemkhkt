#include <esp_now.h>
#include <WiFi.h>


// MAC broadcast
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
Serial.print("Gửi broadcast → trạng thái: ");
Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Thành công" : "Thất bại");
}


void setup() {
Serial.begin(115200);
WiFi.mode(WIFI_STA);
Serial.print("MAC Sender: ");
Serial.println(WiFi.macAddress());


if (esp_now_init() != ESP_OK) {
Serial.println("Lỗi khởi tạo ESP-NOW");
return;
}


esp_now_register_send_cb(OnDataSent);


// Khai báo peer broadcast
esp_now_peer_info_t peerInfo = {};
memcpy(peerInfo.peer_addr, broadcastAddress, 6);
peerInfo.channel = 0;
peerInfo.encrypt = false;


if (esp_now_add_peer(&peerInfo) != ESP_OK) {
Serial.println("Thêm peer broadcast thất bại");
return;
}
}


void loop() {
const char *msg = "Hello all ESP32";
esp_now_send(broadcastAddress, (uint8_t *)msg, strlen(msg));
delay(1000);
}