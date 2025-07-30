#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <queue>
#include <cmath>
#include <map>
#include <tuple>
// #include<bits/stdc++.h>
#include "types.h"
#include "parser.h"

using namespace std;

bool compareByArrival(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

void firstComeFirstServe(vector<Process>& processes) {
    int currentTime = 0;
    for (auto& process : processes) {
        if (process.arrivalTime > currentTime) {
            currentTime = process.arrivalTime;
        }
        process.finishTime = currentTime + process.serviceTime;
        process.turnaroundTime = process.finishTime - process.arrivalTime;
        process.waitingTime = process.turnaroundTime - process.serviceTime;
        currentTime = process.finishTime;
    }
}

void roundRobin(vector<Process>& processes, int quantum) {
    if (processes.empty()) return;
    for(auto& process : processes) process.remainingTime = process.serviceTime;

    queue<int> readyQueue;
    int currentTime = 0;
    size_t completed = 0;
    size_t nextProcessIdx = 0;

    while (completed < processes.size()) {
        while (nextProcessIdx < processes.size() && processes[nextProcessIdx].arrivalTime <= currentTime) {
            readyQueue.push(nextProcessIdx++);
        }

        if (readyQueue.empty()) {
            currentTime = processes[nextProcessIdx].arrivalTime;
            continue;
        }

        int currentIdx = readyQueue.front();
        readyQueue.pop();
        Process& process = processes[currentIdx];

        int timeSlice = min(quantum, process.remainingTime);
        currentTime += timeSlice;
        process.remainingTime -= timeSlice;

        while (nextProcessIdx < processes.size() && processes[nextProcessIdx].arrivalTime <= currentTime) {
            readyQueue.push(nextProcessIdx++);
        }

        if (process.remainingTime == 0) {
            process.finishTime = currentTime;
            process.turnaroundTime = process.finishTime - process.arrivalTime;
            process.waitingTime = process.turnaroundTime - process.serviceTime;
            completed++;
        } else {
            readyQueue.push(currentIdx);
        }
    }
}

void shortestJobFirst(vector<Process>& processes) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> readyQueue;
    int currentTime = 0;
    size_t completed = 0;
    size_t nextProcessIdx = 0;

    while (completed < processes.size()) {
        while (nextProcessIdx < processes.size() && processes[nextProcessIdx].arrivalTime <= currentTime) {
            readyQueue.push({processes[nextProcessIdx].serviceTime, nextProcessIdx});
            nextProcessIdx++;
        }

        if (readyQueue.empty()) {
            currentTime = processes[nextProcessIdx].arrivalTime;
            continue;
        }

        int currentIdx = readyQueue.top().second;
        readyQueue.pop();
        Process& process = processes[currentIdx];

        currentTime += process.serviceTime;
        process.finishTime = currentTime;
        process.turnaroundTime = process.finishTime - process.arrivalTime;
        process.waitingTime = process.turnaroundTime - process.serviceTime;
        completed++;
    }
}

void shortestRemainingTimeNext(vector<Process>& processes) {
    if (processes.empty()) return;
    for(auto& p : processes) p.remainingTime = p.serviceTime;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> readyQueue;
    int currentTime = 0;
    size_t completed = 0;
    size_t nextProcessIdx = 0;

    while (completed < processes.size()) {
        while (nextProcessIdx < processes.size() && processes[nextProcessIdx].arrivalTime <= currentTime) {
            readyQueue.push({processes[nextProcessIdx].remainingTime, nextProcessIdx});
            nextProcessIdx++;
        }

        if (readyQueue.empty()) {
            currentTime = processes[nextProcessIdx].arrivalTime;
            continue;
        }

        int currentIdx = readyQueue.top().second;
        readyQueue.pop();
        Process& process = processes[currentIdx];

        currentTime++;
        process.remainingTime--;

        if (process.remainingTime == 0) {
            process.finishTime = currentTime;
            process.turnaroundTime = process.finishTime - process.arrivalTime;
            process.waitingTime = process.turnaroundTime - process.serviceTime;
            completed++;
        } else {
            readyQueue.push({process.remainingTime, currentIdx});
        }
    }
}

