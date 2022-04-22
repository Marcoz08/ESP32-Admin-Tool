// ------------------------------------------------------------------------------------
// Definitions
// ------------------------------------------------------------------------------------
#define RELAY1 27                  //GPIO27 Relay 1 Output
#define RELAY2 26                  //GPIO26 Relay 2 Output
#define WIFILED 12                 //GPIO12 LED Indicator WIFI
#define MQTTLED 13                 //GPIO27 LED Indicator MQTT
// ------------------------------------------------------------------------------------
// Hardware version
// ------------------------------------------------------------------------------------
#define HW "ADMINESP32 v1 00000000"     //Version del hardwareyñpjy  6uku         liouñ859prgntnonffngsfdiid   
// ------------------------------------------------------------------------------------
// WIFI
// ------------------------------------------------------------------------------------   
boolean staticIP;                       //Uso de IP Estática
char wifi_ssid[30];                     //Red Wifi
char wifi_password[30];                 //Contraseña de Red Wifi
char wifi_ip_static[15];                //IP Estático
char wifi_gateway[15];                  //Gateway
char wifi_subnet[15];                   //Subred 
char wifi_primaryDNS[15];               //DNS Primario
char wifi_secondaryDNS[15];             //DNS Secundario
// ------------------------------------------------------------------------------------
// General configuration
// ------------------------------------------------------------------------------------
char id[30];                            //ID del dispositivo
int bootCount;                          //Numero de reinicios 
// ------------------------------------------------------------------------------------
// Access Point
// ------------------------------------------------------------------------------------
boolean ap_accessPoint;                 //Uso del Modo AP
char ap_nameap[31];                     //SSID AP 
char ap_passwordap[63];                 //Canal AP
int  ap_canalap;                        //Canal AP
int  ap_hiddenap;                       //Es visible o no el AP  (0 - Visible / 1 - Oculto) 
int  ap_connetap;                       //Número de conexiones en el AP
// ------------------------------------------------------------------------------------
// Zona Otras 
// ------------------------------------------------------------------------------------
uint8_t ip[4];                          //Variable funcion convertir string a IP
 