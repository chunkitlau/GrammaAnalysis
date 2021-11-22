#include "algorithm_4_1.hpp"

#include <unistd.h>

int analyze(std::vector<std::string> symbleStringV, Gramma gramma, std::map<std::pair<std::string, std::string>, GeneratingFormula>analyzeTable) {
    std::stack<std::string> stack;
    stack.push(ENDSYMBOL);
    stack.push("E");
    std::queue<std::string, std::deque<std::string> > 
        symbleString(std::deque<std::string>(symbleStringV.begin(),symbleStringV.end()));
    symbleString.push(ENDSYMBOL);
    do {
        std::string stackTop = stack.top(), symbleFront = symbleString.front();
        if (gramma.isTerminator(stackTop) || (stackTop == ENDSYMBOL)) {
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
                iter->second.push(stack);
                if (stack.top() == EPSILON) {
                    stack.pop();
                }
                std::cout << iter->second.print() << std::endl;
            }
            else error();
        }
    } while (stack.top() != ENDSYMBOL);
    return 0;
}

void error() {
    std::cout << "ERROR" << std::endl;
}

int main() {
    Gramma gramma("./demo/arithmeticExpressionGramma1.txt");
    std::map<std::pair<std::string, std::string>, GeneratingFormula> analyzeTable = construct(gramma);
    std::ifstream expressionfile("./demo/arithmeticExpression1.txt"); 
    std::string symbleString;
    while(getline(expressionfile, symbleString)) {
        analyze(string2token(symbleString), gramma, analyzeTable);
    }
    return 0;
}