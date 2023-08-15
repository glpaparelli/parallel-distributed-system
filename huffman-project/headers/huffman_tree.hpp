#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

namespace huffman_tree{
    struct Node {
        char character;
        int frequency;
        Node* left;
        Node* right;

        /// @brief Constructor for the Node of the Huffman Tree
        /// @param character
        /// @param frequency 
        Node(char character, int frequency){
            this->character = character;
            this->frequency = frequency;
            left = right = nullptr;
        }

        /// @brief Descturctor, to delete the tree
        ~Node(){
            delete left;
            delete right;
        }
    };

    struct compare{
        /// @brief Overloaded operator() function to compare two Node pointers based on their frequency counts.
        /// @param l First Node pointer.
        /// @param r Ssecond Node pointer.
        /// @return True if the frequency of the first Node is > than the frequency of the second Node, False otherwise.
        bool operator()(Node* l, Node* r) {
            return l->frequency > r->frequency;
        }
    };

    /// @brief Print the Huffman code for each character in the tree
    /// @param root Root node of the tree
    /// @param s Current huffman code string
    void printCodes(Node* root, string s);

    /// @brief Build the Huffman Tree
    /// @param char_frequency Frequency of chars
    /// @return The root of the tree
    Node* buildHuffmanTree(vector<int> &char_frequency);
}

#endif