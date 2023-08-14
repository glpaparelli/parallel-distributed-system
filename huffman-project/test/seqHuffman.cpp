#include <iostream>
#include <vector>

#include "../headers/io_handling.hpp"
#include "../headers/frequency_counters.hpp"
#include "../headers/huffman_tree.hpp"
#include "../headers/huffman_map.hpp"

using namespace std;

void print(std::vector<int> const &input) {
    for (int i = 0; i < input.size(); i++) 
        std::cout << input[i] << ' ';
}

int main() {
    // STEP 1: read the characters
    string path = "./data/input/ascii_at_random.txt";
    string contents = io_handling::read(path);
    cout << "File contents: " << contents << endl;
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 2: build the frequency
    vector<int> char_frequency = frequency_counters::seqCounter(contents, 0, contents.size());
    print(char_frequency);
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 3: build the Huffman Tree
    huffman_tree::Node* root = huffman_tree::buildHuffmanTree(char_frequency);
    huffman_tree::printCodes(root, "");
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 4: build the Huffman Map
    vector<string> huffmanMap = huffman_map::getHuffmanMap(root);
    for(int i = 0; i < huffmanMap.size(); i++){
        char ith = (char) i; 
        cout << "char: " << ith << "->   code:" << huffmanMap[i] << endl;
    }

    return 1;
}
