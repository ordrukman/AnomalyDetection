/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */

#include <math.h>
#include <iostream>
#include "anomaly_detection_util.h"

float avg(float* x, int size){
    float sum = 0;
    for (int i=0; i < size; i++) {
        sum = sum + x[i];
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
    return sum/size;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    float sigX = sqrt(var(x, size));
    float sigY = sqrt(var(y, size));
    float pearson = cov(x, y, size)/(sigX*sigY);
    return pearson;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){

	return Line(0,0);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	return 0;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	return 0;
}




