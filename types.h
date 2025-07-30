#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <string>
#include <vector>
using namespace std;

struct Process {
    string name;
    int arrivalTime;
    int serviceTime;

    int finishTime = 0;
    int turnaroundTime = 0;
    int waitingTime = 0;

    int remainingTime = 0;
};

struct AlgorithmParams {
    int id;
    int quantum;
};

#endif // TYPES_H_INCLUDED