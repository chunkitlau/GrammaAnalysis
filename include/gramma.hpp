#ifndef GRAMMA_HPP
#define GRAMMA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

#include "generatingFormula.hpp"

#define EPSILON "EPSILON"

class Gramma{
public:
    Gramma(std::string filename);
    std::vector<GeneratingFormula> getGeneratingFormula();
    bool isTerminator(std::string token);
    bool isEpsilon(std::string token);
    std::set<std::string> getFirstSet(std::vector<std::string> token);
    std::set<std::string> getFollowSet(std::string token);
private:
    std::vector<GeneratingFormula> _generatingFormula;
    std::set<std::string> _terminator;
};

#endif