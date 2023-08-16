#include <string>
#include <vector>
#include <jemalloc/jemalloc.h>
#include <thread>
#include <cstring>

#include "../headers/ascii_encodings.hpp"

using namespace std; 

string ascii_encodings::sequential_binary_to_ASCII(const string &s, const int start, const int end) {
    string s_ascii = "";

    for(int i = 0; i < s.size(); i += 8){
        string byte = s.substr(i, 8);
        // the stoi function takes three arguments: 
        // the string to convert
        // a pointer to an int to store the converted value
        // the base of the number system (in this case, 2 for binary).
        char c = static_cast<char>(stoi(byte, nullptr, 2));
        s_ascii += c; 
    }

    return s_ascii;
}

string ascii_encodings::multithread_binary_to_ASCII(const string &s, const int num_threads, const int chunk_size) {
    vector<string> chunks_in_ascii(num_threads);

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
        end = end + chunk_size;
    }

    string result = "";
    for(int i = 0; i < num_threads; i++){
        threads[i].join();
        result = result + chunks_in_ascii[i];
    }

    return result;
}