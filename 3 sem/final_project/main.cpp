#include "utils.hpp"
#include "parser.hpp"

using namespace std;

int main() {
    string htmlInput = open_html("../xsamples/example2.html");
    parseHTML(htmlInput);
    return 0;
}