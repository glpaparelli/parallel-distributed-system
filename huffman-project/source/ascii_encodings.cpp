#include <string>
#include <vector>
#include <jemalloc/jemalloc.h>
#include <thread>
#include <cstring>
#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>
#include <bitset>

#include "../headers/ascii_encodings.hpp"

using namespace std; 

string ascii_encodings::sequential_binary_to_ASCII(const string &s, const int start, const int end) {
    string result = "";
    for (int i = start; i < end; i += 8){
        bitset<8> bits(s.substr(i, 8));
        result += char(bits.to_ulong());
    }

    return result;
}

string ascii_encodings::multithread_binary_to_ASCII(const string &s, const int num_threads) {
    vector<string> chunks_in_ascii(num_threads);

    // static load balancing: the task are equally complex and distributed
    vector<thread> threads; 
    int start = 0; 
    int chunk_size = s.size() / num_threads;
    chunk_size -= chunk_size % 8;
    int end = chunk_size;

    // the string is divided in chunks and each 
    // chunk is encoded using the  huffman map
    for(int i = 0; i < num_threads; i++){
        // the last thread may get a a smaller chunk
        if(i == num_threads - 1)
            end = s.length();

        // creates a new thread
        threads.push_back(thread(
            // define a function to compute the frequency for a chunk of text
            [&chunks_in_ascii, i, &s, start, end](){
                // allocate the memory for the chunk
                char *chunk = (char *) malloc(end - start + 1); 

                // copy and add limiter to the chunk
                strncpy(chunk, s.c_str() + start, end - start);
                chunk[end - start] = '\0';

                // compute the task 
                chunks_in_ascii[i] = sequential_binary_to_ASCII(chunk, 0, end - start);

                // free the memory allocated to the chunk
                free(chunk);
            }));

        start = end; 
        end += chunk_size;
    }

    string result = "";
    for(int i = 0; i < num_threads; i++){
        threads[i].join();
        result += chunks_in_ascii[i];
    }

    return result;
}

string ascii_encodings::fastflow_binary_to_ASCII(const string &s, const int num_workers){
    vector<string> chunks_in_ascii(num_workers);

    // static load balancing: the task are equally complex and distributed
    ff::ParallelFor ffFor(num_workers);

    // round down to the closest multiple of 8 (as ASCII are 8 bits)
    int chunk_size = s.size() / num_workers;
    chunk_size -= chunk_size % 8;

    ffFor.parallel_for_static(
        0, 
        num_workers, 
        1, 
        0,
        [chunk_size, num_workers, &chunks_in_ascii, &s](const long i){
            int start = i * chunk_size;
            int end = start + chunk_size;

            if (i == num_workers - 1)
                end = s.length();

            chunks_in_ascii[i] = sequential_binary_to_ASCII(s, start, end);
        }
    );

    string result = "";
    for (int i = 0; i < num_workers; i++)
        result += chunks_in_ascii[i];

    return result;
}
