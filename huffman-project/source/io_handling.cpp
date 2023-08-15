#include <fstream>
#include <sstream>
#include <iostream>

#include "../headers/io_handling.hpp"

using namespace std;

string io_handling::read(const string &path){
    std::ifstream file(path);

    if(!file.is_open()){
        std::cerr << "Could not open the file - '" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::stringstream buffer; 
    buffer << file.rdbuf();
    file.close();
    
    return buffer.str();
}

void io_handling::write(const string &path, const string &s){
    ofstream file(path);
    
    if(!file.is_open()){
        std::cerr << "Could not open the file - '" << std::endl;
        exit(EXIT_FAILURE);
    }

    file << s;
    file.close();
}