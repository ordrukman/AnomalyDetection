/*
 * anomaly_detection_util.cpp
 *
 * Author:
 * Or Drukman 209090000
 * Yotam Levin 313248916
 */

#include <math.h>
#include <iostream>
#include "anomaly_detection_util.h"

float avg(float* x, int size){
    float sum = 0;
    for (int i=0; i < size; i++) {
        sum = sum + x[i];
    }
    if (size <= 0) {
        std::cout << "Can't calculate average - array is empty" << std::endl;
        return 0;
    }
    float average = sum/size;
	return average;
}

// returns the variance of X and Y
float var(float* x, int size){
    float sum = 0;
    float sumSqr = 0;
    for (int i=0; i < size; i++) {
        sum = sum + x[i];
        sumSqr = sumSqr + pow(x[i], 2);
    }
    if (size <= 0) {
        std::cout << "Can't calculate variance - array is empty" << std::endl;
        return 0;
    }
    float u = sum/size;
    float v = sumSqr/size - pow(u, 2);
	return v;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float avgX = avg(x, size);
    float avgY = avg(y, size);
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum = sum + (x[i] - avgX)*(y[i] - avgY);
    }
    if (size <= 0) {
        std::cout << "Can't calculate covariance - array is empty" << std::endl;
        return 0;
    }
    return sum/size;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    float sigX = sqrt(var(x, size));
    float sigY = sqrt(var(y, size));
    if (size <= 0) {
        std::cout << "Can't calculate pearson - array is empty" << std::endl;
        return 0;
    }
    float pear = cov(x, y, size)/(sigX*sigY);
    return pear;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
    float* arrX = new float[size];
    float* arrY = new float[size];
    for (int i = 0; i < size; i++) {
        arrX[i] = points[i]->x;
        arrY[i] = points[i]->y;
    }
    if (size <= 0) {
        std::cout << "Can't calculate variance - array is empty" << std::endl;
        Line l(0, 0);
        return l;
    }
    float a = cov(arrX, arrY, size)/var(arrX, size);
    float b = avg(arrY, size) - a * avg(arrX, size);
    Line l(a, b);
	return l;
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    Line l = linear_reg(points, size);
    return dev(p, l);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    float dis = fabs(p.y - l.f(p.x));
	return dis;
}




