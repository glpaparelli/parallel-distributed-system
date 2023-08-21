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
    /// @return Vector that associate the char to its occurrences
    vector<int> multithread_counter(const string &s, const int num_threads);

    /// @brief Compute the frequency of chars in a string with FastFlow
    /// @param s String of which we want the char frequency
    /// @param num_thread Number of threads to use
    /// @return Vector that associate the char to its occurrences
    vector<int> fastflow_counter(const string &s, const int num_workers);
}

#endif