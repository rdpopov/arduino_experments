#ifndef CLOCK_MOD_H
#define CLOCK_MOD_H
#include "st.h"
#include "config_mod.h"
#include "network_mod.h"
#include <WiFiUdp.h>
// includes
// interface

#include <NTPClient.h>
#include <WiFiProv.h>
#include <DS3231.h>
#include <cstdint>

// for ntp
// variables
static modState CLOCK_state=ModUninitialized; // module state
static DS3231 myRTC;

static WiFiUDP ntpUDP;
static NTPClient timeClient(ntpUDP);
// config
static int8_t sync_ntp = 1;
static int8_t gmt = 2;
static int8_t ds = 0; // daylight savings
static int8_t useds = 0; // daylight savings
#define HOUR 3600UL
// functuions
static DateTime CurrentTime;
extern bool softAP;
extern DynamicJsonDocument json_conf;
inline int get_day(){return CurrentTime.day();}
inline int get_month(){return CurrentTime.month();}
inline int get_year(){return CurrentTime.year();}
inline int get_gmt(){return gmt+ds; }
// ------------------------
// base interface 
// ------------------------
modState CLOCK_init() { 
    if (CLOCK_state) {
        Wire.begin();
        gmt = json_conf["gmt"]; // default value is default value
        useds = json_conf["useds"]; // default value is default value
        sync_ntp = json_conf["syncntp"]; // default value is default value
        if(!softAP && sync_ntp && WiFi.status() == WL_CONNECTED) {
            timeClient.begin();
            timeClient.update();
            Serial.println("initial set");
            Serial.println(timeClient.getFormattedTime());
            Serial.println(timeClient.getEpochTime());
            myRTC.setEpoch(timeClient.getEpochTime()); // time assumed
            CurrentTime = DateTime(RTClib::now().unixtime() + (gmt + ds) * HOUR);
        }
    }
    Serial.printf("Date: %d/%d/%d %d:%d:%d\n" ,CurrentTime.day(),CurrentTime.month(),CurrentTime.year(),CurrentTime.hour(),CurrentTime.minute(),CurrentTime.second());
    CLOCK_state = ModOK;
    return CLOCK_state;
}

modState CLOCK_update(){
    timeClient.update();
    if(sync_ntp && WiFi.status() == WL_CONNECTED && timeClient.isTimeSet()) {
        myRTC.setEpoch(timeClient.getEpochTime());
    }
    CurrentTime = DateTime(RTClib::now().unixtime() + (gmt + ds) * HOUR);
    if (useds && ds == 0 && 25 <= CurrentTime.day() && CurrentTime.day() <= 31 && CurrentTime.month() == 3 && myRTC.getDoW() == 7 ) {
        ds = 1;
        CurrentTime = DateTime(RTClib::now().unixtime() + (gmt + ds) * HOUR);
    }
    if (useds && ds == 1 && 25 <= CurrentTime.day() && CurrentTime.day() <= 31 && CurrentTime.month() == 10 && myRTC.getDoW() == 7 ) {
        ds = 0;
        CurrentTime = DateTime(RTClib::now().unixtime() + (gmt + ds) * HOUR);
    }
    Serial.printf("Date: %d/%d/%d %d:%d:%d\n" ,CurrentTime.day(),CurrentTime.month(),CurrentTime.year(),CurrentTime.hour(),CurrentTime.minute(),CurrentTime.second());
    return ModOK;
}

int CLOCK_get(){
    return 0;
}


modState CLOCK_log(){ 
#ifdef LOG_MOD_H
    // do the log part
#endif
    return ModOK;
}

#endif // MD_MOD_H
