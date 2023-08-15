#include <vector>
#include <iostream>

#include "../headers/huffman_encodings.hpp"

using namespace std; 

string huffman_encodings::seqStringToBinary(
    const string &s, 
    const int start, 
    const int end, 
    const vector<string> &huffmanMap
){
    string sEncoded = "";
 
    for(int i = start; i < end; i++)
        sEncoded = sEncoded + huffmanMap[static_cast<unsigned char>(s[i])];
    
    return sEncoded;
}