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
    cout << "STEP 1" << endl;
    string input_file_path = "./data/input/ascii_at_random.txt";
    string file_content = io_handling::read(input_file_path);
    cout << "File file_content: " << file_content << endl;
    cout << "---------------------------------------------------------\n" << endl;

    const int num_thread = 4;
    const int chunk_size = file_content.size() / num_thread;

    // STEP 2: build the frequency
    cout << "STEP 2" << endl;
    vector<int> char_frequency = frequency_counters::multithread_counter(file_content, num_thread, chunk_size);
    print(char_frequency);
    cout << "---------------------------------------------------------\n" << endl;
    
    // STEP 3: build the Huffman Tree
    cout << "STEP 3" << endl;
    huffman_tree::Node* root = huffman_tree::build_huffman_tree(char_frequency);
    huffman_tree::print_codes(root, "");
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 4: build the Huffman Map
    cout << "STEP 4" << endl;
    vector<string> huffman_map = huffman_map::build_huffman_map(root);
    for(int i = 0; i < huffman_map.size(); i++){
        char ith = (char) i; 
        cout << "char: " << ith << "->   code:" << huffman_map[i] << endl;
    }
    cout << "---------------------------------------------------------\n" << endl;

    // STEP 5: huffman encode
    cout << "STEP 5" << endl;
    vector <string> huffman_encoded = huffman_encodings::multithread_string_to_binary(
        file_content, 
        num_thread, 
        chunk_size, 
        huffman_map
    );
    for(int i = 0; i < num_thread; i++)
        cout << huffman_encoded[i];


}