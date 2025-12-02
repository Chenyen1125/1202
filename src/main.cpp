#include <Arduino.h>
#include <WiFi.h>

// 週期掃描 SSID（預設每 5 秒掃一次）
const unsigned long SCAN_INTERVAL_MS = 5000; // 5000 ms = 5 秒，若要改頻率請編輯此數值
unsigned long lastScan = 0;

// 執行一次掃描並列印 SSID 名稱（隱藏顯示 <Hidden SSID>）
void doScan() {
  int n = WiFi.scanNetworks();
  if (n <= 0) {
    Serial.println("No networks found");
  } else {
    for (int i = 0; i < n; ++i) {
      String ssid = WiFi.SSID(i);
      if (ssid.length()) Serial.println(ssid);
      else Serial.println("<Hidden SSID>");
    }
  }
  WiFi.scanDelete();
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect();
  delay(100);

  // 立刻執行第一次掃描
  doScan();
  lastScan = millis();
}

void loop() {
  unsigned long now = millis();
  if (now - lastScan >= SCAN_INTERVAL_MS) {
    doScan();
    lastScan = now;
  }
  delay(50); // 小延遲讓系統有時間處理其他任務
}