

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class GivenReport{
public:
    int startTimeStep;
    int endTimeStep;
    bool isExistAnyDetectForThisReport;
};

class CompressReport{
public:
    string description;
    int startTimeStep;
    int endTimeStep;
    bool isReal;

};

struct DetectorFeatures{
public:
    float threshold;
    TimeSeries* trainTS, testTS;
    vector<AnomalyReport> anomalyReport;
};

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
    virtual void createFile(string fileName) {
        ofstream file(fileName);
        string line = read();
        while (line != "done") {
            file << line << endl;
            line = read();
        }
        file.close();
    }

    virtual vector<GivenReport> createRealReportVector() {
        vector<GivenReport> allRealReports;
        GivenReport newReport;
        int pos = 0;
        string line = read();
        while (line != "done") {
            pos = line.find(',');
            newReport.startTimeStep =  stoi(line.substr(0,pos));
            line.erase(0, pos + 1);
            newReport.endTimeStep =  stoi(line);
            allRealReports.push_back(newReport);
            line = read();
        }
        return allRealReports;
    }
};

class StandardIO:public DefaultIO {
    virtual string read() {
        string s;
        cin >> s;
        return s;
    }

    virtual void write(string text) {
        cout << text << endl;
    }

    virtual void write(float f) {
        cout << f << endl;
    }

    virtual void read(float* f) {
        size_t pos = 0;
        int i = 0;
        string all_floats = read();
        string val;

        while ((pos = all_floats.find(',')) != string::npos) {
            val = all_floats.substr(0,pos);
            f[i] = stof(val);
            all_floats.erase(0, pos + 1);
            i++;
        }
        f[i] = stof(all_floats);
    }
};




// you may edit this class
class Command{
protected:
    DefaultIO* dio;
public:
    const string description;
    Command(DefaultIO* dio, string description):dio(dio), description(description){}
	virtual void execute(DetectorFeatures* df)=0;
	virtual ~Command(){}
};


class UploadCSV:public Command {
public:
    UploadCSV(DefaultIO* dio): Command(dio, "upload a time series csv file"){}
    virtual void execute(DetectorFeatures* df){
        dio->write("Please upload your local train CSV file.");
        dio->createFile("trainCSV.csv");
        TimeSeries* trainTable = new TimeSeries("TrainSCV.csv");
        df->testTS = *trainTable;
        dio->write("Upload complete.");
        dio->write("Please upload your local test CSV file.");
        dio->createFile("testCSV.csv");
        TimeSeries* testTable = new TimeSeries("TestSCV.csv");
        df->testTS = *testTable;
        dio->write("Upload complete.");
    }
};


class SetCorrelationSettings:public Command {
public:
    SetCorrelationSettings(DefaultIO* dio): Command(dio, "algorithm settings"){}
    virtual void execute(DetectorFeatures* df){
        dio->write("The current correlation threshold is " + to_string(df->threshold) + "\n");
        float newThresh = stof(dio->read());
        while ((newThresh < 0) || (newThresh > 1)) {
            dio->write("please choose a value between 0 and 1.\n");
            newThresh = stof(dio->read());
        }
        df->threshold = newThresh;
    }
};


class RunDetector:public Command {
public:
    RunDetector(DefaultIO* dio): Command(dio, "detect anomalies"){}
    virtual void execute(DetectorFeatures* df){
        HybridAnomalyDetector* hd = new HybridAnomalyDetector();
        hd->setThreshold(df->threshold);
        hd->learnNormal(*df->trainTS);
        df->anomalyReport = hd->detect(df->testTS);
        dio->write("anomaly detection complete.");
    }
};


class PresentAnomalies:public Command {
public:
    PresentAnomalies(DefaultIO* dio): Command(dio, "display results"){}
    virtual void execute(DetectorFeatures* df){
        vector<AnomalyReport>::iterator  it;
        for(it = df->anomalyReport.begin(); it != df->anomalyReport.end(); it++) {
            dio->write(to_string(it->timeStep) + "\t" + it->description);
        }
        dio->write("Done.");
    }
};

class UploadAnomaliesAndAnalyze:public Command {
public:
    UploadAnomaliesAndAnalyze(DefaultIO* dio): Command(dio, "Upload anomalies and analyze results"){}
    virtual void execute(DetectorFeatures* df){
        dio->write("Please upload your local anomalies file.");
        vector<GivenReport> realReports = dio->createRealReportVector();
        dio->write("Upload complete.");
        vector<CompressReport> compressedReports = compressR(df->anomalyReport);
        for (int i = 0; i < compressedReports.size(); ++i) {
            bool realDetection = false;
            for (int j = 0; j < realReports.size(); ++j) {
                if (checkCrossSection(realReports[j].startTimeStep, realReports[j].endTimeStep,
                                      compressedReports[i].startTimeStep, compressedReports[i].endTimeStep)) {
                    realDetection = true;
                    realReports[j].isExistAnyDetectForThisReport = true;
                }
            }
            compressedReports[i].isReal = realDetection;
        }
        int P = realReports.size();
        int sum = 0;
        int TP = 0;
        for (int i = 0; i < realReports.size(); ++i) {
            sum += realReports[i].endTimeStep + 1 - realReports[i].startTimeStep;
            if (realReports[i].isExistAnyDetectForThisReport) {
                TP++;
            }
        }
        int N = df->testTS.numOfRows() - sum;
        int FP = 0;
        for (int i = 0; i < compressedReports.size(); ++i) {
            if (!compressedReports[i].isReal) {
                FP++;
            }
        }
        float TPR = ((int)(1000.0*TP/P))/1000.0f;
        float FPR = ((int)(1000.0*FP/N))/1000.0f;
        dio->write("True Positive Rate: " + to_string(TPR) + "\n");
        dio->write("False Positive Rate: " + to_string(FPR) + "\n");
    }

    bool checkCrossSection(int realReportStart,int realReportEnd,int givenReportStart, int givenReportEnd){
        return (givenReportStart >= realReportStart && realReportEnd >= givenReportEnd);
    }// TODO semi section

    vector<CompressReport> compressR(vector<AnomalyReport> anomalyReport) {
        vector<CompressReport> compressReports;
        CompressReport newCompress;
        newCompress.startTimeStep = anomalyReport[0].timeStep;
        int curTime = newCompress.startTimeStep;
        newCompress.description = anomalyReport[0].description;
        for(int i = 1; i < anomalyReport.size(); i++) {
            if (anomalyReport[i].timeStep == curTime + 1 && newCompress.description == anomalyReport[i].description) {
                curTime++;
            } else {
                newCompress.endTimeStep = curTime - 1;
                compressReports.push_back(newCompress);
                newCompress.startTimeStep = anomalyReport[i].timeStep;
                curTime = newCompress.startTimeStep;
                newCompress.description = anomalyReport[i].description;
            }
        }
        newCompress.endTimeStep = curTime - 1;
        compressReports.push_back(newCompress);
        return compressReports;
    }
};

class Exit:public Command{
public:
    Exit(DefaultIO* dio):Command(dio,"exit"){}
    virtual void execute(DetectorFeatures* df){}
};


#endif /* COMMANDS_H_ */
