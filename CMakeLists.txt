cmake_minimum_required(VERSION 3.26)
project(school)

set(CMAKE_CXX_STANDARD 17)

add_executable(school main.cpp
        basic.cpp
        basic.h
        exam/WeightedMovingAverage.h
        "exam/WeightedMovingAverage .cpp"
        exam/WeightedMovingAverageManager.cpp
)
