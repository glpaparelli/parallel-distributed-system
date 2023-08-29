#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <chrono>
#include <vector>

using namespace std; 
using namespace chrono;

namespace huffman{
    /// @brief Compute the huffman encoding on the given file
    /// @param file_name Name of the file to apply Huffman
    /// @return The vector of timings needed to complete
    vector<duration<double>> sequential_huffman(
        const string file_name 
    );

    /// @brief Compute the huffman encoding on the given file
    /// @param file_name Name of the file to apply Huffman
    /// @return The vector of timings needed to complete
    vector<duration<double>> multithread_huffman(
        const string file_name, 
        const int num_threads
    );

    /// @brief Compute the huffman encoding on the given file
    /// @param file_name Name of the file to apply Huffman
    /// @return The vector of timings needed to complete
    vector<duration<double>> fastflow_huffman(
        const string file_name, 
        const int num_threads
    );
}

#endif