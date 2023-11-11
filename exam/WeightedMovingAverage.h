//
// Created by capor on 2023-11-11.
//

#ifndef SCHOOL_WEIGHTEDMOVINGAVERAGE_H
#define SCHOOL_WEIGHTEDMOVINGAVERAGE_H


class WeightedMovingAverage {
private:
    double* weights;
    double* values;
    int n;
    int currentSize;
    int maxCapacity;

    double* allocateAndCopy(const double* source, int size);
    void expandValues();

public:
    WeightedMovingAverage(int size, const double* initialWeights);
    ~WeightedMovingAverage();
    WeightedMovingAverage(const WeightedMovingAverage& other);
    WeightedMovingAverage(WeightedMovingAverage&& other) noexcept;
    WeightedMovingAverage& operator=(const WeightedMovingAverage& other);
    WeightedMovingAverage& operator=(WeightedMovingAverage&& other) noexcept;

    void addValue(double value);
    double calculateWMA();
};

#endif