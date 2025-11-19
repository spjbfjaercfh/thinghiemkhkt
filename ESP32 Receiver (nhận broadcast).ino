#include <WiFi.h>
#include <esp_now.h>


// Wi-Fi router
const char* ssid = "YourWiFi";
const char* pass = "YourPassword";


// MAC peer ESP-NOW
uint8_t peerMAC[] = {0x24, 0x6F, 0x28, 0x11, 0x22, 0x33};


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
Serial.print("ESP-NOW gửi → ");
Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Thành công" : "Thất bại");
}


void setup() {
Serial.begin(115200);


// 1. Kết nối Wi-Fi
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, pass);
Serial.print("Connecting to WiFi...");
while (WiFi.status() != WL_CONNECTED) {
delay(300);
Serial.print(".");
}
Serial.println(" Connected!");


// 2. Khởi tạo ESP-NOW
if (esp_now_init() != ESP_OK) {
Serial.println("Lỗi khởi tạo ESP-NOW");
return;
}


esp_now_register_send_cb(OnDataSent);


// 3. Khai báo peer
esp_now_peer_info_t peerInfo = {};
memcpy(peerInfo.peer_addr, peerMAC, 6);
peerInfo.channel = WiFi.channel(); // bắt buộc dùng cùng channel với router
peerInfo.encrypt = false;


esp_now_add_peer(&peerInfo);
}


void loop() {
const char *msg = "DATA via ESP-NOW";
esp_now_send(peerMAC, (uint8_t*)msg, strlen(msg));


delay(1000);
}