#include "algorithm_4_4.hpp"

std::set<Term> closure(Gramma gramma, std::set<Term> termSetI) {
    std::set<Term> termSetJ = termSetI, termSetJNew;
    std::vector<std::string> empty;
    std::vector<GeneratingFormula> generatingFormula = gramma.getGeneratingFormula();
    do {
        termSetJNew = termSetJ;
        for (std::set<Term>::iterator termIter = termSetJNew.begin();
            termIter != termSetJNew.end(); ++termIter) {
                std::vector<std::string> rightRight = (*termIter).getRightRight();
                if (!rightRight.empty() && !gramma.isTerminator(rightRight.front())) {
                    for (std::vector<GeneratingFormula>::iterator formulaIter = generatingFormula.begin();
                    formulaIter != generatingFormula.end(); ++formulaIter) {
                        if (formulaIter->getLeft() == rightRight.front()) {
                            Term newTerm(formulaIter->getLeft(), empty, formulaIter->getRight());
                            termSetJ.insert(newTerm);
                        }
                    }
                }
                
            }
    } while (termSetJNew.size() != termSetJ.size());
    return termSetJ;
}

void error() {
    std::cout << "ERROR" << std::endl;
}