#include "algorithm_4_2.hpp"

std::map<std::pair<std::string, std::string>, GeneratingFormula> construct(Gramma gramma) {
    std::map<std::pair<std::string, std::string>, GeneratingFormula> analyzeTable;
    std::vector<GeneratingFormula> generatingFormula = gramma.getGeneratingFormula();
    for (std::vector<GeneratingFormula>::iterator iter = generatingFormula.begin();
        iter != generatingFormula.end(); ++iter) {
            std::set<std::string> firstSet = gramma.getFirstSet(iter->getRight());
            for (std::set<std::string>::iterator tokenIter = firstSet.begin();
                tokenIter != firstSet.end(); ++tokenIter) {
                    if (gramma.isTerminator(*tokenIter)) {
                        analyzeTable[{iter->getLeft(), *tokenIter}] = *iter;
                    }
                    else if (gramma.isEpsilon(*tokenIter)){
                        std::set<std::string> followSet = gramma.getFollowSet(iter->getLeft());
                        for (std::set<std::string>::iterator followTokenIter = followSet.begin();
                            followTokenIter != followSet.end(); ++followTokenIter) {
                                analyzeTable[{iter->getLeft(), *followTokenIter}] = *iter;
                            }
                    }
                }
        }
    return analyzeTable;
}