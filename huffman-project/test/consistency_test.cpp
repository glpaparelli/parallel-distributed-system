#include <iostream>
#include <vector>
#include <cassert>

#include "../headers/steps/io_handling.hpp"
#include "../headers/steps/frequency_counters.hpp"
#include "../headers/steps/huffman_tree.hpp"
#include "../headers/steps/huffman_map.hpp"
#include "../headers/steps/huffman_encodings.hpp"
#include "../headers/steps/ascii_encodings.hpp"

// Test if the different impplementations (Sequential, Multithread, FastFlow) are consistent
int main() {
    const int num_thread = 16;

    // read the file
    string input_file_path = "./data/input/1MB.txt";
    string content = io_handling::read(input_file_path);
   

    // TEST: char frequency consistency
    vector<int> sequential_char_frequency = frequency_counters::sequential_counter(
        content, 
        0, 
        content.size()
    );
    vector<int> multithread_char_frequency = frequency_counters::multithread_counter(
        content, 
        num_thread
    );
    vector<int> fastflow_char_frequency = frequency_counters::fastflow_counter(content, num_thread);
    assert(sequential_char_frequency == multithread_char_frequency);
    assert(sequential_char_frequency == fastflow_char_frequency);


    // build the tree and fromm it the mamp
    huffman_tree::Node* root = huffman_tree::build_huffman_tree(sequential_char_frequency);
    vector<string> huffman_map = huffman_map::build_huffman_map(root);

    // TEST: string encoding consistency
    string sequential_content_encoded = huffman_encodings::sequential_string_to_binary(
        content, 
        0, 
        content.length(),
        huffman_map
    );

    string multithread_content_encoded = huffman_encodings::multithread_string_to_binary(
        content, 
        num_thread, 
        huffman_map
    );
    string fastflow_content_encoded = huffman_encodings::fastflow_string_to_binary(
        content, 
        num_thread, 
        huffman_map
    );
    assert(sequential_content_encoded == multithread_content_encoded);
    assert(sequential_content_encoded == fastflow_content_encoded);
    
    // clarity sugar
    string content_encoded = sequential_content_encoded;
    // add padding to the encoded strings
    huffman_encodings::add_padding(content_encoded);

    // TEST: encoded string in ASCII consistency
    string sequential_content_compressed = ascii_encodings::sequential_binary_to_ASCII(
        content_encoded, 
        0, 
        content_encoded.length()
    );
    string multithread_content_compressed = ascii_encodings::multithread_binary_to_ASCII(
        content_encoded, 
        num_thread
    );
    string fastflow_content_compressed = ascii_encodings::fastflow_binary_to_ASCII(
        content_encoded, 
        num_thread
    );
    assert(sequential_content_compressed == multithread_content_compressed);
    assert(sequential_content_compressed == fastflow_content_compressed);
}