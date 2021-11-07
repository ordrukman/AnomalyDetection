
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->cf = vector<correlatedFeatures>();
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
}

// Find the biggest distance of a point from the regression line
float maxDeviation(Point** points, Line line, int size) {
    float maxDev = 0, deviation;
    for (int i = 0; i < size; i++) {

        // Calculate deviation
        deviation = dev(*points[i], line);
        if (deviation > maxDev) {
            maxDev = deviation;
        }
    }
    return maxDev;
}

// Creates list of points from vectors of 2 correlated features
Point** getPoints(float* v1, float* v2, int size) {
    Point** points = new Point*[size];
    for (int i = 0; i < size; i++) {
        points[i] = new Point(v1[i], v2[i]);
    }
    return points;
}

// Create vector of correlated features from training data
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    int indCor;
    float maxCor, p;
    vector<float*> vec = ts.getAllValuesVectors();

    // For each feature, iterates through all others to find the most correlated
    for (int i = 0; i < ts.numOfFeatures(); i++) {
        maxCor = 0.9;
        indCor = -1;
        for (int j = i + 1; j < ts.numOfFeatures(); j++) {
            if ((p = abs(pearson(vec[i], vec[j], ts.numOfRows()))) > maxCor) {
                maxCor = p;
                indCor = j;
            }
        }

        // If a correlation was found
        if (indCor != -1) {

            // Linear Regression:
            Point** points = getPoints(vec[i], vec[indCor], ts.numOfRows());
            Line line = linear_reg(points, ts.numOfRows());

            // Threshold (deviation):
            float maxDev = maxDeviation(points, line, ts.numOfRows());
            correlatedFeatures c = {.feature1 = ts.getFeatureName(i), .feature2 = ts.getFeatureName(indCor),
                                    .corrlation = maxCor, .lin_reg = line, .threshold = maxDev * 1.1f};
            this->cf.push_back(c);
            for (int i = 0; i < ts.numOfRows(); ++i) {
                delete points[i];
            }
        }
    }

    // Frees space allocated
    for (int i = 0; i < vec.size(); ++i) {
        delete [] vec[i];
    }
}

// Detects anomalies from data
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> anomalyVec;

    // For each row, iterates through all correlated features and checks for large deviation
	for (int i = 1; i <= ts.numOfRows(); i++) {
        for (int j = 0; j < this->getNormalModel().size(); j++) {
            correlatedFeatures c = this->getNormalModel()[j];
            Point* p = new Point(stof(ts.getTable()[i][ts.getFeatureNum(c.feature1)]),
                                stof(ts.getTable()[i][ts.getFeatureNum(c.feature2)]));
            float pointDev = dev(*p, c.lin_reg);
            delete p;

            // If a large deviation was found
            if (pointDev > c.threshold) {
                AnomalyReport* ar = new AnomalyReport(c.feature1 + "-" + c.feature2, i);
                anomalyVec.push_back(*ar);
            }
        }
    }
    return anomalyVec;
}

