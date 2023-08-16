#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <cstring>
#include <jemalloc/jemalloc.h>

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
        s_encoded = s_encoded + huffman_map[static_cast<unsigned char>(s[i])];
    
    return s_encoded;
}

string huffman_encodings::multithread_string_to_binary(
    const string &s, 
    const int num_threads, 
    const int chunk_size, 
    const vector<string> &huffman_map)
{   
    vector<string> chunks_encoded(num_threads);

    // static load balancing: the task are equally complex and distributed
    vector<thread> threads; 
    int start = 0; 
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
            [&chunks_encoded, i, &s, start, end, huffman_map](){
                // allocate the memory for the chunk
                char *chunk = (char *) malloc(end - start + 1); 

                // copy and add limiter to the chunk
                strncpy(chunk, s.c_str() + start, end - start);
                chunk[end - start] = '\0';

                // compute the task 
                chunks_encoded[i] = sequential_string_to_binary(chunk, 0, end - start, huffman_map);

                // free the memory allocated to the chunk
                free(chunk);
            }));

        start = end; 
        end = end + chunk_size;
    }

    string result = "";
    for(int i = 0; i < num_threads; i++){
        threads[i].join();
        result = result + chunks_encoded[i];
    }

    return result;
}