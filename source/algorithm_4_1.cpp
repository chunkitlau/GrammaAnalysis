#include "algorithm_4_1.hpp"

GeneratingFormula::GeneratingFormula(std::string) {
    
}

void GeneratingFormula::print() {
    std::cout << _left << "->";
    for (std::vector<std::string>::iterator iter = _right.begin();
        iter != _right.end(); ++iter) {
            std::cout << *iter;
        }
    std::cout <<std::endl;
}

void GeneratingFormula::push(std::stack<std::string> &stack) {
    for (std::vector<std::string>::reverse_iterator iter = _right.rbegin(); 
        iter != _right.rend(); ++iter ) {
            stack.push(*iter);
        }
}

int analyze(std::queue<std::string> symbleString, std::map<std::pair<std::string, std::string>, GeneratingFormula>analyzeTable) {
    std::stack<std::string> stack;
    stack.push(DOLLAR);
    stack.push(startSymble);
    symbleString.push("$");
    do {
        std::string stackTop = stack.top(), symbleFront = symbleString.front();
        if (isTerminator(stackTop) || (stackTop == "$")) {
            if (stackTop == symbleFront) {
                stack.pop();
                symbleString.pop();
            }
            else error();
        }
        else {
            std::map<std::pair<std::string, std::string>, GeneratingFormula>::iterator 
                iter = analyzeTable.find({stackTop, symbleFront});
            if (iter != analyzeTable.end()) {
                stack.pop();
                iter->second.push(&stack);
                iter->second.print();
            }
            else error();
        }
    } while (stack.top() != "$");
}

void error() {
    std::cout << "ERROR" << std::endl;
}