void highestResponseRatioNext(vector<Process>& processes) {
    int currentTime = 0;
    size_t completed = 0;
    vector<bool> isCompleted(processes.size(), false);

    while(completed < processes.size()) {
        int bestProcessIdx = -1;
        double maxResponseRatio = -1.0;

        for (size_t i = 0; i < processes.size(); ++i) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                int waitingTime = currentTime - processes[i].arrivalTime;
                double responseRatio = (double)(waitingTime + processes[i].serviceTime) / processes[i].serviceTime;
                if (responseRatio > maxResponseRatio) {
                    maxResponseRatio = responseRatio;
                    bestProcessIdx = i;
                }
            }
        }
                
        if (bestProcessIdx == -1) {
            int nextArrivalTime = -1;
            for(size_t i = 0; i < processes.size(); ++i) {
                if(!isCompleted[i]) {
                    if(nextArrivalTime == -1 || processes[i].arrivalTime < nextArrivalTime) {
                        nextArrivalTime = processes[i].arrivalTime;
                    }
                }
            }
            currentTime = nextArrivalTime;
            continue;
        }

        Process& process = processes[bestProcessIdx];
        currentTime += process.serviceTime;
        process.finishTime = currentTime;
        process.turnaroundTime = process.finishTime - process.arrivalTime;
        process.waitingTime = process.turnaroundTime - process.serviceTime;
        isCompleted[bestProcessIdx] = true;
        completed++;
    }
}

void printStatsTable(const vector<Process>& processes) {
    if (processes.empty()) return;
    cout << left << setw(10) << "Process" << setw(10) << "| Arrival" << setw(10) << "| Service"
         << setw(9)  << "| Finish" << setw(13) << "| Turnaround" << setw(11) << "| Waiting  |" << endl;
    float totalTurnaround = 0, totalWaitingTime = 0;
    for (const auto& p : processes) {
        totalTurnaround += p.turnaroundTime;
        totalWaitingTime += p.waitingTime;
        cout << left << setw(10) << p.name << "| " << left << setw(8) << p.arrivalTime << "| " << left << setw(8) << p.serviceTime
             << "| " << left << setw(7) << p.finishTime << "| " << left << setw(11) << p.turnaroundTime
             << "| " << left << setw(9) << p.waitingTime << "|" << endl;
    }
    cout << string(75, '-') << endl;
    float meanTurnaround = (processes.size() > 0) ? totalTurnaround / processes.size() : 0;
    float meanWaitingTime = (processes.size() > 0) ? totalWaitingTime / processes.size() : 0;
    cout << left << setw(11) << "Mean" << setw(10) << "| " << setw(10) << "| " << setw(9)  << "| "
         << "| " << left << setw(11) << fixed << setprecision(2) << meanTurnaround
         << "| " << left << setw(9) << fixed << setprecision(2) << meanWaitingTime << "|" << endl;
}

void executeAlgorithm(vector<Process>& processes, const AlgorithmParams& params) {
    const char* names[] = {"", "FCFS", "RR", "SJF", "SRTN", "HRRN"};
    if (params.id > 0 && params.id < 6) {
        cout << names[params.id];
        if (params.id == 2) cout << "-" << params.quantum;
        cout << endl;
    }

    sort(processes.begin(), processes.end(), compareByArrival);

    switch (params.id) {
        case 1: firstComeFirstServe(processes); break;
        case 2: roundRobin(processes, params.quantum); break;
        case 3: shortestJobFirst(processes); break;
        case 4: shortestRemainingTimeNext(processes); break;
        case 5: highestResponseRatioNext(processes); break;
        default: break;
    }
}

int main() {
    SchedulerData data = parse();
    
    for (const auto& params : data.algorithmQueue) {
        vector<Process> currentProcesses = data.processes; 

        executeAlgorithm(currentProcesses, params);
        
        printStatsTable(currentProcesses);
        cout << "\n";
    }

    return 0;
}