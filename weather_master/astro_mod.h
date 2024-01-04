#ifndef ASTRO_MOD_H
#define ASTRO_MOD_H
#include "DS3231.h"
#include "HardwareSerial.h"
#include "st.h"
// includes
#include "clock_mod.h"
#include "config_mod.h"
#include <moonPhase.h>
#include <MoonRise.h>
#include <SunRise.h>
// interface
// variables
//

#define SOFIA_lat 42.6977; // Sofia, Bulgaria Latitude
#define SOFIA_lon 23.3219; // Sofia, Bulgaria  Longitude

static modState ASTRO_state; // module state
static double lat = SOFIA_lat; // Sofia, Bulgaria Latitude
static double lon = SOFIA_lon; // Sofia, Bulgaria  Longitude

static moonPhase moonPhase_inst;
static moonData_t moon_dat;
static MoonRise moon_rise;
static SunRise sun_rise;
static DateTime MRTime;
static DateTime MSTime;
static DateTime SRTime;
static DateTime SSTime;
extern DateTime CurrentTime;
extern DynamicJsonDocument json_conf;
static std::mutex ASTRO_mutex;
// functuions

// ------------------------
// base interface
// ------------------------

modState ASTRO_init() {
    ASTRO_state = ModOK;
    lat = json_conf["lat"];
    if (lat == 0.0) {
        lat = SOFIA_lat;
    }
    lon = json_conf["lon"];
    if (lon == 0.0) {
        lon = SOFIA_lon;
    }
    return ASTRO_state;
}

modState ASTRO_update(){
    ASTRO_mutex.lock();
    moon_rise.calculate(lat, lon, CurrentTime.unixtime());
    sun_rise.calculate(lat, lon, CurrentTime.unixtime());
    MRTime = DateTime(moon_rise.riseTime);
    MSTime = DateTime(moon_rise.setTime);
    SRTime = DateTime(sun_rise.riseTime);
    SSTime = DateTime(sun_rise.setTime);
    moon_dat = moonPhase_inst.getPhase();
    ASTRO_mutex.unlock();
    return ASTRO_state;
}

int ASTRO_get(){ 
    return 0;
}

modState ASTRO_log(){ 
#ifdef LOG_MOD_H
    // do the log part
#endif
    return ModOK;
}

#endif // MD_MOD_H
