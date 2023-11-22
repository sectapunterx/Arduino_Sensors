#include <Arduino.h>
#include <MQ2Lib-master/MQ2Lib.h>
#include <MQUnifiedsensor-2.0.1/src/MQUnifiedsensor.h>
#include "SubstanceDetectorMQ2.h"
#include "GasSensorMQ37.h"


SubstanceDetectorMQ2 detector;
MQ2 mq2(A0, true);
GasSensorMQ37 mq3 ("MQ-3", A1, 60);
GasSensorMQ37 mq7("MQ-7", A2, 27.5);

void setup() {
    Serial.begin(9600);
    mq2.begin();
    mq3.begin();
    mq7.begin();
}

void loop() {
    //FOR MQ2
    float lpg = mq2.readLPG();
    float co = mq2.readCO();
    float smoke = mq2.readSmoke();

    String substance = detector.detectSubstance(lpg, co, smoke);
    Serial.println("Обнаруженное вещество: " + substance);

    //FOR MQ3 OR MQ7



    delay(1000);
}
