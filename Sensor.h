//
// Created by alvaro on 8/08/15.
//

#ifndef SENSOR_H
#define SENSOR_H

enum Quantity {
  ALL = 0b1111111111111111,
  TEMPERATURE = 1 << 0,
  HUMIDITY = 1 << 1
};

typedef struct{
    char *name;
    Quantity *quantities;
}SensorType;



class Sensor {
public:
    virtual const char* getName();
    virtual float* getValues(unsigned int quantities, unsigned int * readValues);
    static const char* getType();
    static Sensor* fromConfig(void *);
    Sensor* Config(void *);
};






#endif //SENSOR__H
