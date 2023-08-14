#include <iostream>
#include <queue>
#include <vector>

#include "../headers/huffman_tree.hpp"

using namespace std; 

huffman_tree::Node* huffman_tree::buildHuffmanTree(std::vector<int> &char_frequency) {
    std::priority_queue<huffman_tree::Node*, std::vector<Node*>, huffman_tree::compare> pq;

    for (int i = 0; i < char_frequency.size(); i++)
        if(char_frequency[i] != 0)
            pq.push(new Node(i, char_frequency[i]));
        
    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* top = new Node('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        pq.push(top);
    }

    Node* root = pq.top();
    pq.pop();
    return root;
}

void huffman_tree::printCodes(Node* root, std::string str) {
    if (!root) 
        return;
    
    if (root->character != '$') 
        std::cout << root->character << " : " << str << std::endl;
    
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}