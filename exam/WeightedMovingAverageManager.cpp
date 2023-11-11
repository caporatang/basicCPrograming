//
// Created by capor on 2023-11-11.
//

#ifndef SCHOOL_WEIGHTEDMOVINGAVERAGEMANAGER_H
#define SCHOOL_WEIGHTEDMOVINGAVERAGEMANAGER_H


#include <iostream>
#include "WeightedMovingAverage.h"

class WeightedMovingAverageManager {
private:
    WeightedMovingAverage wma;
};

int main() {
    try {
        double initialWeights[] = {0.5, 0.3, 0.15, 0.05};
        WeightedMovingAverage wma(4, initialWeights);
        wma.addValue(10);
        wma.addValue(5);
        wma.addValue(8);
        wma.addValue(12);
        wma.addValue(10);
        wma.addValue(14);
        std::cout << "WMA: " << wma.calculateWMA() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

#endif