#ifndef FREQUENCY_COUNTERS_HPP
#define FREQUENCY_COUNTERS_HPP

#include <vector>
#include <string>

using namespace std;

namespace frequency_counters{
    /// @brief Sequentially compute the frequency of chars in a string
    /// @param s String of which we want the char frequency
    /// @param start Start index of the string
    /// @param end End index of the string
    /// @return Vector that associate the char to its occurrences
    vector<int> sequential_counter(const string &s, const int start, const int end);

    /// @brief Compute the frequency of chars in a string with multi-threading
    /// @param s String of which we want the char frequency
    /// @param num_thread Number of threads to use
    /// @param chunk_size Size of the string chunk assigned to each thread
    /// @return Vector that associate the char to its occurrences
    vector<int> multithread_counter(const string &s, const int num_threads, const int chunk_size);
}

#endif