#include <iostream>
#include <fstream>
#include <vector>

#include "../headers/huffman.hpp"
#include "../headers/steps/io_handling.hpp"
#include "../headers/steps/frequency_counters.hpp"
#include "../headers/steps/huffman_tree.hpp"
#include "../headers/steps/huffman_map.hpp"
#include "../headers/steps/huffman_encodings.hpp"
#include "../headers/steps/ascii_encodings.hpp"

using namespace std; 
using namespace chrono;

void automatic(){
    vector<string> file_names = {"1MB.txt", "5MB.txt", "10MB.txt", "50MB.txt", "100MB.txt"};

    // computing the timings for the sequential implementaton
    // for each file size we execute the algorithm 5 times and take the average
    vector<vector<duration<double>>> five_durations;
    vector<duration<double>> avg; 
    avg.assign(8, duration<double>::zero());
    
    ofstream file("./results/sequential.csv");
    file << "file size, avg read time, avg count time, avg tree time, avg map time, avg encode time, avg ascii time, avg write time, avg start to finish time" << endl;
    
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

    // for multithread implementation
    five_durations.clear();
    avg.assign(8, duration<double>::zero());
    file.open("./results/multithreaded.csv");
    int num_threads = 2;
    cout << "Start Measuring Multithreaded Implementation" << endl;
    while (num_threads <= 32){
        file << "file size, #threads, avg read time, avg count time, avg tree time, avg map time, avg encode time, avg ascii time, avg write time, avg start to finish time" << endl;

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

    //for fastflow implementation
    five_durations.clear();
    avg.assign(8, duration<double>::zero());
    file.open("./results/fastflow.csv");
    num_threads = 2;
    cout << "Start Measuring Fastflow Implementation" << endl;
    while (num_threads <= 32){
        file << "file size, #threads, avg read time, avg count time, avg tree time, avg map time, avg encode time, avg ascii time, avg write time, avg start to finish time" << endl;

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

}

void help(){
    cout << "Invalid Command." << endl;
    cout << "For the automatic generation of data type: ./main -a" << endl;
    cout << "For the interactive usage type: ./main -i" << endl;
}


int main(int argc, char* argv[]){
    if(argc != 2){
       help();
       return 0;
    }

    string command = argv[1];
    if(command == "-a")
        automatic();
    else if(command == "-i")
        interactive();
    else
        help();
    
    return 0;
}