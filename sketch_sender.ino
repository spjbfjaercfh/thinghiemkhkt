#include <esp_now.h>
#include <WiFi.h>


// Địa chỉ MAC của ESP32 Receiver (thay bằng MAC thật khi chạy)
uint8_t receiverMAC[] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC};


// Hàm callback khi gửi thành công hoặc thất bại
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
Serial.print("Gửi đến: ");
for (int i = 0; i < 6; i++) Serial.printf("%02X", mac_addr[i]);
Serial.print(" → trạng thái: ");
Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Thành công" : "Thất bại");
}


void setup() {
Serial.begin(115200);


WiFi.mode(WIFI_STA); // Bắt buộc để ESP‑NOW hoạt động
Serial.println(WiFi.macAddress());


if (esp_now_init() != ESP_OK) {
Serial.println("Lỗi khởi tạo ESP-NOW");
return;
}


esp_now_register_send_cb(OnDataSent);


// Khai báo peer
esp_now_peer_info_t peerInfo = {};
memcpy(peerInfo.peer_addr, receiverMAC, 6);
peerInfo.channel = 0;
peerInfo.encrypt = false;


if (esp_now_add_peer(&peerInfo) != ESP_OK) {
Serial.println("Thêm peer thất bại");
return;
}
}


void loop() {
const char *msg = "Hello ESP-NOW";
esp_now_send(receiverMAC, (uint8_t *)msg, strlen(msg));
delay(1000);
}