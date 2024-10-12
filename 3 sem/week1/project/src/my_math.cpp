#include <cmath>
#include "ans_handler.hpp"

AnswerHandler my_sin(double x) {
    return AnswerHandler(x, x - pow(x, 3)/6 + pow(x, 5)/120);
}

AnswerHandler my_cos(double x) {
    return AnswerHandler(x, 1 - pow(x, 2)/4 + pow(x, 4)/24);
}

AnswerHandler my_tan(double x) {
    return AnswerHandler(x, x + pow(x, 3)/6 + 2*pow(x, 5)/15);
}

AnswerHandler my_ctan(double x) {
    return AnswerHandler(x, 1/tan(x));
}