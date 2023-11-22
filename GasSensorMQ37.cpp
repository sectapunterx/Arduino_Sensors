#include "GasSensorMQ37.h"

float MQUnifiedsensor::getRatioCleanAir() const {
    return this->_ratio;
}

GasSensorMQ37::GasSensorMQ37(const String& type, int pin, float ratioCleanAir, float a, float b) : sensorType(type), pin(pin) {
    if(type == "MQ-2"){
        Serial.println("Error: this method is not for MQ2 sensor");
    }else if (ratioCleanAir == 0){
        Serial.println("Specify the value of Ratio Clean Air for " + type + " sensor");
    } else {
        unifiedSensor = new MQUnifiedsensor("Arduino Uno", 5.0, 10, pin, type);
        unifiedSensor->setRatioCleanAir(ratioCleanAir);
        if(a == 0 & b == 0) {
            unifiedSensor->setA(99.042);
            unifiedSensor->setB(-1.518);
        } else {
            unifiedSensor->setA(a);
            unifiedSensor->setB(b);
        }
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
        while(true);
    }
    if(calcR0 == 0){
        Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
        while(true);
    }

}

float GasSensorMQ37::read() {
    if (sensorType == "MQ-2") {
        return -1; // Возвращаем -1, чтобы указать на ошибку, так как этот метод не для MQ2
    } else {
        unifiedSensor->update();
        return unifiedSensor->readSensor();
    }
}

String GasSensorMQ37::identifySubstance(float reading) {
    if (sensorType == "MQ-7") {
        if (reading >= 9) {
            return "Бензин вблизи";
        } else if (reading >= 5 && reading < 9) {
            return "Сигареты вблизи";
        } else if (reading >= 2.2 && reading < 5) {
            return "Горение бумаги вблизи";
        } else if (reading > 0 && reading <= 2.1) {
            // Диапазон 0-2 перекрывает значения "Сигареты далеко" и "Бумага далеко"
            return "Невозможно однозначно определить вещество";
        }
    } else if (sensorType == "MQ-3") {
        if (reading >= 20) {
            return "Парфюм вблизи";
        } else if (reading >= 4 && reading < 20) {
            return "Спирт вблизи";
        } else if (reading >= 1.2 && reading < 4) {
            return "Алкоголь вблизи";
        } else if (reading >= 0.2 && reading < 1.2) {
            return "Смесь парфюма и алкоголя";
        } else if (reading > 0 && reading < 0.2) {
            // Диапазон 0-0.2 перекрывает несколько веществ
            return "Невозможно однозначно определить вещество";
        }
    }
    return "Неопределенное вещество";
}

