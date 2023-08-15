#include <string>

#include "../headers/ascii_encodings.hpp"

using namespace std; 

string ascii_encodings::seqBinaryToASCII(string &s, const int start, const int end){
    // ASCII characters are 8 bits, hence the length of 
    // the original input text is a multiple of 8. 
    // This is not true once we created the Huffman code, as 
    // characters have a shorter representation based on their
    // frequence in the text. 
    // Hence we have to add a padding to the encoded text
    string s_ascii = "";
    int padding = 8 - (s.size() % 8);
    s += string(padding, '0');

    for(int i = 0; i < s.size(); i += 8){
        string byte = s.substr(i, 8);
        // the stoi function takes three arguments: 
        // the string to convert
        // a pointer to an int to store the converted value
        // the base of the number system (in this case, 2 for binary).
        char c = static_cast<char>(stoi(byte, nullptr, 2));
        s_ascii += c; 
    }

    return s_ascii;
}