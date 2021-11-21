#ifndef ALGORITHM_4_3_HPP
#define ALGORITHM_4_3_HPP

#include <cstdio>
#include <string>
#include <stack>
#include <queue>
#include <map>

#include "generatingFormula.hpp"

#define SHIFT "SHIFT"
#define REDUCE "REDUCE"
#define STARTSTATE "STARTSTATE"
#define ENDSYMBOL "ENDSYMBOL"

int analyze(std::queue<std::string> symbolString, std::map<std::pair<std::string, std::string>, std::pair<std::string, GeneratingFormula> > actionTable, std::map<std::pair<std::string, std::string>, std::string> gotoTable);

#endif