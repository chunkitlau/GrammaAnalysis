#ifndef GRAMMA_HPP
#define GRAMMA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

#include "generatingFormula.hpp"

#define SHIFT "SHIFT"
#define REDUCE "REDUCE"
#define STARTSTATE "STARTSTATE"
#define ENDSYMBOL "ENDSYMBOL"
#define EPSILON "EPSILON"

class Gramma{
public:
    Gramma(std::string filename);
    std::vector<GeneratingFormula> getGeneratingFormula();
    bool isTerminator(std::string token);
    bool isEpsilon(std::string token);
    std::set<std::string> getFirstSet(std::vector<std::string> token);
    std::set<std::string> getFollowSet(std::string token);
    std::set<std::string> getNoneTerminator();
    std::set<std::string> getToken();
private:
    std::vector<GeneratingFormula> _generatingFormula;
    std::set<std::string> _terminator, _noneTerminator, _token;
    std::map<std::string, std::set<std::string> > _followSet;
};

std::vector<std::string> string2token(std::string string);

#endif