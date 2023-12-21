#ifndef SENSOR_INT_H
#define SENSOR_INT_H

class SenorTrait {
    virtuial bool init() = 0;
    virtuial bool update() = 0;
    virtuial String str() = 0;
};

#endif // SENSOR_INT_H
