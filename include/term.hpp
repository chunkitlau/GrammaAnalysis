#ifndef TERM_HPP
#define TERM_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stack>

class Term{
public:
    Term();
    Term(std::string left, std::vector<std::string> rightLeft, std::vector<std::string> rightRight);
    std::string getLeft() const;
    std::vector<std::string> getRightLeft() const;
    std::vector<std::string> getRightRight() const;
    //std::string print();
    //void push(std::stack<std::string> &stack);
private:
    std::string _left;
    std::vector<std::string> _rightLeft;
    std::vector<std::string> _rightRight;
};

#endif