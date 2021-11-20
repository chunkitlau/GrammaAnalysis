#include "recursiveCallPredictiveAnalysis.hpp"

void procE(void) {
    procT();
    if (token == "+" || token == "-") {
        forward pointer;
        procE();
    }
}

void procT(void) {
    procF();
    if (token == "*" || token == "/") {
        forward pointer;
        procT();
    }
}

void procF(void) {
    if (token == "(") {
        forward pointer;
        procE();
        if (token == ")") {
            forward pointer;
        }
        else error();
    }
    else if (token == "num") {
        forward pointer;
    }
    else error();
}

int analyze() {
    
}

void error() {
    std::cout << "ERROR" << std::endl;
}