#ifndef ARDUINOOLYMPHELPMEPLS_GASSENSORMQ37_H
#define ARDUINOOLYMPHELPMEPLS_GASSENSORMQ37_H
#include <Arduino.h>
#include <MQUnifiedsensor-2.0.1/src/MQUnifiedsensor.h>

class GasSensorMQ37 {
private:
    String sensorType;
    MQUnifiedsensor *unifiedSensor;
    int pin;

public:
    GasSensorMQ37(String type, int pin, float ratioCleanAir = 0, float a = 0, float b = 0);
    void begin();
    float read();
    String identifySubstance(float reading);
};
#endif //ARDUINOOLYMPHELPMEPLS_GASSENSORMQ37_H
