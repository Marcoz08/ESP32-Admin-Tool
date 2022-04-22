/* ------------------------------------------------------------------------------------
 * AdminTool - MZTechnologies 2022 by Marco A. Zatarain
 * Website: https://mztechnologies.tk
 * E-Mail: technologies.maz@gmail.com
 * Platform ESP32 and ESP8266
 * Project Admin dashboard Embedded server for ESP32
 * ------------------------------------------------------------------------------------
*/

#include <Arduino.h>

bool ioBlink = false;
unsigned long milOld;
int rndTemp = 0;

// ------------------------------------------------------------------------------------
// Simple blinking function - Pestañeo para Alarmas tiempo variable
// ------------------------------------------------------------------------------------
void blinkSingle(int speed, int _pin) {
    if((milOld + speed) < millis()) {
        milOld = millis();
        if(ioBlink == false) {
            digitalWrite(_pin, HIGH);
            ioBlink = true;
        }
        else {
            digitalWrite(_pin, LOW);
            ioBlink = false;
        }
    }

}
// ------------------------------------------------------------------------------------
// Parpadeo Asincronico Tiempo On y Tiempo Off - tiempo variable
// ------------------------------------------------------------------------------------
void blinkSingleAsy(int timeHigh, int timeLow, int _pin) {
    if (ioBlink == false) {
        if ((milOld + timeHigh) < millis()) {
            milOld = millis();
            digitalWrite(_pin, LOW);
            ioBlink = true;
        }
    }
    else {
        if ((milOld + timeLow) < millis()) {
            milOld = millis();
            digitalWrite(_pin, HIGH);
            ioBlink = false;
        }
    }

}
// ------------------------------------------------------------------------------------
// Blinking with randomised delay como para TX/RX de Datos
// ------------------------------------------------------------------------------------
void blinkRandomSingle(int minTime, int maxTime, int _pin) {
    if ((milOld + rndTemp) < millis()) {
        milOld = millis();
        rndTemp = random(minTime, maxTime);
        if(ioBlink == false) {
            digitalWrite(_pin, HIGH);
            ioBlink = true;
        }
        else {
            digitalWrite(_pin, LOW);
            ioBlink = false;
        }
    }

}
// ------------------------------------------------------------------------------------
// On un LED
// ------------------------------------------------------------------------------------
void setOnSingle(int _pin) {
    digitalWrite(_pin, HIGH);
}
// ------------------------------------------------------------------------------------
// Off un LED
// ------------------------------------------------------------------------------------
void setOffSingle(int _pin) {
    digitalWrite(_pin, LOW);
}