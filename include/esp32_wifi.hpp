/* ------------------------------------------------------------------------------------
 * AdminTool - MZTechnologies 2022 by Marco A. Zatarain
 * Website: https://mztechnologies.tk
 * E-Mail: technologies.maz@gmail.com
 * Platform ESP32 and ESP8266
 * Project Admin dashboard Embedded server for ESP32
 * ------------------------------------------------------------------------------------ 
*/

#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h>

const byte DNSSERVER_PORT = 53;
DNSServer dnsServer;

IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

int wifi_mode = WIFI_STA;

unsigned long previousMillisWIFI = 0;
unsigned long intervalWIFI = 30000;

// Hostname for ESPmDNS. Should work at least on windows. Try http://adminesp32.local
const char *esp_hostname = id;

void startAP(){
    log("Info: Inciciando Modo AP");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.setHostname(deviceID().c_str());
    WiFi.softAP(ap_nameap, ap_passwordap, ap_canalap, ap_hiddenap, ap_connetap);
    log("Info: WiFi AP " + deviceID() + " - IP " + ipStr(WiFi.softAPIP()));
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNSSERVER_PORT, "*", apIP);
    wifi_mode = WIFI_AP;
}

void startClient() {
    if (staticIP) {
        if (!WiFi.config(CharToIP(wifi_ip_static), CharToIP(wifi_gateway), CharToIP(wifi_subnet), CharToIP(wifi_primaryDNS), CharToIP(wifi_secondaryDNS))) {
            log("Error: Fallo al conectar el Modo Estacion");
        }
    }
WiFi.hostname(deviceID());
WiFi.begin(wifi_ssid, wifi_password);
log("Info: Conectando WiFi " + String(wifi_ssid));
delay(50);
byte b = 0;
while (WiFi.status() != WL_CONNECTED && b < 60) {
    b++;
    log("Warning: Intentando conexion WiFi... ");
    delay(500);
    // Para parpadear LED WiFi cuando esta conectandose al wifi no bloqueante
    // Parpadeo simple del LED cada 100 ms
    //blinkSingle(100, WIFILED);
}
if (WiFi.status() == WL_CONNECTED) {
    // WiFi Station conectado
    log("Info: WiFi conectado (" + String(WiFi.RSSI()) + ") IP " + ipStr(WiFi.localIP()) );
    // Parpadeo random del LED
    //blinkRandomSingle(10, 100, WIFILED);
    delay(100);
} else {
    // WiFi Station No conectado
    log(F("Error: WiFi no conectado"));
    // Parpadeo random del LED
    //blinkRandomSingle(10, 100, WIFILED);
    delay(100);
}
}


//WiFi.mode(WIFI_STA)              -- Station mode: the esp32 connects to an access point
//WiFi.mode(WIFI_AP)               -- Access point mode: stations can connect to the ESP32
//WiFi.mode(WIFI_AP_STA)           -- Access point and a station connected to another access point

void wifi_setup(){
    WiFi.disconnect();
    // 1) Si esta activo el modo AP
    if(ap_accessPoint){
        startAP();
        log("Info: WiFi Modo AP");
    }
    // 2) Caso contrario en Modo Cliente (Estacion)
    else {
        WiFi.mode(WIFI_STA);
        wifi_mode = WIFI_STA;
        startClient();
        log("Info: WiFi Modo Estacion");
    }

    // Iniciar Hostname broadcast en modo STA o AP
    if (wifi_mode == WIFI_STA || wifi_mode == WIFI_AP) {
        if (MDNS.begin(esp_hostname)) {
            MDNS.addService("http", "tcp", 80);
            //log(esp_hostname);
            //MDNS.addService("ws", "tcp", 81);
        }
    }

}
// ------------------------------------------------------------------------------------
// Loop Modo cliente o Estacion
// ------------------------------------------------------------------------------------
void wifiLoop() {

    unsigned long currentMillis = millis();

    if (WiFi.status() != WL_CONNECTED && (currentMillis - previousMillisWIFI >= intervalWIFI) ) {
        // Para parpadear un Led cuando esta conectandose al wifi no bloqueante
        // Parpadeo simple del led cada 100 ms
        blinkSingle(100, WIFILED);

        WiFi.disconnect();
        WiFi.reconnect();
        previousMillisWIFI = currentMillis;

    } else {
        // Parpadeo del led Tiempo On y Tiempo Off
        blinkSingleAsy(10,500,WIFILED);
    }
}
// ------------------------------------------------------------------------------------
// Loop Modo AP
// ------------------------------------------------------------------------------------
void wifiAPLoop(){
    // Parpadeo del led con tiempo variable como transferencia de Datos
    blinkRandomSingle(50,100, WIFILED);
    dnsServer.processNextRequest(); // Captive portal DNS re-dierct
}