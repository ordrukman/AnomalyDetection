/*
 * Or Drukman 209090000
 * Yotam Levin 313248916
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
    float center_x, center_y;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{

public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}
    bool setThreshold(float thresh);
protected:
    virtual correlatedFeatures addCorrelatedFeatures(const TimeSeries& ts, Point** points, string feature_1, string feature_2, float cor_val);
    virtual bool checkAnomaly(Point* p, correlatedFeatures c);
    vector<correlatedFeatures> cf;
    float threshold;
};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
