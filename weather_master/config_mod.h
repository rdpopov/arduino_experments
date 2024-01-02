// this "class" would jsut handle writing and reading of configuration
// we dont check the keys and provide a default implementation
// default implementation is best done in place if key is missing
// just so modules are decoupled
#ifndef CONFIG_MOD_H
#define CONFIG_MOD_H
#include "st.h"
#include <ArduinoJson.h>
// includes
#include "storage_mod.h"
#include "clock_mod.h"
#define CONFIG_NAME "/conf.json"
// this is overkill for size of buffer
#define JSON_BUFSIZE 2048 
#define JSON_PARAMETERS_MAX 20
static char config_buf[JSON_BUFSIZE];
DynamicJsonDocument json_conf(JSON_BUFSIZE);
// CONFIG filename format gmt year month day
// interface
// variables
static modState CONFIG_state = ModUninitialized; // module state
// functuions
// ------------------------
// base interface 
// ------------------------

modState CONFIG_init() {
    if (CONFIG_state) {
#ifdef SD_STORAGE_MOD_H
        if (SD_STORAGE_state) {
            SD_STORAGE_init();
            if (SD_STORAGE_state)
                CONFIG_state = ModError;
        }
        int ret = readFileToBuf(SD,CONFIG_NAME, config_buf, JSON_BUFSIZE);
        if(ret) {
            Serial.printf("Error reading file %s with %d",CONFIG_NAME,ret);
            CONFIG_state = ModError;
        }
        DeserializationError err = deserializeJson(json_conf, config_buf);
        if (err) {
            CONFIG_state = ModError;
        }

#else
        CONFIG_state = ModOK;
#endif
    }
    return CONFIG_state;
}

modState CONFIG_update(){
    serializeJson(json_conf,config_buf,2048);
    writeFile(SD,CONFIG_NAME,config_buf);
    return CONFIG_state;
}

modState CONFIG_display(){ 
    Serial.printf("CONFIG:%d,",0);
    return ModOK;
}

modState CONFIG_CONFIG(){
    return ModOK;
}

#endif // MD_MOD_H
