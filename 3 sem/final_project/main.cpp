#include "utils.hpp"
#include "parser.hpp"

using namespace std;

int main() {
    string file_to_read = string("../xsamples/example.html");
    string file_to_write = string("my_data.txt");
    // cout << "Введите путь к файлу, который надо прочитать: \n" << endl;
    // cin >> file_to_read;
    // cout << "Введите путь до файла, в который будет записан результат: \n" << endl;
    // cin >> file_to_write;
    string htmlInput = open_file(file_to_read);
    parseHTML(htmlInput, file_to_write);
    return 0;
}


