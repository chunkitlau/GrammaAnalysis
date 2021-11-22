#include "generatingFormula.hpp"

GeneratingFormula::GeneratingFormula() {
    std::string left;
    std::vector<std::string> right;
    _left = left;
    _right = right;
}

GeneratingFormula::GeneratingFormula(std::string left, std::vector<std::string> right) {
    _left = left;
    _right = right;
}

std::string GeneratingFormula::getLeft() {
    return _left;
}

std::vector<std::string> GeneratingFormula::getRight() {
    return _right;
}

std::string GeneratingFormula::print() {
    std::string string = _left + " -> ";
    for (std::vector<std::string>::iterator iter = _right.begin();
        iter != _right.end(); ++iter) {
            string += *iter + " ";
        }
    return string;
}

void GeneratingFormula::push(std::stack<std::string> &stack) {
    for (std::vector<std::string>::reverse_iterator iter = _right.rbegin(); 
        iter != _right.rend(); ++iter ) {
            stack.push(*iter);
        }
}