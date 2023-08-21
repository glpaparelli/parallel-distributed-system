#include <iostream>
#include <vector>
#include <chrono>

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

    auto start = std::chrono::high_resolution_clock::now();


    // STEP 1: read the characters
    // cout << "STEP 1" << endl;
    string input_file_path = "./data/input/ascii_at_random.txt";
    string file_content = io_handling::read(input_file_path);
    // cout << "File file_content: " << file_content << endl;
    // cout << "---------------------------------------------------------\n" << endl;

    const int num_thread = 16;
    const int chunk_size = file_content.size() / num_thread;

    // STEP 2: build the frequency
    // cout << "STEP 2" << endl;
    vector<int> char_frequency = frequency_counters::multithread_counter(file_content, num_thread, chunk_size);
    // print(char_frequency);
    // cout << "---------------------------------------------------------\n" << endl;
    
    // STEP 3: build the Huffman Tree
    // cout << "STEP 3" << endl;
    huffman_tree::Node* root = huffman_tree::build_huffman_tree(char_frequency);
    // huffman_tree::print_codes(root, "");
    // cout << "---------------------------------------------------------\n" << endl;

    // STEP 4: build the Huffman Map
    // cout << "STEP 4" << endl;
    vector<string> huffman_map = huffman_map::build_huffman_map(root);
    // for(int i = 0; i < huffman_map.size(); i++){
    //     char ith = (char) i; 
    //     cout << "char: " << ith << "->   code:" << huffman_map[i] << endl;
    // }
    // cout << "---------------------------------------------------------\n" << endl;

    // STEP 5: huffman encode a string
    // cout << "STEP 5" << endl;
    string file_content_encoded = huffman_encodings::multithread_string_to_binary(
        file_content, 
        num_thread, 
        chunk_size, 
        huffman_map
    );

    // ASCII characters are 8 bits, hence the length of 
    // the original input text is a multiple of 8. 
    // this is not true once we created the Huffman code, as 
    // characters have a shorter representation based on their
    // frequence in the text. 
    // hence we have to add a padding to the encoded text
    int padding = 8 - (file_content_encoded.size() % 8);
    file_content_encoded += string(padding, '0');

    // cout << file_content_encoded << endl;
    // cout << "---------------------------------------------------------\n" << endl;


    // STEP 6: convert the encoded binary string to ASCII
    // cout << "STEP 6" << endl;
    string file_content_compressed = ascii_encodings::multithread_binary_to_ASCII(file_content_encoded, num_thread, chunk_size);
    // cout << "encoded to ASCII: " << file_content_compressed << endl;
    // cout << "---------------------------------------------------------\n" << endl;

    // STEP 7: write the ascii encoded string to an output file
    // cout << "STEP 7" << endl;
    string output_file_path = "./data/output/multithread_output.txt";
    io_handling::write(output_file_path, file_content_compressed);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;
}