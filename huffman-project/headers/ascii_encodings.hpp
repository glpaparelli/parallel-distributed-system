#ifndef ASCII_ENCODINGS_HPP
#define ASCII_ENCODINGS_HPP

#include <string>
#include <iostream>

using namespace std; 

namespace ascii_encodings{
    /// @brief Sequentially "convert" a binary string to a string in ASCII
    /// @param s String to be converted
    /// @param start Starting point
    /// @param end Ending of the string
    /// @return The converted ASCCI string
    string sequential_binary_to_ASCII(const string &s, const int start, const int end);

    /// @brief Multithreadlly "convert" a binary string to a string in ASCII
    /// @param s String to be converted
    /// @param num_thread Number of threads to use
    /// @param chunk_size Size of the string chunk assigned to each thread
    /// @return The converted ASCII string
    string multithread_binary_to_ASCII(const string &s, const int num_threads, const int chunk_size);
}

#endif