#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <cstring>
#include <jemalloc/jemalloc.h>
#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>

#include "../headers/huffman_encodings.hpp"

using namespace std; 

string huffman_encodings::sequential_string_to_binary(
    const string &s, 
    const int start, 
    const int end, 
    const vector<string> &huffman_map)
{
    string s_encoded = "";
 
    for(int i = start; i < end; i++)
        s_encoded += huffman_map[static_cast<unsigned char>(s[i])];
    
    return s_encoded;
}

string huffman_encodings::multithread_string_to_binary(
    const string &s, 
    const int num_threads, 
    const vector<string> &huffman_map)
{   
    vector<string> chunks_encoded(num_threads);

    // static load balancing: the task are equally complex and distributed
    vector<thread> threads; 
    int chunk_size = s.size() / num_threads;
    int start = 0; 
    int end = chunk_size;

    for (int i = 0; i < num_threads; i++) {
        if (i == num_threads - 1)
            end = s.length();

        threads.push_back(thread(
            [&chunks_encoded, i, &s, start, end, huffman_map]() {
                chunks_encoded[i] = sequential_string_to_binary(s, start, end, huffman_map);
            }));

        start = end;
        end += chunk_size;
    }

    string s_encoded = "";
    for(int i = 0; i < num_threads; i++){
        threads[i].join();
        s_encoded += chunks_encoded[i];
    }

    return s_encoded;
}

string huffman_encodings::fastflow_string_to_binary(
    const string &s, 
    const int num_workers,
    const vector<string> huffman_map)
{
    string s_encoded = "";

    ff::ParallelForReduce<string> ffForReduce(num_workers);

    // parallel_reduce_static divides the range of elements into fixed-size chunks
    // and assigns each chunk to a thread for parallel processing. 
    // The reduction operation is performed in parallel on each chunk, 
    // and the partial results are combined using the merging operation to obtain the final result.
    ffForReduce.parallel_reduce_static(
        s_encoded, // accumulator
        "", // identity value
        0, // first value of the iteration variable
        s.size(), // last value of the iteration variable 
        1, // step size
        0, // grain: min amount of work to each worker
        [&huffman_map, &s](const long i, string &partial){
            // encoding step
            int pos = static_cast<unsigned char>(s[i]);
            partial += huffman_map[pos];
        },
        [](string &s_encoded, const string &partial){
            // merging step
            s_encoded += partial;
        },
        num_workers);

    return s_encoded;
}


void huffman_encodings::add_padding(string &s){
    // ASCII characters are 8 bits, hence the length of 
    // the original input s is a multiple of 8. 
    // this is not true once we created the Huffman code, as 
    // characters have a shorter representation based on their
    // frequence in the s. 
    // hence we have to add a padding to the encoded s
    int padding = 8 - (s.size() % 8);
    s += string(padding, '0');
}