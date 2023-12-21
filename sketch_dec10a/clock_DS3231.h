#ifndef DS3231_CLOCK_H
#define DS3231_CLOCK_H
#include <NTPClient.h>
#include <DS3231.h>
#include <cstdint>
#include "clock_int.h"

class DS3231_ntp: ClockTrait {
    public:
        bool ntp_force_sync;
        int  timezone;
        int update_delta;
        uint64_t unix_time;
        DS3231_ntp() {};
        bool init(bool ntp_force_sync,bool ntp_sync) {

        };
        void update(bool ntp_sync) {
            if (ntp_sync || ntp_force_sync) {
                //update
            }
        };
        void update_unix_time(uint64_t unix_time) {
        };
        void update_timezone(int timezone) {
        };
        uint64_t get(){
            return unix_time;
        };
        Sting str(){
            return "DS3231_ntp ret value";
        };
};

#endif // DS3231_CLOCK_H
