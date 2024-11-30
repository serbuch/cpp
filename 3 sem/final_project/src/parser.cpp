#include <regex>

#include "HTMLel.hpp"
#include "utils.hpp"
#include "parser.hpp"

using namespace std;

void parseHTML(const string& input) {
    
    vector<HTMLElement> elements;
    size_t pos = 0;

    while (pos < input.length()) {
        // Find the start of a tag
        size_t startTag = input.find('<', pos);
        if (startTag == string::npos) break;

        // Find the end of the tag
        size_t endTag = input.find('>', startTag);
        if (endTag == string::npos) break;

        // Extract tag name
        string tag = input.substr(startTag + 1, endTag - startTag - 1);
        size_t spacePos = tag.find(' ');
        if (spacePos != string::npos) {
            tag = regex_replace(tag.substr(0, spacePos), regex("\n"), string("")); // Get only the tag name
        }

        // Check for closing tags
        if (tag[0] == '/') {
            pos = endTag + 1;
            continue; // Skip closing tags
        }

        // Extract text content before the next opening tag
        size_t textStart = endTag + 1;
        size_t nextTag = input.find('<', textStart);
        string textContent = input.substr(textStart, nextTag - textStart);

        // Create HTMLElement and add to vector
        if (not(regex_match(textContent, regex("^ *")) or regex_match(textContent, regex(R"(^\n *)")) or textContent == string("")))
            elements.push_back({tag, regex_replace(textContent, regex("&nbsp;"), string(" "))});
        
        pos = nextTag; // Move position to next iteration
    }

    // Output parsed elements
    write_data(elements);
}