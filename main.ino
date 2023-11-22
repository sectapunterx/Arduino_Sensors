#include <Arduino.h>
#include <MQ2Lib-master/MQ2Lib.h>
#include <MQUnifiedsensor-2.0.1/src/MQUnifiedsensor.h>
#include "SubstanceDetectorMQ2.h"


SubstanceDetectorMQ2 detector;
MQ2 mq2(A0, true);

void setup() {
    Serial.begin(9600);
    mq2.begin();
}

void loop() {
    float lpg = mq2.readLPG();
    float co = mq2.readCO();
    float smoke = mq2.readSmoke();

    String substance = detector.detectSubstance(lpg, co, smoke);
    Serial.println("Обнаруженное вещество: " + substance);

    delay(1000);
}
