#ifndef GAS_MOD_H
#define GAS_MOD_H
#include "st.h"
// includes
#include "MQ7.h"
// interface
// variables
static modState GAS_state = ModUninitialized; // module state
static MQ7 mq7(36); //param[1] : Analog pin number, param[2] : Sensor Vcc value
// functuions
static float GAS_ppm = -1.0;
// ------------------------
// base interface 
// ------------------------
modState GAS_init() {
    GAS_state = ModOK;
    mq7.calibrate();
    return GAS_state;
}

modState GAS_update(){ 
    GAS_ppm = mq7.readPpm();
    return ModOK;
}

int GAS_get(){ 
    return 0;
}

modState GAS_log(){ 
#ifdef LOG_MOD_H
    LOG_write_float("CO/ppm", GAS_ppm);
#endif
    return ModOK;
}

#endif // MD_MOD_H
