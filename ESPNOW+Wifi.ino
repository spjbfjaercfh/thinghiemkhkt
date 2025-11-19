#include <WiFi.h>
#include <esp_now.h>


uint8_t peerMAC[] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC};
uint8_t lmk[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };


void setup() {
Serial.begin(115200);
WiFi.mode(WIFI_STA);


// PMK 16 bytes
esp_now_set_pmk((uint8_t *)"1234567890ABCDEF");


if (esp_now_init() != ESP_OK) {
Serial.println("Lỗi ESP-NOW");
return;
}


esp_now_peer_info_t peerInfo = {};
memcpy(peerInfo.peer_addr, peerMAC, 6);
peerInfo.channel = 0;
peerInfo.encrypt = true; // bật mã hóa
memcpy(peerInfo.lmk, lmk, 16); // Local Master Key


esp_now_add_peer(&peerInfo);
}


void loop() {}