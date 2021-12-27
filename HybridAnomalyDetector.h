/*
 * Or Drukman 209090000
 * Yotam Levin 313248916
 */

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual correlatedFeatures addCorrelatedFeatures(const TimeSeries &ts, Point **points, string feature_1, string feature_2, float cor_val);
    virtual bool checkAnomaly(Point* p, correlatedFeatures c);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
