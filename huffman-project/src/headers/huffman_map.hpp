#ifndef HUFFMAN_MAP_HPP
#define HUFFMAN_MAP_HPP

#include <unordered_map>
#include <string>
#include "headers/huffman_tree.hpp"

using namespace std; 

namespace huffman_map{
    /// @brief Creates the map character -> Huffman code
    /// @param root The root of the Huffman Tree
    /// @return Return the map
    vector<string> getHuffmanMap(huffman_tree::Node* root);
}

#endif 
