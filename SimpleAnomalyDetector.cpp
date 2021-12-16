/*
 * Or Drukman 209090000
 * Yotam Levin 313248916
 */

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
        maxCor = 0.5;
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

            // Threshold (deviation):
            correlatedFeatures c = addCorrelatedFeatures(ts, points, ts.getFeatureName(i), ts.getFeatureName(indCor), maxCor);
            this->cf.push_back(c);

            for (int k = 0; k < ts.numOfRows(); ++k) {
                delete points[k];
            }
        }
    }

    // Frees space allocated
    for (int i = 0; i < vec.size(); ++i) {
        delete [] vec[i];
    }
}

// Adds a new correlation between features
correlatedFeatures SimpleAnomalyDetector::addCorrelatedFeatures(const TimeSeries& ts, Point** points, string feature_1, string feature_2, float cor_val) {
    Line line = linear_reg(points, ts.numOfRows());
    float maxDev = maxDeviation(points, line, ts.numOfRows());
    correlatedFeatures c;
    c.feature1 = feature_1;
    c.feature2 = feature_2;
    c.corrlation = cor_val;
    c.lin_reg = line;
    c.threshold = maxDev * 1.1f;
    return c;
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

            // If a large deviation was found
            if (checkAnomaly(p, c)) {
                AnomalyReport* ar = new AnomalyReport(c.feature1 + "-" + c.feature2, i);
                anomalyVec.push_back(*ar);
            }
            delete p;
        }
    }
    return anomalyVec;
}

bool SimpleAnomalyDetector::checkAnomaly(Point *p, correlatedFeatures c) {
    float pointDev = dev(*p, c.lin_reg);
    if (pointDev > c.threshold) {
        return true;
    } else {
        return false;
    }
}

