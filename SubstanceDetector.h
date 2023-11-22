
#ifndef ARDUINOOLYMPHELPMEPLS_SUBSTANCEDETECTOR_H
#define ARDUINOOLYMPHELPMEPLS_SUBSTANCEDETECTOR_H
#include <Arduino.h>

class SubstanceDetector {
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
    SubstanceDetector();
    String detectSubstance(float lpg, float co, float smoke);
};
#endif //ARDUINOOLYMPHELPMEPLS_SUBSTANCEDETECTOR_H
