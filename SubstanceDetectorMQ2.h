
#ifndef ARDUINOOLYMPHELPMEPLS_SUBSTANCEDETECTORMQ2_H
#define ARDUINOOLYMPHELPMEPLS_SUBSTANCEDETECTORMQ2_H
#include <Arduino.h>

class SubstanceDetectorMQ2 {
private:
    struct SubstanceThreshold {
        float lpg_min, lpg_max;
        float co_min, co_max;
        float smoke_min, smoke_max;
    };

    SubstanceThreshold paperBurningClose;
    SubstanceThreshold paperBurningFar;
    SubstanceThreshold vapeClose;
    SubstanceThreshold vapeFar;

public:
    SubstanceDetectorMQ2();
    String detectSubstance(float lpg, float co, float smoke);

};
#endif //ARDUINOOLYMPHELPMEPLS_SUBSTANCEDETECTORMQ2_H
