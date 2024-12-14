#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>


std::string open_file(const std::string& filepath);

template <typename T>
void write_data(const std::vector<T>& data, const std::string& path) {
    
    std::ofstream os(path);
    int cnt = 0;
    for (const auto& element : data)
    {   
        std::clog << "\rProgress: " << cnt*100/data.size() << "%" << ' ' 
        << std::string(round(cnt*100/data.size()), '#') + std::string(round(100-cnt*100/data.size()), '_')  << ' ' << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cnt++;
        os << "Tag: " << element.tagName << ", Content: " << element.textContent << '\n';
    }
    std::clog << "\rDone.                                                                                                             "
     << std::endl;
}

#endif