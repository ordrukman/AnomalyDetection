
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->cf = vector<correlatedFeatures>();
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	//  Auto-generated destructor stub
}

float maxDeviation(Point** points, Line line, int size) {
    float maxDev = 0, deviation;
    for (int i = 0; i < size; i++) {
        deviation = dev(*points[i], line);
        if (deviation > maxDev) {
            maxDev = deviation;
        }
    }
    return maxDev;
}

Point** getPoints(float* v1, float* v2, int size) {
    Point** points = new Point*[size];
    for (int i = 0; i < size; i++) {
        points[i] = new Point(v1[i], v2[i]);
    }
    return points;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    int indCor, pears;
    float maxCor, p;
    vector<float*> vec = ts.getAllValuesVectors();
    for (int i = 0; i < ts.numOfFeatures(); i++) {
        maxCor = 0.9;
        indCor = -1;
        for (int j = i + 1; j < ts.numOfFeatures(); j++) {
            if ((p = abs(pearson(vec[i], vec[j], ts.numOfRows()))) > maxCor) {
                maxCor = p;
                indCor = j;
            }
        }

        if (indCor != -1) {
            // Linear Regression:
            Point** points = getPoints(vec[i], vec[indCor], ts.numOfRows());
            Line line = linear_reg(points, ts.numOfRows());

            // Threshold:
            float maxDev = maxDeviation(points, line, ts.numOfRows());

            correlatedFeatures c = {.feature1 = ts.getFeatureName(i), .feature2 = ts.getFeatureName(indCor),
                                    .corrlation = maxCor, .lin_reg = line, .threshold = maxDev};
            this->cf.push_back(c);
        }
    }
}





vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// Auto-generated destructor stub
}

