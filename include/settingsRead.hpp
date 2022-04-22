/* ------------------------------------------------------------------------------------
 * AdminTool - MZTechnologies 2022 by Marco A. Zatarain
 * Website: https://mztechnologies.tk
 * E-Mail: technologies.maz@gmail.com
 * Platform ESP32 and ESP8266
 * Project Admin dashboard Embedded server for ESP32
 * ------------------------------------------------------------------------------------ 
*/

// ------------------------------------------------------------------------------------
// Leer configuraciones de los parametros WIFI
// ------------------------------------------------------------------------------------  
boolean settingsReadWifi(){
    StaticJsonDocument<500> jsonConfig;
    File file = SPIFFS.open("/SettingWifi.json", "r");
    if(deserializeJson(jsonConfig, file)){
        // Si falla la lectura inicia valores por defecto
        settingsResetWifi();
        log("Error: Falló la lectura de la configuración Wifi, tomando valores por defecto");
        return false;
    }
    else{
          /* ------------------- GENERAL ------------------- */
           strlcpy(id, jsonConfig["id"], sizeof(id));
           bootCount = jsonConfig["boot"];
          /* ------------------- CLIENTE ------------------- */
          staticIP = jsonConfig["wifi_staticIP"];
          strlcpy(wifi_ssid, jsonConfig["wifi_ssid"], sizeof(wifi_ssid));
          strlcpy(wifi_password, jsonConfig["wifi_password"], sizeof(wifi_password));
          strlcpy(wifi_ip_static, jsonConfig["wifi_ip_static"], sizeof(wifi_ip_static));
          strlcpy(wifi_gateway, jsonConfig["wifi_gateway"], sizeof(wifi_gateway));
          strlcpy(wifi_subnet, jsonConfig["wifi_subnet"], sizeof(wifi_subnet));
          strlcpy(wifi_primaryDNS, jsonConfig["wifi_primaryDNS"], sizeof(wifi_primaryDNS));
          strlcpy(wifi_secondaryDNS, jsonConfig["wifi_secondaryDNS"], sizeof(wifi_secondaryDNS));
          /* ------------------- AP ------------------- */
          ap_accessPoint = jsonConfig["ap_accessPoint"];
          strlcpy(ap_nameap, jsonConfig["ap_nameap"], sizeof(ap_nameap));
          strlcpy(ap_passwordap, jsonConfig["ap_passwordap"], sizeof(ap_passwordap));
          ap_canalap = jsonConfig["ap_canalap"];
          ap_hiddenap = jsonConfig["ap_hiddenap"];
          ap_connetap = jsonConfig["ap_connetap"];
          file.close();
          log("Info: Lectura configuración WiFi correcta");
          return true;
    }
}