#include "GasSensorMQ37.h"

float MQUnifiedsensor::getRatioCleanAir() const {
    return this->_ratio;
}

GasSensorMQ37::GasSensorMQ37(String type, int pin, float ratioCleanAir = 0) : sensorType(type), pin(pin) {
    if (ratioCleanAir == 0){
        Serial.println("Specify the value of Ratio Clean Air for " + type + " sensor");
    } else {
        unifiedSensor = new MQUnifiedsensor(type, 5.0, 1023, pin);
        unifiedSensor->setRatioCleanAir(ratioCleanAir);
    }
}

void GasSensorMQ37::begin() {
    unifiedSensor->setRegressionMethod(1); //_PPM = a*ratio^b
    unifiedSensor->init();
    Serial.print("Calibrating please wait.");
    float calcR0 = 0;
    for(int i = 1; i<=10; i ++)
    {
        unifiedSensor->update(); // обновление данных
        calcR0 += unifiedSensor->calibrate(unifiedSensor->getRatioCleanAir());
        Serial.print(".");
    }
    unifiedSensor->setR0(calcR0/10);
    Serial.println("  done!.");
    if(isinf(calcR0)) {
        Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply");
        while(1);
    }
    if(calcR0 == 0){
        Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
        while(1);
    }

}

float GasSensorMQ37::read() {
    if (sensorType == "MQ2") {
        return -1; // Возвращаем -1, чтобы указать на ошибку, так как этот метод не для MQ2
    } else {
        unifiedSensor->update();
        return unifiedSensor->readSensor();
    }
}
