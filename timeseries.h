

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class TimeSeries{
public:
    vector<vector<string>> table;

    TimeSeries(const char* CSVfileName){
        ifstream csvData;
        csvData.open(CSVfileName);
        if (csvData.fail()) {
            cout << "YES";
        }
        size_t pos;
        string field;
        string line;
        int i = 0;
        while (csvData.good()) {
            getline(csvData, line, '\n');
            table.push_back(vector<string>());
            pos = 0;
            while ((pos = line.find(',')) != string::npos) {
                field = line.substr(0,pos);
                table[i].push_back(field);
                line.erase(0, pos + 1);
            }
            table[i].push_back(line);
            i++;
            cout << "HI" << "";

        }
    }

    vector<vector<string>> getTable() const {
        return this->table;
    }

    int numOfFeatures() const{
        return this->table[0].size();
    }

    int numOfRows() const{
        return this->table.size();
    }

    int getFeatureNum(string feature) const{
        for (int i = 0; i < numOfFeatures(); i++) {
            if (this->table[0][i] == feature) {
                return i;
            }
        }
        return -1;
    }

    string getFeatureName(int index) const{
        return this->table[0][index];
    }

    float* getValueVector(const string& feature) const{
        float* values = new float[numOfRows()];
        // Start from 1 to ignore feature names
        for (int i = 1; i < numOfRows(); i++) {
            values[i] = stof(this->table[i][getFeatureNum(feature)]);
        }
        return values;
    }

    vector<float*> getAllValuesVectors() const{
        vector<float*> vec;
        for (int i = 0; i < numOfFeatures(); i++) {
            vec.push_back(getValueVector(getFeatureName(i)));
        }
        return vec;
    }
};



#endif /* TIMESERIES_H_ */

