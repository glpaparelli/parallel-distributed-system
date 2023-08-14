#include <iostream>
#include <vector>

#include "../headers/frequency_counters.hpp"

using namespace std;

vector<int> frequency_counters::seqCounter(const string &s, const int start, const int end){
    // Vector of size 256 (as much as ASCII chars) inizialized with 0
    vector<int> char_frequancy = vector<int>(256, 0);

    for(int i = start; i < end; i++){
        int char_index = static_cast<unsigned char>(s[i]);
        char_frequancy[char_index]++;
    }

    return char_frequancy;
}