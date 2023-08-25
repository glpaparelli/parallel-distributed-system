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
    string s_encoded = "";
    for (int i = start; i < end; i += 8){
        bitset<8> bits(s.substr(i, 8));
        s_encoded += char(bits.to_ulong());
    }

    return s_encoded;
}

string ascii_encodings::multithread_binary_to_ASCII(const string &s, const int num_threads) {
    vector<string> chunks_in_ascii(num_threads);

    // static load balancing: the task are equally complex and distributed
    vector<thread> threads; 
    int start = 0; 
    int chunk_size = s.size() / num_threads;
    chunk_size -= chunk_size % 8;
    int end = chunk_size;

    // Encoding
    for (int i = 0; i < num_threads; i++) {
        if (i == num_threads - 1)
            end = s.size();

        threads.push_back(thread(
            [&chunks_in_ascii, i, &s, start, end]() {
                chunks_in_ascii[i] = sequential_binary_to_ASCII(s, start, end);
            }));

        start = end;
        end += chunk_size;
    }

    string s_encoded = "";
    for(int i = 0; i < num_threads; i++){
        threads[i].join();
        s_encoded += chunks_in_ascii[i];
    }

    return s_encoded;
}

string ascii_encodings::fastflow_binary_to_ASCII(const string &s, const int num_workers){
    vector<string> chunks_in_ascii(num_workers);
    // round down to the closest multiple of 8 (as ASCII are 8 bits)
    int chunk_size = s.size() / num_workers;
    chunk_size -= chunk_size % 8;

    ff::ParallelFor ffFor(num_workers);
    ffFor.parallel_for_static(
        0, // first
        num_workers, // last
        1, // step
        0, // grain
        [chunk_size, num_workers, &chunks_in_ascii, &s](const long i){
            int start = i * chunk_size;
            int end = start + chunk_size;

            if (i == num_workers - 1)
                end = s.length();

            chunks_in_ascii[i] = sequential_binary_to_ASCII(s, start, end);
        }
    );

    string s_encoded = "";
    for (int i = 0; i < num_workers; i++)
        s_encoded += chunks_in_ascii[i];

    return s_encoded;
}
