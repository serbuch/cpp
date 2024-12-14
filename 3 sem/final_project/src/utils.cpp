#include "utils.hpp"

using namespace std;

string open_file(const string& filepath) {
    ifstream file(filepath); 
    stringstream buffer;
    if (file.is_open()) {
        buffer << file.rdbuf(); // Read the entire file into the buffer
        file.close();
    } 
    else {
        std::cerr << "Unable to open file: " << filepath << std::endl;
    }

    return buffer.str(); // Return the content as a string
}


