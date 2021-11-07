cmake_minimum_required(VERSION 3.20)
project(AnomalyDetection)

set(CMAKE_CXX_STANDARD 11)

add_executable(AnomalyDetection MainTrain.cpp anomaly_detection_util.cpp)
set(SOURCE_FILES anomaly_detection_util.cpp )