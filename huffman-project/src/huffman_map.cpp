#include "headers/huffman_map.hpp"
#include "headers/huffman_tree.hpp"

using namespace std;

void traverseTree(
    huffman_tree::Node* node, 
    string code, 
    vector<string> &huffmanMap)
{
    if (node == nullptr) 
        return;

    // the node is a leaf, store its character and code in the map.
    if (node->left == nullptr && node->right == nullptr) 
        huffmanMap[static_cast<unsigned char>(node->character)] = code;

    // traverse left and append '0' to the code.
    traverseTree(node->left, code + "0", huffmanMap);

    // traverse right and append '1' to the code.
    traverseTree(node->right, code + "1", huffmanMap);
}

/**
 * @brief Function that builds the Huffman map using a Huffman tree.
 * @param root The root node of the Huffman tree.
 * @return The map of characters to Huffman codes.
 */
vector<string> getHuffmanMap(huffman_tree::Node* root) {
    vector<string> huffmanMap;
    string code;

    traverseTree(root, code, huffmanMap);

    return huffmanMap;
}
