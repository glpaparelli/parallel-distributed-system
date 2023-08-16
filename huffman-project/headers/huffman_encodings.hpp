#ifndef HUFFMAN_ENCODINGS_HPP
#define HUFFMAN_ENCODINGS_HPP

#include <string>
#include <vector>

using namespace std; 

namespace huffman_encodings{
    /// @brief Sequentially computes the encoding of a string: each char of the string to its huffman code
    /// @param s String to be encoded 
    /// @param start Starting index 
    /// @param end End index
    /// @param huffman_map Huffman Map char -> Huffman code
    /// @return The encoded string
    string sequential_string_to_binary(
        const string &s, 
        const int start, 
        const int end, 
        const vector<string> &huffman_map
    );

    /// @brief  Multithreadlly compute the encoding of a string: each char of the string to its huffman code
    /// @param s String to be encoded 
    /// @param num_thread Number of threads to use
    /// @param chunk_size Size of the string chunk assigned to each thread
    /// @param huffman_map Huffman Map char -> Huffman code
    /// @return The vector encoded chunks
    vector<string> multithread_string_to_binary(
        const string &s, 
        const int num_thread, 
        const int chunk_size, 
        const vector<string> &huffman_map
    );
}

#endif