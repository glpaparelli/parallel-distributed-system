#include <string>

#include "../headers/ascii_encodings.hpp"

using namespace std; 

string ascii_encodings::seqBinaryToASCII(string &s, const int start, const int end){
    string s_ascii = "";
    int padding = 8 - (s.size() % 8);
    s += string(padding, '0');

    for(int i = 0; i < s.size(); i += 8){
        string byte = s.substr(i, 8);
        char c = static_cast<char>(stoi(byte, nullptr, 2));
        s_ascii += c; 
    }

    return s_ascii;
}