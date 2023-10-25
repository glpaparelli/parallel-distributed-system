#include <iostream>
#include <vector>
#include <chrono>
#include <map>

#include "../headers/huffman.hpp"
#include "../headers/steps/io_handling.hpp"
#include "../headers/steps/frequency_counters.hpp"
#include "../headers/steps/huffman_tree.hpp"
#include "../headers/steps/huffman_map.hpp"
#include "../headers/steps/huffman_encodings.hpp"
#include "../headers/steps/ascii_encodings.hpp"

using namespace std;
using namespace chrono;

// compute huffman sequentially and returns the timings
vector<duration<double>> huffman::sequential_huffman(const string file_name){
    vector<duration<double>> durations; 
    string input_file  = "./data/input/" + file_name;
    string output_file = "./data/output/seq_" + file_name;

    auto start = high_resolution_clock::now();

    // STEP 1: read the characters
    auto step_start = high_resolution_clock::now();
    string file_content = io_handling::read(input_file);
    auto step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);
    
    // STEP 2: build the frequency
    step_start = high_resolution_clock::now();
    vector<int> char_frequency = frequency_counters::sequential_counter(
        file_content, 
        0, 
        file_content.length()
    );
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);
    
    // STEP 3: build the Huffman Tree
    step_start = high_resolution_clock::now();
    huffman_tree::Node* root = huffman_tree::build_huffman_tree(char_frequency);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 4: build the Huffman Map
    step_start = high_resolution_clock::now();
    vector<string> huffman_map = huffman_map::build_huffman_map(root);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 5: huffman encode a string
    step_start = high_resolution_clock::now();
    string file_content_encoded = huffman_encodings::sequential_string_to_binary(
        file_content, 
        0, 
        file_content.length(),
        huffman_map
    );
    huffman_encodings::add_padding(file_content_encoded);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 6: convert the encoded binary string to ASCII
    step_start = high_resolution_clock::now();
    string file_content_compressed = ascii_encodings::sequential_binary_to_ASCII(
        file_content_encoded, 
        0, 
        file_content_encoded.length()
    );
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 7: write the ascii encoded string to an output file
    step_start = high_resolution_clock::now();
    io_handling::write(output_file, file_content_compressed);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    auto end = high_resolution_clock::now();
    durations.push_back(end - start);

    return durations;
}

// compute huffman using multithreading and returns the timings
vector<duration<double>> huffman::multithread_huffman(
    const string file_name, 
    const int num_threads
){
    vector<duration<double>> durations; 
    string input_file  = "./data/input/" + file_name;
    string output_file = "./data/output/mt_" + to_string(num_threads) + "t_" + file_name;

    auto start = high_resolution_clock::now();

    // STEP 1: read the characters
    auto step_start = high_resolution_clock::now();
    string file_content = io_handling::read(input_file);
    auto step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);
    
    // STEP 2: build the frequency
    step_start = high_resolution_clock::now();
    vector<int> char_frequency = frequency_counters::multithread_counter(file_content, num_threads);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);
    
    // STEP 3: build the Huffman Tree
    step_start = high_resolution_clock::now();
    huffman_tree::Node* root = huffman_tree::build_huffman_tree(char_frequency);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 4: build the Huffman Map
    step_start = high_resolution_clock::now();
    vector<string> huffman_map = huffman_map::build_huffman_map(root);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 5: huffman encode a string
    step_start = high_resolution_clock::now();
    string file_content_encoded = huffman_encodings::multithread_string_to_binary(
        file_content, 
        num_threads, 
        huffman_map
    );
    huffman_encodings::add_padding(file_content_encoded);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 6: convert the encoded binary string to ASCII
    step_start = high_resolution_clock::now();
    string file_content_compressed = ascii_encodings::multithread_binary_to_ASCII(file_content_encoded, num_threads);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 7: write the ascii encoded string to an output file
    step_start = high_resolution_clock::now();
    io_handling::write(output_file, file_content_compressed);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    auto end = high_resolution_clock::now();
    durations.push_back(end - start);

    return durations;
}

// compute huffman using fastflow and returns the timings
vector<duration<double>> huffman::fastflow_huffman(
    const string file_name, 
    const int num_threads
){
    vector<duration<double>> durations; 
    string input_file  = "./data/input/" + file_name;
    string output_file = "./data/output/ff_" + to_string(num_threads) + "t_" + file_name;

    auto start = high_resolution_clock::now();

    // STEP 1: read the characters
    auto step_start = high_resolution_clock::now();
    string file_content = io_handling::read(input_file);
    auto step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);
    
    // STEP 2: build the frequency
    step_start = high_resolution_clock::now();
    vector<int> char_frequency = frequency_counters::fastflow_counter(file_content, num_threads);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);
    
    // STEP 3: build the Huffman Tree
    step_start = high_resolution_clock::now();
    huffman_tree::Node* root = huffman_tree::build_huffman_tree(char_frequency);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 4: build the Huffman Map
    step_start = high_resolution_clock::now();
    vector<string> huffman_map = huffman_map::build_huffman_map(root);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 5: huffman encode a string
    step_start = high_resolution_clock::now();
    string file_content_encoded = huffman_encodings::fastflow_string_to_binary(
        file_content, 
        num_threads, 
        huffman_map
    );
    huffman_encodings::add_padding(file_content_encoded);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 6: convert the encoded binary string to ASCII
    step_start = high_resolution_clock::now();
    string file_content_compressed = ascii_encodings::fastflow_binary_to_ASCII(file_content_encoded, num_threads);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    // STEP 7: write the ascii encoded string to an output file
    step_start = high_resolution_clock::now();
    io_handling::write(output_file, file_content_compressed);
    step_end = high_resolution_clock::now();
    durations.push_back(step_end - step_start);

    auto end = high_resolution_clock::now();
    durations.push_back(end - start);

    return durations;
}