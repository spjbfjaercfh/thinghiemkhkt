#include <esp_now.h>
#include <WiFi.h>


void OnDataRecv(const uint8_t *mac, const uint8_t *data, int len) {
Serial.print("Nhận từ MAC: ");
for (int i = 0; i < 6; i++) Serial.printf("%02X", mac[i]);


Serial.print(" | Dữ liệu: ");
for (int i = 0; i < len; i++) Serial.print((char)data[i]);
Serial.println();
}


void setup() {
Serial.begin(115200);
WiFi.mode(WIFI_STA);
Serial.print("MAC Receiver: ");
Serial.println(WiFi.macAddress());


if (esp_now_init() != ESP_OK) {
Serial.println("Lỗi khởi tạo ESP-NOW");
return;
}


esp_now_register_recv_cb(OnDataRecv);
}


void loop() {}