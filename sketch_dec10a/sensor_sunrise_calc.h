
#include <cstdint>
class SunriseCalculator: SenorTrait {
    float longitude;
    float latitude;
    int64_t sunrise_timestamp;
    int64_t sunset_timestamp;
    SunriseCalculator(float longitute,float latitude);
    bool init(){};
    bool update(){
        // calculate tume by formula
    };
    String str(){
        return "SunriseCalculator";
    }
};
