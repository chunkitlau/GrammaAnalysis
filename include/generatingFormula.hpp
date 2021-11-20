#ifndef GENERATINGFORMULA_HPP
#define GENERATINGFORMULA_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stack>

class GeneratingFormula{
public:
    GeneratingFormula(std::string left, std::vector<std::string> right);
    std::string getLeft();
    std::vector<std::string> getRight();
    void print();
    void push(std::stack<std::string> &stack);
private:
    std::string _left;
    std::vector<std::string> _right;
};

#endif