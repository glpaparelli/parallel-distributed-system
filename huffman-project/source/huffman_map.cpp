#include <string>
#include <vector>

#include "../headers/huffman_map.hpp"
#include "../headers/huffman_tree.hpp"

using namespace std;

void traverse_tree(
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
    traverse_tree(node->left, code + "0", huffmanMap);

    // traverse right and append '1' to the code.
    traverse_tree(node->right, code + "1", huffmanMap);
}

vector<string> huffman_map::build_huffman_map(huffman_tree::Node* root){
    vector<string> huffmanMap = vector<string>(256);
    string code;

    traverse_tree(root, code, huffmanMap);

    // huffmanMap here is a vector[char] -> huffman code of that char
    return huffmanMap;
}
