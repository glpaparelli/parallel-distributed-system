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

    /// @brief Multithreadlly compute the encoding of a string: each char of the string to its huffman code
    /// @param s String to be encoded 
    /// @param num_thread Number of threads to use
    /// @param huffman_map Huffman Map char -> Huffman code
    /// @return The vector encoded chunks
    /// @return The encoded string
    string multithread_string_to_binary(
        const string &s, 
        const int num_thread, 
        const vector<string> &huffman_map
    );

    /// @brief Compute the encoding of a string using FF: each char of the string to its huffman code
    /// @param s String to be encoded 
    /// @param huffman_map Huffman Map char -> Huffman code
    /// @param num_workers Number of workers to use
    /// @return The encoded string
    string fastflow_string_to_binary(
        const string &s, 
        const int num_workers,
        const vector<string> huffman_map
    );
    
    /// @brief Encoded strings are not anymore multiple of 8, hence we add a padding
    /// @param s String to which we add the padding
    void add_padding(string &s);
}

#endif