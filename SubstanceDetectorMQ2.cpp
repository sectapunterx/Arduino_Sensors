#include "SubstanceDetectorMQ2.h"

SubstanceDetectorMQ2::SubstanceDetectorMQ2() {
    paperBurningClose = {160, 170, 4500, 4600, 830, 840};
    paperBurningFar = {1.7, 1.8, 8.5, 9.5, 6.5, 6.9};
    vapeClose = {0.9, 1.2, 4, 4.8, 4.0, 4.2};
    vapeFar = {0.3, 0.4, 0.9, 1.1, 1.2, 1.3};
}

String SubstanceDetectorMQ2::detectSubstance(float lpg, float co, float smoke) {
    // Логика для определения вещества на основе текущих показаний датчиков
    if (lpg >= paperBurningClose.lpg_min && lpg <= paperBurningClose.lpg_max &&
        co >= paperBurningClose.co_min && co <= paperBurningClose.co_max &&
        smoke >= paperBurningClose.smoke_min && smoke <= paperBurningClose.smoke_max) {
        return "Горение бумаги вблизи";
    }
    if(lpg >= paperBurningFar.lpg_min && lpg <= paperBurningFar.lpg_max &&
       co >= paperBurningFar.co_min && co <= paperBurningFar.co_max &&
       smoke >= paperBurningFar.smoke_min && smoke <= paperBurningFar.smoke_max) {
        return "Горение бумаги вдали";
    }
    if(lpg >= vapeClose.lpg_min && lpg <= vapeClose.lpg_max &&
       co >= vapeClose.co_min && co <= vapeClose.co_max &&
       smoke >= vapeClose.smoke_min && smoke <= vapeClose.smoke_max) {
        return "Вейп вблизи";
    }
    if(lpg >= vapeFar.lpg_min && lpg <= vapeFar.lpg_max &&
       co >= vapeFar.co_min && co <= vapeFar.co_max &&
       smoke >= vapeFar.smoke_min && smoke <= vapeFar.smoke_max) {
        return "Вейп вдали";
    }
    return "Неизвестное вещество";
}
