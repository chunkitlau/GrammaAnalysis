#include "algorithm_4_5.hpp"

std::set<Term> go(std::set<Term> I, std::string token) {
    std::set<Term> result;
    for (std::set<Term>::iterator termIter = I.begin();
        termIter != I.end(); ++termIter) {
            std::vector<std::string> rightRight = termIter->getRightRight();
            if (rightRight.front() == token) {
                std::vector<std::string> rightLeft = termIter->getRightLeft();
                rightLeft.push_back(rightRight.front());
                rightRight.erase(rightRight.begin());
                Term newTerm(termIter->getLeft(), rightLeft, rightRight);
                result.insert(newTerm);
            }
        }
    return result;
}

std::string print(std::set<Term> set) {
    std::string string;
    string = "{";
    for (std::set<Term>::iterator termIter = set.begin();
        termIter != set.end(); ++termIter) {
            string += termIter->getLeft() + " -> " + 
                termIter->getRightLeft().print() + " . " + 
                termIter->getRightRight().print() + " ";
        }
    string += "}";
    return string;
}

std::set<std::set<Term> > construct(Gramma gramma) {
    std::vector<std::string> empty, E(1);
    E[0] = "E";
    Term initTerm("E'", empty, E);
    std::set<std::set<Term> > C, newC;
    std::set<Term> init;
    init.insert(initTerm);
    C.insert(closure(gramma, init));
    std::set<std::string> token = gramma.getToken();
    do {
        newC = C;
        for (std::set<std::set<Term> >::iterator closureIter = newC.begin();
            closureIter != newC.end(); ++closureIter) {
                for (std::set<std::string>::iterator tokenIter = token.begin();
                    tokenIter != token.end(); ++tokenIter) {
                        std::set<Term> newSet = closure(gramma, go(*closureIter, *tokenIter));
                        std::cout << print(*closureIter) << " read " << *tokenIter << " goto " << print(newSet) << std::endl;
                        if (!newSet.empty()) {
                            C.insert(newSet);
                        }
                    }
                
            }
    } while (newC.size() != C.size());
    return C;
}

void error() {
    std::cout << "ERROR" << std::endl;
}