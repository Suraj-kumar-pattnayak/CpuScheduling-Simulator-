#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "types.h"

struct SchedulerData {
    std::vector<AlgorithmParams> algorithmQueue;
    std::vector<Process> processes;
};

SchedulerData parse() {
    SchedulerData data;
    std::string algorithm_chunk;
    int process_count;

    std::cin >> algorithm_chunk;
    std::cin >> process_count;

    std::stringstream algo_stream(algorithm_chunk);
    std::string segment;
    while (getline(algo_stream, segment, ',')) {
        std::stringstream segment_stream(segment);
        std::string id_str, quantum_str;
        
        getline(segment_stream, id_str, '-');
        getline(segment_stream, quantum_str);

        char id_char = id_str.empty() ? '0' : id_str[0];
        int id_num = (id_char >= '1' && id_char <= '5') ? (id_char - '0') : 0;
        
        int quantum = !quantum_str.empty() ? stoi(quantum_str) : 0;
        if(id_num != 0) {
             data.algorithmQueue.push_back({id_num, quantum});
        }
    }

    for (int i = 0; i < process_count; i++) {
        std::string process_chunk, name_str, arrival_str, service_str;
        std::cin >> process_chunk;
        std::stringstream proc_stream(process_chunk);

        getline(proc_stream, name_str, ',');
        getline(proc_stream, arrival_str, ',');
        getline(proc_stream, service_str, ',');
        
        data.processes.push_back({
            name_str,
            stoi(arrival_str),
            stoi(service_str)
        });
    }
    
    return data;
}

#endif // PARSER_H_INCLUDED