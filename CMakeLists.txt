cmake_minimum_required(VERSION 3.20)
project(AnomalyDetection)

set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_CXX_STANDARD 11)

add_executable(AnomalyDetection MainTrain.cpp anomaly_detection_util.cpp minCircle.cpp)
set(SOURCE_FILES anomaly_detection_util.cpp)