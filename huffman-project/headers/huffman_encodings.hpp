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
    /// @param huffmanMap Huffman Map char -> huffman code
    /// @return The encoded string
    string seqStringToBinary(
        const string &s, 
        const int start, 
        const int end, 
        const vector<string> &huffmanMap
    );
}

#endif