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
    // starting time
    auto start_to_finish = std::chrono::high_resolution_clock::now();

    // STEP 1: read the characters
    auto start = std::chrono::high_resolution_clock::now();
    string input_file_path = "./data/input/ascii_at_random.txt";
    string file_content = io_handling::read(input_file_path);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time needed for reading: " << elapsed.count() << " seconds" << std::endl;

    // STEP 2: build the frequency
    start = std::chrono::high_resolution_clock::now();
    vector<int> char_frequency = frequency_counters::sequential_counter(file_content, 0, file_content.size());
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time needed for frequency: " << elapsed.count() << " seconds" << std::endl;
    
    // STEP 3: build the Huffman Tree
    start = std::chrono::high_resolution_clock::now();
    huffman_tree::Node* root = huffman_tree::build_huffman_tree(char_frequency);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time needed for tree building: " << elapsed.count() << " seconds" << std::endl;
    
    // STEP 4: build the Huffman Map
    start = std::chrono::high_resolution_clock::now();
    vector<string> huffman_map = huffman_map::build_huffman_map(root);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time needed for map building: " << elapsed.count() << " seconds" << std::endl;

    // STEP 5: huffman encode a string
    start = std::chrono::high_resolution_clock::now();
    string file_content_encoded = huffman_encodings::sequential_string_to_binary(file_content, 0, file_content.size(), huffman_map);
    // ASCII characters are 8 bits, hence the length of 
    // the original input text is a multiple of 8. 
    // this is not true once we created the Huffman code, as 
    // characters have a shorter representation based on their
    // frequence in the text. 
    // hence we have to add a padding to the encoded text
    int padding = 8 - (file_content_encoded.size() % 8);
    file_content_encoded += string(padding, '0');
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time needed for string to binary: " << elapsed.count() << " seconds" << std::endl;

    // STEP 6: convert the encoded binary string to ASCII
    start = std::chrono::high_resolution_clock::now();
    string file_content_compressed = ascii_encodings::sequential_binary_to_ASCII(file_content_encoded, 0, file_content_encoded.size());
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time needed for binary to ascii: " << elapsed.count() << " seconds" << std::endl;

    // STEP 7: write the ascii encoded string to an output file
    start = std::chrono::high_resolution_clock::now();
    string output_file_path = "./data/output/sequential_output.txt";
    io_handling::write(output_file_path, file_content_compressed);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time needed for writing: " << elapsed.count() << " seconds" << std::endl;

    // end time
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start_to_finish;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;
}