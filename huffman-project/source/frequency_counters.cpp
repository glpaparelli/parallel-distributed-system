#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <jemalloc/jemalloc.h>
#include <cstring>

#include "../headers/frequency_counters.hpp"

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

vector <int> frequency_counters::multithread_counter(
    const string &s, 
    const int num_threads, 
    const int chunk_size) 
{
    /**
     * we use je_malloc to allocate memory for each chunk of the text. 
     * this ensures that each thread has its own memory space to work with, 
     * reducing the contention for accessing the heap and improving performance.
    */
    
    vector<vector<int>> partial_frequency(num_threads);

    // static load balancing: the task are equally complex and distributed
    vector<thread> threads;
    int start = 0; 
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
                // allocate the memory for the chunk
                char *chunk = (char *) malloc(end - start + 1); 

                // copy and add limiter to the chunk
                strncpy(chunk, s.c_str() + start, end - start);
                chunk[end - start] = '\0';

                // compute the task
                partial_frequency[i] = sequential_counter(chunk, 0, end - start);

                // free the memory allocated to the chunk
                free(chunk);
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