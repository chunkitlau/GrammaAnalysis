#include "algorithm_4_6.hpp"

std::pair<std::map<std::pair<std::string, std::string>, GeneratingFormula>, std::map<std::pair<std::string, std::string>, GeneratingFormula> > construct2(Gramma gramma) {
    std::set<std::set<Term> > closureTable = construct(gramma);
    std::map<std::pair<std::string, std::string>, GeneratingFormula> actionTable, gotoTable;
    std::vector<GeneratingFormula> generatingFormula = gramma.getGeneratingFormula();
    for (std::vector<GeneratingFormula>::iterator iter = generatingFormula.begin();
        iter != generatingFormula.end(); ++iter) {
            std::set<std::string> firstSet = gramma.getFirstSet(iter->getRight());
            for (std::set<std::string>::iterator tokenIter = firstSet.begin();
                tokenIter != firstSet.end(); ++tokenIter) {
                    if (gramma.isTerminator(*tokenIter) && !gramma.isEpsilon(*tokenIter)) {
                        actionTable[{iter->getLeft(), *tokenIter}] = *iter;
                    }
                    if (gramma.isEpsilon(*tokenIter)){
                        std::set<std::string> followSet = gramma.getFollowSet(iter->getLeft());
                        for (std::set<std::string>::iterator followTokenIter = followSet.begin();
                            followTokenIter != followSet.end(); ++followTokenIter) {
                                gotoTable[{iter->getLeft(), *followTokenIter}] = *iter;
                            }
                    }
                }
        }
    return {actionTable, gotoTable};
}