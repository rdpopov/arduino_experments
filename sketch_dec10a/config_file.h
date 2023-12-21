
#ifndef CONFIG_H
#define CONFIG_H
#include "sd_test.h"

#define CONFIG_FNAME "config"
#define CONFIG_FORMAT "wifi_ssid=%s\nwifi_pass=%s\ntime_zone=%d"

static char* wifi_ssid ="";
static char* wifi_pass ="";
static int time_zone ="";
#define CONFIG_MAX_SIZE 512
static char config[CONFIG_MAX_SIZE] = {};
static int config_state = 0;

void read_config(){
    if (setup_sd()){
        File file = SD.open(path);
        if(!file){
            Serial.println("Failed to open file for reading");
            return;
        }
        if (file.size() >= CONFIG_MAX_SIZE ){
            Serial.printf("File size too big %d > %d",file.size(),CONFIG_MAX_SIZE);
            return;
        }
        file.read(config,CONFIG_MAX_SIZE);
        sscanf(config,CONFIG_FORMAT,&wifi_ssid,&wifi_pass,&time_zone);
        file.close();
    }
}

void write_config(){
    memset(config,0,CONFIG_MAX_SIZE);
    sprintf(config,CONFIG_FORMAT,wifi_ssid,wifi_pass,time_zone);
    writeFile(SD,CONFIG_FNAME,config);
}


#endif
