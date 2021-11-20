#include "gramma.hpp"

std::vector<std::string> string2token(std::string string) {
    std::istringstream istrStream(string);
    std::string token;
    std::vector<std::string> tokens;
    while (!istrStream.eof()) {
        istrStream >> token;
        tokens.push_back(token);
    }
    return tokens;
}

/****************************************************************
 * GeneratingFormula example: E -> E + T | E – T | T 
 */
Gramma::Gramma(std::string filename) {
    // load generating formula
    std::ifstream infile(filename.c_str()); 
    std::string line;
    while(getline(infile, line)) {
        int p = line.find("->"), q;
        std::string left = line.substr(0, p++ - 1);
        do {
            q = line.find("|", p);
            std::vector<std::string> right = 
                string2token(line.substr(p + 2, ((q != std::string::npos) ? q : line.length() + 1) - p - 3));
            _generatingFormula.push_back(GeneratingFormula(left, right));
        } while (q != std::string::npos);
    }

    // get terminator set
    std::set<std::string> leftSet, rightSet;
    for (std::vector<GeneratingFormula>::iterator iter = _generatingFormula.begin();
        iter != _generatingFormula.end(); ++iter) {
            leftSet.insert(iter->getLeft());
            std::vector<std::string> right = iter->getRight();
            for (std::vector<std::string>::iterator tokenIter = right.begin();
                tokenIter != right.end(); ++tokenIter) {
                    rightSet.insert(*tokenIter);
                }
        }
    std::set_difference(std::begin(rightSet), std::end(rightSet), std::begin(leftSet), std::end(leftSet), std::inserter(_terminator, std::begin(_terminator)));

    // get first set

    // get follow set
}

std::vector<GeneratingFormula> Gramma::getGeneratingFormula() {
    return _generatingFormula;
}

bool Gramma::isTerminator(std::string token) {
    return _terminator.find(token) != _terminator.end();
}

bool Gramma::isEpsilon(std::string token) {
    return token == EPSILON;
}

std::set<std::string> Gramma::getFirstSet(std::vector<std::string> token) {
    std::set<std::string> firstSet;
    if (isTerminator(token.front())) {
        firstSet.insert(token.front());
        return firstSet;
    }
    for (std::vector<GeneratingFormula>::iterator iter = _generatingFormula.begin();
        iter != _generatingFormula.end(); ++iter) {
            if (iter->getLeft() == token.front()) {
                std::vector<std::string> right = iter->getRight();
                if (isTerminator(right.front())) {
                    firstSet.insert(right.front());
                }
                else if (isEpsilon(right.front()) && (right.size() == 1)) {
                    // WARNING: Empty production is not eliminated
                    firstSet.insert(EPSILON);
                }
                else if (right.front() != token.front()){
                    // WARNING: Left regression is not eliminated
                    std::set<std::string> appending = getFirstSet(right);
                    firstSet.insert(appending.begin(), appending.end());
                }
            }
        }
    return firstSet;
}

std::set<std::string> Gramma::getFollowSet(std::string token) {

}