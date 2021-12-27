#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
}

void CLI::start(){
    int userInput;
    while (true) {
        cout << "Welcome to the Anomaly Detection Server.\n"
                "Please choose an option:\n"
                "1. upload a time series csv file\n"
                "2. algorithm settings\n"
                "3. detect anomalies\n"
                "4. display results\n"
                "5. upload anomalies and analyze results\n"
                "6. exit" << endl;
        cin >> userInput;
        switch (userInput) {
            case 1:
                UploadCSV *uploadCSV = new UploadCSV(dio);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                return;
        }
    }
}


CLI::~CLI() {
}


