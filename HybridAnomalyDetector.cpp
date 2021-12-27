/*
 * Or Drukman 209090000
 * Yotam Levin 313248916
 */

#include "HybridAnomalyDetector.h"
#include "SimpleAnomalyDetector.h"
#include "SimpleAnomalyDetector.cpp"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

// Adds a new correlation between features
correlatedFeatures HybridAnomalyDetector::addCorrelatedFeatures(const TimeSeries& ts, Point** points, string feature_1, string feature_2, float cor_val) {
    if (cor_val >= 0.9) {
        return SimpleAnomalyDetector::addCorrelatedFeatures(ts, points, feature_1, feature_2, cor_val);
    } else {
        Circle minCircle = findMinCircle(points, ts.numOfRows());
        correlatedFeatures c;
        c.feature1 = feature_1;
        c.feature2 = feature_2;
        c.corrlation = cor_val;
        c.threshold = minCircle.radius * 1.1f;
        c.center_x = minCircle.center.x;
        c.center_y = minCircle.center.y;
        return c;
    }
}

// Check if an anomaly has occurred
bool HybridAnomalyDetector::checkAnomaly(Point *p, correlatedFeatures c) {
    if (c.corrlation >= 0.9) {
        return SimpleAnomalyDetector::checkAnomaly(p, c);
    }
    float pointDev = distanceOfTwoPoints(*p, Point(c.center_x, c.center_y));
    if (pointDev > c.threshold) {
        return true;
    } else {
        return false;
    }
}
