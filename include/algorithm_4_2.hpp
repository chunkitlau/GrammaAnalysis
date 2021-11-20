#ifndef ALGORITHM_4_2_HPP
#define ALGORITHM_4_2_HPP

#include <string>
#include <vector>
#include <set>
#include <map>

#include "generatingFormula.hpp"
#include "gramma.hpp"

std::map<std::pair<std::string, std::string>, GeneratingFormula> construct(Gramma gramma);

#endif