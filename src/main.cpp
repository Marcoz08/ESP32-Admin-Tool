/* ------------------------------------------------------------------------------------
 * AdminTool - MZTechnologies 2022 by Marco A. Zatarain
 * Website: https://mztechnologies.tk
 * E-Mail: technologies.maz@gmail.com
 * Platform ESP32 and ESP8266
 * Project Admin dashboard Embedded server for ESP32
 * ------------------------------------------------------------------------------------
*/

// ------------------------------------------------------------------------------------
// Libraries
// ------------------------------------------------------------------------------------
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

// ------------------------------------------------------------------------------------
// *.hpp files - Fragmented code
// ------------------------------------------------------------------------------------
#include "settings.hpp"
#include "functions.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"
// ------------------------------------------------------------------------------------
// Setup
// ------------------------------------------------------------------------------------
void setup() {
   // BaudRate
  Serial.begin(115200);
   // CPU Freq
  setCpuFrequencyMhz(240);
   // Incio del log por serial
  log("\nInfo: Iniciando Setup");
   // Configurar los pines
   settingPines();
   // Inicio del SPIFFS
  if (!SPIFFS.begin(true)){
     log(F("Error: Fallo la inicializacion del SPIFFS"));
     while (true);
  }
   // Lee la configuracion del WiFi
  settingsReadWifi();
   // Configuración WiFi
  WiFi.disconnect(true);
  delay(1000);
   // Setup del WiFi
  wifi_setup();
}
// ------------------------------------------------------------------------------------
// Main Loop - Core 0
// ------------------------------------------------------------------------------------
void loop() {
   yield();
   // ---------------------------------------------------------------------------------
   // WIFI
   // ---------------------------------------------------------------------------------
   if (wifi_mode == WIFI_STA) {
      wifiLoop();
   }
   if (wifi_mode == WIFI_AP) {
      wifiAPLoop();
   }


}
