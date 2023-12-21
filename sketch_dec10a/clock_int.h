#ifndef CLOCK_INT_H
#define CLOCK_INT_H
#include <NTPClient.h>
#include <WiFiProv.h>
#include <DS3231.h>

static int ntp_use = 0;
static int ntp_update_period = 0;
static int ntp_update_delta = 0;
static DS3231 myRTC;

int init_ntp(const char* ssid,const char* pass){
    if (ssid && pass && ntp_use){
        int tries = 10;
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED && tries--) {
            delay(500);
            Serial.print(".");
        }

        if (WiFi.status() != WL_CONNECTED){
            ntp_use = 0;
            return -1;
        } else{
            Serial.println("WiFi connected.");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
        }
    }
    return  0;
}

void set_timezone(int tz){
    if (ntp_use){

    }
}

void setup_clock(const char* ssid,const char* pass) {
    init_ntp(ssid, pass);
    Wire.begin();
}
#endif // CLCOK_INT_H
