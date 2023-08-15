#include <iostream>
#include <queue>
#include <vector>

#include "../headers/huffman_tree.hpp"

using namespace std; 

huffman_tree::Node* huffman_tree::buildHuffmanTree(vector<int> &char_frequency){
    /**
     * step-by-step Huffman Tree building process
     * 1) Create a priority queue "pq" that stores Node pointers. 
     *    The queue is defined with a custom compare operator, 
     *    nodes with lower frequencies will have higher priority
     * 2) Iterate over "char_frequency" to create Node "objects" for 
     *    chars with != 0 frequency and push them in the pq. 
     *    Each Node object is a leaf node of the tree and contains
     *    the character and its frequency
     * 3) While the size of pq is != 1 perform the following step
     *      a) Pop the two top nodes, aka the two nodes with heighest
     *         priority. 
     *         This nodes represent the nodes with the lowest frequencies in
     *         the Huffman Tree
     *      b) Create a new Node object "top" with the char "$" and a frequency 
     *         equal to the sum of the frequency of the two popped nodes. 
     *         This new node will become the parent node of the two popped nodes.
     *      c) Set the "left" and "right" pointers of the node "top" to the two
     *         popped nodes
     *      d) push the node "top" in the priority queue 
     * 4) After the while loop pq will contain only one node, which is the root 
     *    of the Huffman Tree. Pop this node and assign it to the root variable. 
     * 5) Return root. 
    */
    priority_queue<Node*, vector<Node*>, compare> pq;

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

void huffman_tree::printCodes(Node* root, string str){
    if (!root) 
        return;
    
    if (root->character != '$') 
        cout << root->character << " : " << str << endl;
    
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}