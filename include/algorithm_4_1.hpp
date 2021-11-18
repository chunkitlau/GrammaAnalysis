#ifndef ALGORITHM_4_1_HPP
#define ALGORITHM_4_1_HPP

#include <string>
#include <stack>
#include <queue>
#include <map>

#define DOLLAR "DOLLAR"

class GeneratingFormula{
public:
    GeneratingFormula(std::string);
    void print();
    void push(std::stack<std::string> &stack);
private:
    std::string _left;
    std::vector<std::string> _right;
}

std::map<std::string, int> token2num;

std::string startSymble;

#endif