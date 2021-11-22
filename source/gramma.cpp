#include "gramma.hpp"

#include <unistd.h>

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
            q = line.find("|", p + 1);
            std::vector<std::string> right = 
                string2token(line.substr(p + 2, ((q != std::string::npos) ? q : line.length() + 1) - p - 3));
            _generatingFormula.push_back(GeneratingFormula(left, right));
            p = q;
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
    _noneTerminator = leftSet;
    _token = rightSet;

    // get follow set
    int lastSize = 0, nowSize = 0;
    do {
        _followSet[_generatingFormula.front().getLeft()].insert(ENDSYMBOL); 
        for (std::vector<GeneratingFormula>::iterator iter = _generatingFormula.begin();
            iter != _generatingFormula.end(); ++iter) {
                std::vector<std::string> right = iter->getRight();
                for (std::vector<std::string>::iterator tokenIter = right.begin();
                    tokenIter != right.end(); ++tokenIter) {
                        if (!isTerminator(*tokenIter)) {
                            if (tokenIter + 1 != right.end()) {
                                std::vector<std::string> tokens(tokenIter + 1, right.end());
                                std::set<std::string> firstSet = getFirstSet(tokens);
                                if (firstSet.find(EPSILON) != firstSet.end()) {
                                    firstSet.erase(EPSILON);
                                    std::set<std::string> followB = _followSet[iter->getLeft()];
                                    _followSet[*tokenIter].insert(followB.begin(), followB.end());
                                }
                                _followSet[*tokenIter].insert(firstSet.begin(), firstSet.end());
                            }
                            else {
                                std::set<std::string> followB = _followSet[iter->getLeft()];
                                _followSet[*tokenIter].insert(followB.begin(), followB.end());
                            }
                        }
                    }
            }
        lastSize = nowSize;
        nowSize = 0;
        for (std::map<std::string, std::set<std::string> >::iterator iter = _followSet.begin();
            iter != _followSet.end(); ++iter) {
                nowSize += iter->second.size();
            }
    } while (lastSize != nowSize);
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
    return _followSet[token];
}

std::set<std::string> Gramma::getNoneTerminator() {
    return _noneTerminator;
}

std::set<std::string> Gramma::getToken() {
    return _token;
}