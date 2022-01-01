

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DetectorFeatures{
public:
    float threshold;
    TimeSeries* trainTS, testTS;
    vector<AnomalyReport> report;

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
    UploadCSV(DefaultIO* dio): Command(dio, "Uploads a CSV"){}
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


class SetCorrelation:public Command {
public:
    SetCorrelation(DefaultIO* dio): Command(dio, "Updates correlation threshold"){}
    virtual void execute(DetectorFeatures* df){
        dio->write("The current correlation threshold is " + to_string(df->threshold));
        float newThresh = stof(dio->read());
        while ((newThresh < 0) || (newThresh > 1)) {
            dio->write("please choose a value between 0 and 1.");
            newThresh = stof(dio->read());
        }
        df->threshold = newThresh;
    }
};


class RunDetector:public Command {
public:
    RunDetector(DefaultIO* dio): Command(dio, "Executes the detector"){}
    virtual void execute(DetectorFeatures* df){
        HybridAnomalyDetector* hd = new HybridAnomalyDetector();
        hd->setThreshold(df->threshold);
        hd->learnNormal(*df->trainTS);
        df->report = hd->detect(df->testTS);
        dio->write("anomaly detection complete.");
    }
};


class PresentAnomalies:public Command {
public:
    PresentAnomalies(DefaultIO* dio): Command(dio, "Presents all anomalies found"){}
    virtual void execute(DetectorFeatures* df){
        vector<AnomalyReport>::iterator  it;
        for(it = df->report.begin(); it != df->report.end(); it++) {
            dio->write(to_string(it->timeStep) + "\t" + to_string(it->description));
        }
        dio->write("Done.");
    }
};


#endif /* COMMANDS_H_ */
