/*
 * Or Drukman 209090000
 * Yotam Levin 313248916
 */


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
    TimeSeries(){};

    TimeSeries(const char* CSVfileName){

        // Load CSV
        ifstream csvData;
        csvData.open(CSVfileName);
        if (csvData.fail()) {
            cout << "FAILED";
        }
        size_t pos;
        string field;
        string line;
        int i = 0;

        // Read from CSV line by line
        while (csvData.good()) {
            getline(csvData, line, '\n');
            // Ignore last empty row
            if (line.size() < 2) {
                break;
            }
            table.push_back(vector<string>());
            pos = 0;

            // Read fields one by one
            while ((pos = line.find(',')) != string::npos) {
                field = line.substr(0,pos);
                table[i].push_back(field);
                line.erase(0, pos + 1);
            }
            table[i].push_back(line);
            i++;
        }
        csvData.close();
    }

    vector<vector<string>> getTable() const {
        return this->table;
    }

    int numOfFeatures() const{
        return this->table[0].size();
    }

    int numOfRows() const{
        return this->table.size()-1;
    }

    // Get the index of a certain feature
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

    // Get a vector of values for a certain feature
    float* getValueVector(const string& feature) const{
        float* values = new float[numOfRows()];
        int j = getFeatureNum(feature);

        // Start from 1 to ignore feature names
        for (int i = 1; i <= numOfRows(); i++) {
            values[i-1] = stof(this->table[i][j]);
        }
        return values;
    }

    // Return all vector values for all features
    vector<float*> getAllValuesVectors() const{
        vector<float*> vec;
        for (int i = 0; i < numOfFeatures(); i++) {
            vec.push_back(getValueVector(getFeatureName(i)));
        }
        return vec;
    }
};



#endif /* TIMESERIES_H_ */