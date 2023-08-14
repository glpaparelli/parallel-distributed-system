#ifndef HUFFMAN_MAP_HPP
#define HUFFMAN_MAP_HPP

#include <vector>
#include <string>
#include "huffman_tree.hpp"

using namespace std; 

namespace huffman_map{
    /// @brief Creates the map as the vector[character] = code
    /// @param root The root of the Huffman Tree
    /// @return Return the map as the vector[character] = code
    vector<string> getHuffmanMap(huffman_tree::Node* root);
}

#endif 
