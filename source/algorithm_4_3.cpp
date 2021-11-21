#include "algorithm_4_3.hpp"

int analyze(std::queue<std::string> symbolString, std::map<std::pair<std::string, std::string>, std::pair<std::string, GeneratingFormula> > actionTable, std::map<std::pair<std::string, std::string>, std::string> gotoTable) {
    std::stack<std::string> stateStack, symbolStack;
    stateStack.push(STARTSTATE);
    symbolString.push(ENDSYMBOL);
    do {
        std::string stackTop = stateStack.top(), symbolFront = symbolString.front();
        std::map<std::pair<std::string, std::string>, std::pair<std::string, GeneratingFormula> >::iterator
            iter = actionTable.find({stackTop, symbolFront});
        if (iter != actionTable.end()) {
            if ((iter->second.first) == SHIFT) {
                symbolStack.push(symbolFront);
                stateStack.push(iter->second.second.getLeft());
                symbolString.pop();
            }
            else if (iter->second.first == REDUCE) {
                for (int k = iter->second.second.getRight().size(); k; --k) {
                    symbolStack.pop();
                }
                symbolStack.push(iter->second.second.getLeft());
                stateStack.push(gotoTable[{stateStack.top(), iter->second.second.getLeft()}]);
                iter->second.second.print();
            }
            else error();
        }
        else error();
    } while (1);
}

void error() {
    std::cout << "ERROR" << std::endl;
}