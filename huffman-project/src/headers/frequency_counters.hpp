#ifndef FREQUENCY_COUNTERS_HPP
#define FREQUENCY_COUNTERS_HPP

#include <vector>
#include <string>

using namespace std;

namespace frequency_counters{
    /// @brief sequentially compute the frequency of chars in a string
    /// @param s string of which we want the char frequency
    /// @param start start index of the string
    /// @param end end index of the string
    /// @return vector of chars and their frequencies
    vector<int> seqCounter(const string &s, const int start, const int end);
}

#endif