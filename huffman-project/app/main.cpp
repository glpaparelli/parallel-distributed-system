#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <thread>

#include "../headers/huffman.hpp"
#include "../headers/steps/io_handling.hpp"
#include "../headers/steps/frequency_counters.hpp"
#include "../headers/steps/huffman_tree.hpp"
#include "../headers/steps/huffman_map.hpp"
#include "../headers/steps/huffman_encodings.hpp"
#include "../headers/steps/ascii_encodings.hpp"

using namespace std; 
using namespace chrono;

// ugly way to print timings
void print_timings(vector<duration<double>> results){
    cout << "Time for READ: " << results[0].count() << endl;
    cout << "Time for COUNT: " << results[1].count() << endl;
    cout << "Time for TREE: " << results[2].count() << endl;
    cout << "Time for MAP: " << results[3].count() << endl;
    cout << "Time for ENCODE: " << results[4].count() << endl;
    cout << "Time for ASCII: " << results[5].count() << endl;
    cout << "Time for READ: " << results[6].count() << endl;

    cout << endl; 
    cout << "Time needed for completion: " << results[7].count() << endl;
}

// for each implementation compute the average timings aand write them in a csv file
void automatic(){
    vector<string> file_names = {"1MB.txt", "5MB.txt", "10MB.txt", "50MB.txt", "100MB.txt"};

    // computing the timings for the sequential implementaton
    // for each file size we execute the algorithm 5 times and take the average
    vector<vector<duration<double>>> five_durations;
    vector<duration<double>> avg; 
    avg.assign(8, duration<double>::zero());
    
    ofstream file("./results/sequential.csv");
        file << "SIZE, READ, COUNT, TREE, MAP, ENCODE, ASCII, WRITE, COMPLETION" << endl;
    
    cout << "Start Measuring Sequential Implementation" << endl;
    for(string f : file_names){
        // compute the results five times
        for(int i = 0; i < 5; i++)
            five_durations.push_back(huffman::sequential_huffman(f));

        // sum the results of each step 
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 5; j++)
                avg.at(i) += five_durations.at(j).at(i);
        
        // take the average
        for(int i = 0; i < 8; i++)
            avg.at(i) = avg.at(i) / 5;
        
        // write the averge times into the csv file
        file << f.substr(0, f.length() - 4) + ", ";
        for(int i = 0; i < avg.size()-1; i++)
            file << avg.at(i).count() << ", ";
        file << avg.at(avg.size()-1).count() << endl;

        five_durations.clear();
        avg.assign(8, duration<double>::zero());

    }
    file.close();
    cout << "Completed Measuring Sequential Implementation" << endl;

    // same but for multithread implementation, using incrementally more threads
    five_durations.clear();
    avg.assign(8, duration<double>::zero());
    file.open("./results/multithreaded.csv");
    int num_threads = 1;
    int max_threads = thread::hardware_concurrency();
    cout << "Start Measuring Multithreaded Implementation" << endl;
    while (num_threads <= max_threads){
        file << "SIZE, #THREADS, READ, COUNT, TREE, MAP, ENCODE, ASCII, WRITE, COMPLETION" << endl;

        for(string f : file_names){
            // compute the results five times
            for(int i = 0; i < 5; i++)
                five_durations.push_back(huffman::multithread_huffman(f, num_threads));

            // sum the results of each step 
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 5; j++)
                    avg.at(i) += five_durations.at(j).at(i);
            
            // take the average
            for(int i = 0; i < 8; i++)
                avg.at(i) = avg.at(i) / 5;
            
            // write the averge times into the csv file
            file << f.substr(0, f.length() - 4) + ", ";
            file << to_string(num_threads) + ", ";
            for(int i = 0; i < avg.size()-1; i++)
                file << avg.at(i).count() << ", ";
            file << avg.at(avg.size()-1).count() << endl;

            five_durations.clear();
            avg.assign(8, duration<double>::zero());
        }

        num_threads *= 2; 
        file << endl;
    }
    file.close();
    cout << "Completed Measuring Multithreaded Implementation" << endl;

    // same but for fastflow implementation, using incrementally more threads
    five_durations.clear();
    avg.assign(8, duration<double>::zero());
    file.open("./results/fastflow.csv");
    num_threads = 1;
    cout << "Start Measuring Fastflow Implementation" << endl;
    while (num_threads <= max_threads){
        file << "SIZE, #THREADS, READ, COUNT, TREE, MAP, ENCODE, ASCII, WRITE, COMPLETION" << endl;

        for(string f : file_names){
            // compute the results five times
            for(int i = 0; i < 5; i++)
                five_durations.push_back(huffman::fastflow_huffman(f, num_threads));

            // sum the results of each step 
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 5; j++)
                    avg.at(i) += five_durations.at(j).at(i);
            
            // take the average
            for(int i = 0; i < 8; i++)
                avg.at(i) = avg.at(i) / 5;
            
            // write the averge times into the csv file
            file << f.substr(0, f.length() - 4) + ", ";
            file << to_string(num_threads) + ", ";
            for(int i = 0; i < avg.size()-1; i++)
                file << avg.at(i).count() << ", ";
            file << avg.at(avg.size()-1).count() << endl;

            five_durations.clear();
            avg.assign(8, duration<double>::zero());
        }

        num_threads *= 2; 
        file << endl;
    }
    file.close();
    cout << "Measuring Completed" << endl;
}

void interactive(){
    cout << "Choose the implementation to use:" << endl;
    cout << "1) Sequential" << endl;
    cout << "2) Multithread" << endl;
    cout << "3) Fastflow" << endl; 
    cout << endl;
    cout << "> ";
    string s_imp; 
    getline(cin, s_imp);
    int imp = stoi(s_imp); 

    cout << endl;
    cout << "Enter the size of the input file, e.g., 1MB\n" << endl;
    string file_name;
    cout << "> ";
    getline (cin, file_name);
    cout << endl;

    file_name += ".txt";
    int num_threads; 

    vector<duration<double>> results;

    switch(imp) {
        case 1: 
            results = huffman::sequential_huffman(file_name);
            break; 
        case 2: 
            cout << "Enter the number of threads to use\n" << endl;
            cout << "> ";   
            cin >> num_threads;
            cout << endl;

            results = huffman::multithread_huffman(file_name, num_threads);
            break;
        case 3: 
            cout << "Enter the number of threads to use\n" << endl;
            cout << "> ";
            cin >> num_threads;
            cout << endl;

            results = huffman::fastflow_huffman(file_name, num_threads);
            break;
        default: 
            cout << "Invalid input: Enter the number of the implementation to use" << endl;
    }

    print_timings(results);
}

void help(){
    cout << "Invalid Command." << endl;
    cout << "For the automatic generation of data type: ./main -a" << endl;
    cout << "For the interactive usage type: ./main -i" << endl;
}

// tested, code just in case
void consistency_test(string file_name, int num_thread){
    // read the file
    string input_file_path = "./data/input/" + file_name;
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

int main(int argc, char* argv[]){
    if(argc != 2){
       help();
       return 0;
    }

    string command = argv[1];
    if(command == "-a")
        // automatically compute the timings for each implementation
        automatic();
    else if(command == "-i")
        // command line interface to execute a specific implementation with specific parameters
        interactive();
    else
        help();
    
    return 0;
}