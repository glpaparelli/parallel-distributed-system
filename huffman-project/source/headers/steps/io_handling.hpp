#ifndef IO_HANDLING_HPP
#define IO_HANDLING_HPP

#include <string>

using namespace std; 

namespace io_handling{    
    /// @brief Read from a file
    /// @param path The path of the file to read
    /// @return The content of the file as a string
    string read(const string &path);
    
    /// @brief Write a string into a file
    /// @param path The path of the file to write
    void write(const string &path, const string &s);
}

#endif