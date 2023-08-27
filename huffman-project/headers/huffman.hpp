#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <chrono>
#include <vector>

using namespace std; 
using namespace chrono;

namespace huffman{
    vector<duration<double>> sequential_huffman(
        const string file_name 
    );

    vector<duration<double>> multithread_huffman(
        const string file_name, 
        const int num_threads
    );

    vector<duration<double>> fastflow_huffman(
        const string file_name, 
        const int num_threads
    );
}

#endif