# 1202 - ESP32 SSID Scanner

此專案示範一個極簡的 ESP32（nodemcu-32s）WiFi SSID 掃描程式，會將附近無線網路的 SSID 名稱輸出到序列埠。

**檔案位置**
- 主程式：`src/main.cpp`
- 專案設定：`platformio.ini`

**功能簡述**
- 以 Station 模式（`WIFI_MODE_STA`）啟用 WiFi，但不嘗試連線。
- 週期掃描附近無線網路，並將每個 AP 的 SSID 名稱輸出到序列埠。
- 若 SSID 為空（隱藏 SSID），顯示為 `<Hidden SSID>`。

**如何編譯 / 上傳 / 監視（PowerShell）**
```powershell
# 在專案根目錄執行：
# 只 build（編譯）
pio run -e nodemcu-32s

# build 並上傳到板子（請先把板子插上電腦）
pio run -e nodemcu-32s -t upload

# 打開序列埠監視器（baud 115200）
pio device monitor -b 115200
```

**`src/main.cpp` 重要說明**
- 程式使用常數 `SCAN_INTERVAL_MS` 控制掃描間隔（毫秒）。
  - 目前預設為 5000（代表每 5 秒掃描一次）。
  - 若要改成每 10 秒掃描，請修改為 `10000`。

- 範例核心程式（重點）：
```cpp
// 設定掃描間隔（單位：毫秒）
const unsigned long SCAN_INTERVAL_MS = 5000;

// 執行一次掃描並印出 SSID
void doScan() {
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i) {
    String ssid = WiFi.SSID(i);
    if (ssid.length()) Serial.println(ssid);
    else Serial.println("<Hidden SSID>");
  }
  WiFi.scanDelete();
}
```

**執行流程**
1. 上傳程式到 ESP32。
2. 開啟序列埠監視器（`pio device monitor -b 115200`）。
3. 你會在序列埠看到第一次掃描結果，之後每隔 `SCAN_INTERVAL_MS` 顯示一次清單。

**除錯與常見問題**
- 若 `pio run` 失敗：檢查 PlatformIO 擴充是否安裝、`platformio.ini` 中的 `board` 是否正確。
- 若上傳失敗：確認 USB 線與驅動、以及 Windows 的 COM 埠是否正確。
- 若序列埠無輸出：確認監視器的 baud 設為 `115200` 並且板子有上電。

**想做的下一步（選擇性）**
- 改為只執行一次掃描後進入深度睡眠（省電）。
- 將掃描結果透過 HTTP / MQTT 傳回主機或顯示在 OLED。

---
如果你要我幫你：
- 執行一次 `pio run`（只 build），回傳編譯日誌；或
- 幫你把間隔改成其他數值（例如 2000 ms），
請直接回覆要做的項目。