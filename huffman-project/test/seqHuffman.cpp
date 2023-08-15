#include <iostream>
#include <vector>

#include "../headers/io_handling.hpp"
#include "../headers/frequency_counters.hpp"
#include "../headers/huffman_tree.hpp"
#include "../headers/huffman_map.hpp"
#include "../headers/huffman_encodings.hpp"
#include "../headers/ascii_encodings.hpp"

using namespace std;

void print(std::vector<int> const &input) {
    for (int i = 0; i < input.size(); i++) 
        std::cout << input[i] << ' ';
}

int main() {
    // STEP 1: read the characters
    string input_file_path = "./data/input/ascii_at_random.txt";
    string file_content = io_handling::read(input_file_path);
    cout << "File file_content: " << file_content << endl;
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 2: build the frequency
    vector<int> char_frequency = frequency_counters::seqCounter(file_content, 0, file_content.size());
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
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 5: huffman encode a string
    string file_content_encoded = huffman_encodings::seqStringToBinary(file_content, 0, file_content.size(), huffmanMap);
    cout << "encoded: " << file_content_encoded << endl;
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 6: convert the encoded binary string to ASCII
    string file_content_compressed = ascii_encodings::seqBinaryToASCII(file_content_encoded, 0, file_content_encoded.size());
    cout << "encoded to ASCII: " << file_content_compressed << endl;
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 7: write the ascii encoded string to an output file
    string output_file_path = "./data/output/huffman_output.txt";
    io_handling::write(output_file_path, file_content_compressed);

    return 1;
}
