#include "algorithm_4_1.hpp"

int analyze(std::queue<std::string> symbleString, Gramma gramma, std::map<std::pair<std::string, std::string>, GeneratingFormula>analyzeTable) {
    std::stack<std::string> stack;
    stack.push(DOLLAR);
    stack.push(startSymble);
    symbleString.push("$");
    do {
        std::string stackTop = stack.top(), symbleFront = symbleString.front();
        if (gramma.isTerminator(stackTop) || (stackTop == "$")) {
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