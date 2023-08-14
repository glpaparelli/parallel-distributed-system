#include <iostream>
#include "headers/io_handling.hpp"

using namespace std;

int main() {
    std::string path = "./test/input/ascii_at_random.txt";
    std::string contents = io_handling::read(path);
    std::cout << "File contents: " << contents << std::endl;
    return 0;
}