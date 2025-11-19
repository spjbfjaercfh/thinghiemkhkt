#include <esp_now.h>
#include <WiFi.h>


uint8_t espA_MAC[] = {0x24, 0x6F, 0x28, 0x11, 0x22, 0x33}; // Điền MAC của ESP32 A


// Callback khi nhận dữ liệu từ A
void OnDataRecv(const uint8_t *mac, const uint8_t *data, int len) {
Serial.print("Nhận từ A: ");
for (int i = 0; i < len; i++) Serial.print((char)data[i]);
Serial.println();


// Gửi ACK lại cho A
const char *ack = "Received";
esp_now_send(espA_MAC, (uint8_t *)ack, strlen(ack));
}


// Callback gửi ACK
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
Serial.print("ACK gửi đến A → ");
Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Thành công" : "Thất bại");
}


void setup() {
Serial.begin(115200);
WiFi.mode(WIFI_STA);
Serial.println(WiFi.macAddress());


if (esp_now_init() != ESP_OK) {
Serial.println("Lỗi khởi tạo ESP-NOW");
return;
}


esp_now_register_recv_cb(OnDataRecv);
esp_now_register_send_cb(OnDataSent);


esp_now_peer_info_t peerInfo = {};
memcpy(peerInfo.peer_addr, espA_MAC, 6);
peerInfo.channel = 0;
peerInfo.encrypt = false;


if (esp_now_add_peer(&peerInfo) != ESP_OK) {
Serial.println("Thêm peer thất bại");
return;
}
}


void loop() {}