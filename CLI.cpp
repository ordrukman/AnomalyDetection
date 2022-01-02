#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->allCommands.push_back(new UploadCSV(dio));
    this->allCommands.push_back(new SetCorrelationSettings(dio));
    this->allCommands.push_back(new RunDetector(dio));
    this->allCommands.push_back(new PresentAnomalies(dio));
    this->allCommands.push_back(new UploadAnomaliesAndAnalyze(dio));
    this->allCommands.push_back(new Exit(dio));
}

void CLI::start(){
    DetectorFeatures detectorFeatures;
    int userInput = 0;
    while (userInput != 6) {
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        for (int i = 0; i < this->allCommands.size(); ++i) {
            dio->write(to_string(i + 1) + "." + allCommands[i]->description + "\n");
        }
        string s = dio->read();
        //cout << s << endl;
        userInput = stoi(s);
        if (userInput <= allCommands.size() && userInput >= 1) {
            allCommands[userInput - 1]->execute(&detectorFeatures);
        }
    }
}


CLI::~CLI() {
    for(int i = 0; i < this->allCommands.size(); i++){
        delete this->allCommands[i];
    }
}


