#include "algorithm_4_2.hpp"

std::map<std::pair<std::string, std::string>, GeneratingFormula> construct(Gramma gramma) {
    std::map<std::pair<std::string, std::string>, GeneratingFormula> analyzeTable;
    std::vector<GeneratingFormula> generatingFormula = gramma.getGeneratingFormula();
    for (std::vector<GeneratingFormula>::iterator iter = generatingFormula.begin();
        iter != generatingFormula.end(); ++iter) {
            std::set<std::string> firstSet = gramma.getFirstSet(iter->getRight());
            for (std::set<std::string>::iterator tokenIter = firstSet.begin();
                tokenIter != firstSet.end(); ++tokenIter) {
                    if (gramma.isTerminator(*tokenIter) && !gramma.isEpsilon(*tokenIter)) {
                        analyzeTable[{iter->getLeft(), *tokenIter}] = *iter;
                    }
                    if (gramma.isEpsilon(*tokenIter)){
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
/*
int main() {
    Gramma gramma("./demo/arithmeticExpressionGramma1.txt");
    std::map<std::pair<std::string, std::string>, GeneratingFormula> analyzeTable = construct(gramma);
    for (std::map<std::pair<std::string, std::string>, GeneratingFormula>::iterator iter = analyzeTable.begin();
        iter != analyzeTable.end(); ++iter) {
            std::cout << "M[" << iter->first.first << "," << iter->first.second << "]=" << iter->second.print() << std::endl;
        }
}
*/