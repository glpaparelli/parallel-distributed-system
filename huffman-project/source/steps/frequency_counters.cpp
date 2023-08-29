#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <cstring>
#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>

#include "../headers/steps/frequency_counters.hpp"

using namespace std;

vector<int> frequency_counters::sequential_counter(
    const string &s, 
    const int start, 
    const int end)
{
    // Vector of size 256 (as much as ASCII chars) inizialized with 0
    vector<int> char_frequancy = vector<int>(256, 0);

    // vector[char] -> frequency of char
    for(int i = start; i < end; i++){
        int char_index = static_cast<unsigned char>(s[i]);
        char_frequancy[char_index]++;
    }

    return char_frequancy;
}

vector <int> frequency_counters::multithread_counter(const string &s, const int num_threads) {
    /**
     * we use je_malloc to allocate memory for each chunk of the text. 
     * this ensures that each thread has its own memory space to work with, 
     * reducing the contention for accessing the heap and improving performance.
    */

    vector<vector<int>> partial_frequency(num_threads);

    // static load balancing: the task are equally complex and distributed
    vector<thread> threads;
    int start = 0; 
    int chunk_size = s.size() / num_threads;
    int end = chunk_size;

    // counting chars for each chunk
    for(int i = 0; i < num_threads; i++){
        // the last thread may get a a smaller chunk
        if(i == num_threads - 1)
            end = s.size();

        // creates a new thread
        threads.push_back(thread(
            // define a function to compute the frequency for a chunk of text
            [&partial_frequency, i, &s, start, end](){
                partial_frequency[i] = sequential_counter(s, start, end);
            }));

        start = end; 
        end = end + chunk_size;
    }

    // we merge the partial results into the frequency "map"
    vector<int> char_frequancy = vector<int>(256, 0);
    for(int i = 0; i < num_threads; i++){
        threads[i].join();

        for(int k = 0; k < 256; k++)
            char_frequancy[k] = char_frequancy[k] + partial_frequency[i][k];
    }

    return char_frequancy;
}

vector<int> frequency_counters::fastflow_counter(const string &s, const int num_workers) {
    vector<int> char_frequency = vector<int>(256, 0);
    ff::ParallelForReduce<vector<int>> ffForReduce(num_workers);

    // parallel_reduce_static divides the range of elements into fixed-size chunks
    // and assigns each chunk to a thread for parallel processing. 
    // The reduction operation is performed in parallel on each chunk, 
    // and the partial results are combined using the merging operation to obtain the final result.
    ffForReduce.parallel_reduce_static(
        char_frequency, // accumulator
        vector<int>(256, 0), // identity value
        0, // first value of the iteration variable
        s.size(), // last value of the iteration variable 
        1, // step size
        0, // grain: min amount of work to each worker
        [&s](const long i, vector<int> &partial){
            // counting step
            int c_int = static_cast<unsigned char>(s[i]);
            partial[c_int]++;
        },
        [](vector<int> &char_frequency, const vector<int> &partial){
            // merging step
            for (int i = 0; i < 256; i++)
                char_frequency[i] += partial[i];
        },
        num_workers
    );

    return char_frequency;
}