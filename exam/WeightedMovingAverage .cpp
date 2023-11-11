#include "WeightedMovingAverage.h"
#include <algorithm>

double* WeightedMovingAverage::allocateAndCopy(const double* source, int size) {
    // 동적 배열 메모리 할당 및 초기화
    double* newArray = new double[size];
    std::copy(source, source + size, newArray);
    return newArray;
}

void WeightedMovingAverage::expandValues() {
    // values 배열 확장
    int newCapacity = std::max(1, 2 * maxCapacity);
    double* newValues = new double[newCapacity];

    if (values) {
        std::copy(values, values + currentSize, newValues);
        delete[] values;
    }

    values = newValues;
    maxCapacity = newCapacity;
}

WeightedMovingAverage::WeightedMovingAverage(int size, const double* initialWeights) : n(size), currentSize(0), maxCapacity(0), values(nullptr) {
    // 생성자
    weights = allocateAndCopy(initialWeights, size);
}

WeightedMovingAverage::~WeightedMovingAverage() {
    // 소멸자
    delete[] weights;
    delete[] values;
}

WeightedMovingAverage::WeightedMovingAverage(const WeightedMovingAverage& other) : n(other.n), currentSize(other.currentSize), maxCapacity(other.maxCapacity) {
    // 복사 생성자
    weights = allocateAndCopy(other.weights, n);
    values = allocateAndCopy(other.values, maxCapacity);
}

WeightedMovingAverage::WeightedMovingAverage(WeightedMovingAverage&& other) noexcept : weights(other.weights), values(other.values), n(other.n), currentSize(other.currentSize), maxCapacity(other.maxCapacity) {
    // 이동 생성자
    other.weights = nullptr;
    other.values = nullptr;
}

WeightedMovingAverage& WeightedMovingAverage::operator=(const WeightedMovingAverage& other) {
    // 복사 할당 연산자
    if (this != &other) {
        delete[] weights;
        delete[] values;

        n = other.n;
        currentSize = other.currentSize;
        maxCapacity = other.maxCapacity;
        weights = allocateAndCopy(other.weights, n);
        values = allocateAndCopy(other.values, maxCapacity);
    }
    return *this;
}

WeightedMovingAverage& WeightedMovingAverage::operator=(WeightedMovingAverage&& other) noexcept {
    // 이동 할당 연산자
    if (this != &other) {
        delete[] weights;
        delete[] values;

        weights = other.weights;
        values = other.values;
        n = other.n;
        currentSize = other.currentSize;
        maxCapacity = other.maxCapacity;

        other.weights = nullptr;
        other.values = nullptr;
    }
    return *this;
}

void WeightedMovingAverage::addValue(double value) {
    // 데이터 추가하는 함수
    if (currentSize >= maxCapacity) {
        expandValues();
    }

    values[currentSize++] = value;
    if (currentSize > n) {
        std::copy(values + 1, values + currentSize, values);
        --currentSize;
    }
}

double WeightedMovingAverage::calculateWMA() {
    // 가중 이동 평균 계산
    int effectiveSize = std::min(n, currentSize);
    double weightedSum = 0.0;
    double weightsSum = 0.0;

    for (int i = 0; i < effectiveSize; ++i) {
        weightedSum += values[currentSize - 1 - i] * weights[i];
        weightsSum += weights[i];
    }

    return weightsSum != 0.0 ? weightedSum / weightsSum : weightedSum;
}
