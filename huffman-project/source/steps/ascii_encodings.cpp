#include <string>
#include <vector>
#include <thread>
#include <cstring>
#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>
#include <bitset>

#include "../headers/steps/ascii_encodings.hpp"

using namespace std; 

string ascii_encodings::sequential_binary_to_ASCII(const string &s, const int start, const int end) {        
    string s_encoded; 
    s_encoded.reserve(s.length()/8);

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

        // Each threads compute its chunk
        threads.push_back(thread(
            [&chunks_in_ascii, i, &s, start, end]() {
                chunks_in_ascii[i] = sequential_binary_to_ASCII(s, start, end);
            }));

        start = end;
        end += chunk_size;
    }

    // Merge the results computed by the threads
    unsigned int size = 0;
    for(int i = 0; i < num_threads; i++){
        threads[i].join();
        size += chunks_in_ascii[i].length();
    }

    string s_encoded;
    s_encoded.reserve(size);
    unsigned int i_insert = 0; 
    for(int i = 0; i < chunks_in_ascii.size(); i++){
        s_encoded += chunks_in_ascii[i];
    }

    return s_encoded;
}

string ascii_encodings::fastflow_binary_to_ASCII(const string &s, const int num_threads){
    vector<string> chunks_in_ascii(num_threads);
    // round down to the closest multiple of 8 (as ASCII are 8 bits)
    int chunk_size = s.size() / num_threads;
    chunk_size -= chunk_size % 8;

    // Encoding phase
    ff::ParallelFor ffFor(num_threads);
    ffFor.parallel_for_static(
        0, // first
        num_threads, // last
        1, // step
        0, // grain
        [chunk_size, num_threads, &chunks_in_ascii, &s](const long i){
            int start = i * chunk_size;
            int end = start + chunk_size;

            if (i == num_threads - 1)
                end = s.length();

            chunks_in_ascii[i] = sequential_binary_to_ASCII(s, start, end);
        }
    );
   
    // Merge the results computed by the threads
    unsigned int size = 0;
    for(int i = 0; i < num_threads; i++)
        size += chunks_in_ascii[i].length();
    
    string s_encoded;
    s_encoded.reserve(size);
    unsigned int i_insert = 0; 
    for(int i = 0; i < chunks_in_ascii.size(); i++)
        s_encoded += chunks_in_ascii[i];
    
    return s_encoded;
}
