#include <iostream>
#include "anomaly_detection_util.h"

using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;

    const int N=10;
    float x[]={1,2,3,4,5,6,7,8,9,10};
    float y[]={5,6,7,8,9,10,11,12,13,14};
    float temp = pearson(x, y, N);
    cout << temp;
    return 0;
}
