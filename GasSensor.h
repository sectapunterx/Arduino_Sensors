#ifndef ARDUINOOLYMPHELPMEPLS_GASSENSOR_H
#define ARDUINOOLYMPHELPMEPLS_GASSENSOR_H
#include <Arduino.h>
#include <MQUnifiedsensor-2.0.1/src/MQUnifiedsensor.h>
#include <MQ2Lib-master/MQ2Lib.h>

class GasSensor {
private:
    String sensorType;
    MQUnifiedsensor *unifiedSensor;
    MQ2 *mq2Sensor;
    int pin;

public:
    GasSensor(String type, int pin, float ratioCleanAir);
    void begin();
    float read();
    float readMQ2(String gasType); // Для MQ2
    float getRatioCleanAir() const;
};
#endif //ARDUINOOLYMPHELPMEPLS_GASSENSOR_H
