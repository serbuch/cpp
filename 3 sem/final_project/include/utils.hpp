#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string open_html(const string& filepath);

template <typename T>
void write_data(vector<T> data) {
    
    string path("my_data.txt");
    ofstream os(path);
    int cnt = 0;
    for (const auto& element : data)
    {   
        clog << "\rScanlines remaining: " << ((data.size() - cnt)*100/data.size()) << '%' << ' ' << flush;
        this_thread::sleep_for(std::chrono::milliseconds(5));
        cnt++;
        os << "Tag: " << element.tagName << ", Content: " << element.textContent << '\n';
    }
    clog << "\rDone.                    \n";
}

#endif