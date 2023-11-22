#include "GasSensor.h"

GasSensor::GasSensor(String type, int pin, float ratioCleanAir = 0) : sensorType(type), pin(pin) {
    if (type == "MQ2") {
        mq2Sensor = new MQ2(pin);
    } else {
        unifiedSensor = new MQUnifiedsensor(type, 5.0, 1023, pin);
        unifiedSensor->setRatioCleanAir(ratioCleanAir);
    }
}

void GasSensor::begin() {
    if (sensorType == "MQ2") {
        mq2Sensor->begin();
    } else {
        unifiedSensor->setRegressionMethod(1); //_PPM = a*ratio^b
        unifiedSensor->init();
        unifiedSensor->calibrate(getRatioCleanAir());
    }
}

float GasSensor::read() {
    if (sensorType == "MQ2") {
        return -1; // Возвращаем -1, чтобы указать на ошибку, так как этот метод не для MQ2
    } else {
        unifiedSensor->update();
        return unifiedSensor->readSensor();
    }
}

float GasSensor::readMQ2(String gasType) {
    if (sensorType == "MQ2") {
        if (gasType == "LPG") {
            return mq2Sensor->readLPG();
        } else if (gasType == "CO") {
            return mq2Sensor->readCO();
        } else if (gasType == "SMOKE") {
            return mq2Sensor->readSmoke();
        }
    }
    return -1;
}

float MQUnifiedsensor::getRatioCleanAir() const {
    return this->_ratio;
}
