#include "term.hpp"

Term::Term() {
    std::string left;
    std::vector<std::string> rightLeft, rightRight;
    _left = left;
    _rightLeft = rightLeft;
    _rightRight = rightRight;
}

Term::Term(std::string left, std::vector<std::string> rightLeft, std::vector<std::string> rightRight) {
    _left = left;
    _rightLeft = rightLeft;
    _rightRight = rightRight;
}

std::string Term::getLeft() const {
    return _left;
}

std::vector<std::string> Term::getRightLeft() const {
    return _rightLeft;
}

std::vector<std::string> Term::getRightRight() const {
    return _rightRight;
}