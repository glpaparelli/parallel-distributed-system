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
    //this is ugly code for now

    // STEP 1: read the characters
    cout << "STEP 1" << endl;
    string input_file_path = "./data/input/ascii_at_random.txt";
    string file_content = io_handling::read(input_file_path);
    cout << "File file_content: " << file_content << endl;
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 2: build the frequency
    cout << "STEP 2" << endl;
    vector<int> char_frequency = frequency_counters::sequential_counter(file_content, 0, file_content.size());
    print(char_frequency);
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 3: build the Huffman Tree
    cout << "STEP 3" << endl;
    huffman_tree::Node* root = huffman_tree::build_huffman_tree(char_frequency);
    huffman_tree::print_codes(root, "");
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 4: build the Huffman Map
    cout << "STEP 4" << endl;
    vector<string> huffmanMap = huffman_map::build_huffman_map(root);
    for(int i = 0; i < huffmanMap.size(); i++){
        char ith = (char) i; 
        cout << "char: " << ith << "->   code:" << huffmanMap[i] << endl;
    }
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 5: huffman encode a string
    cout << "STEP 5" << endl;
    string file_content_encoded = huffman_encodings::sequential_string_to_binary(file_content, 0, file_content.size(), huffmanMap);
    cout << "encoded: " << file_content_encoded << endl;
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 6: convert the encoded binary string to ASCII
    cout << "STEP 6" << endl;
    string file_content_compressed = ascii_encodings::sequential_binary_to_ASCII(file_content_encoded, 0, file_content_encoded.size());
    cout << "encoded to ASCII: " << file_content_compressed << endl;
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 7: write the ascii encoded string to an output file
    cout << "STEP 7" << endl;
    string output_file_path = "./data/output/huffman_output.txt";
    io_handling::write(output_file_path, file_content_compressed);

    return 1;
}
