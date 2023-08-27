#include <fstream>
#include <sstream>
#include <iostream>

#include "../headers/steps/io_handling.hpp"

using namespace std;

string io_handling::read(const string &path) { 
    ifstream file(path);
    if(!file.is_open()){
        cerr << "Could not open the file at: " + path << endl;
        exit(EXIT_FAILURE);
    }

    stringstream buffer; 
    buffer << file.rdbuf();
    file.close();
    
    return buffer.str();
}

void io_handling::write(const string &path, const string &s) {
    ofstream file(path);
    
    if(!file.is_open()){
        cerr << "Could not open the file - '" << endl;
        exit(EXIT_FAILURE);
    }

    file << s;
    file.close();
}