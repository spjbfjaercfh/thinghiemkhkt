unsigned long t0;
uint8_t peerMAC[] = {0x24, 0x6F, 0x28, 0x11, 0x22, 0x33};


void OnDataRecv(const uint8_t *mac, const uint8_t *data, int len) {
unsigned long t1 = micros();
Serial.print("Latency (us): ");
Serial.println(t1 - t0);
}


void loop() {
t0 = micros();
const char *msg = "PING";
esp_now_send(peerMAC, (uint8_t*)msg, strlen(msg));
delay(500);
}