#include <iostream>
#include "string"
#include "vector"
#include "unordered_map"
#include "bitset"
#include <chrono>

using namespace std;

string file_content = "AAJKSJ";

struct HuffCode {
    unsigned char code;
    unsigned int size;

    HuffCode(unsigned char f_code, unsigned int f_size) : code(f_code), size(f_size) {}
};

unordered_map<char, HuffCode> huff_map;

string print_char_binary(unsigned char b) {
    bitset<8> c(b);
    return c.to_string();
}

void encode_ascii_write() {
    huff_map.insert({'A', HuffCode(0b11000000, 2)});
    huff_map.insert({'K', HuffCode(0b10000000, 3)});
    huff_map.insert({'J', HuffCode(0b00000000, 1)});
    huff_map.insert({'S', HuffCode(0b10000000, 3)});

    // chars ready to be written in the output file
    vector<unsigned char> encoded;
    // current buffer, the "window"
    unsigned char buff = 0;
    // buffer size
    unsigned int b_size = 0;

    // bits that can't be inserted in the current buffer, we will insert them in the next one
    unsigned int bits_leftovers = 0;
    // bits that can be written inside the buffer
    unsigned int buffer_free;
    // if there are leftovers this is true
    bool pending_bits = false;

    for (auto i = 0; i < file_content.size(); i++) {
        //cout << "index:" << endl;

        unsigned char current_char = file_content[i];
        // huffman code: unsigned char (8 bits), #significant bits
        HuffCode hc = huff_map.at(current_char);

        // easy case: we can fit the current char (encoded in huffman) inside the current buffer
        if(b_size + hc.size <= 8) {
            // shift the buffer and insert the code
            buff |= (hc.code >> b_size);
            // increase the buffer size with the #inserted bits
            b_size += hc.size;
        
        // the current buffer + the current huffman code are more than 8 bits
        } else if(b_size + hc.size > 8) {
            // how many bits there are available in the buffer
            buffer_free = 8 - b_size;
            // number of bits that will not be written in the buffer
            bits_leftovers = hc.size - buffer_free;
            // insert the available bits in the buffer
            buff |= (hc.code >> b_size);
            // the buffer is now full
            b_size = 8;
        }

        // otherwise, if the buffer is full we push it as this can be encoded as an ascii
        if(b_size == 8) {
            encoded.push_back(buff);
            buff = 0;
            b_size = 0;

            // if there are also leftovers from the current char we 
            // insert them in the new buffer
            if(bits_leftovers) {
                buff |= (hc.code << buffer_free);
                b_size += bits_leftovers;
                bits_leftovers = 0;
            }
        }
        // if this char is the last one we insert the buffer even if it is not a full buffer
        else if(i == (file_content.size() - 1)) 
            encoded.push_back(buff);
    }

    for (char c: file_content) {
        auto huff = huff_map.at(c);
        bitset<8> rr(huff.code);
        cout << "COD di " << c << " =" << rr.to_string() << " LSB=" << huff.size << endl;
    }

    string final;
    for (char c: encoded) {
        bitset<8> rr(c);
        final += rr.to_string() + " ";
    }

    cout << final << endl;

    // ofstream file(filename, std::ios::binary);
    // for(char c: encoded) 
    //     ofstream file(filename, std::ios::binary);
    // file.close();
}

int main() {
    auto start = std::chrono::high_resolution_clock::now(); // get start time
    encode_ascii_write();
    auto end = std::chrono::high_resolution_clock::now(); // get end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // calculate duration in milliseconds
    std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl; // print duration
    return 0;
}
