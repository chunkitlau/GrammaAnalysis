#ifndef ALGORITHM_4_6_HPP
#define ALGORITHM_4_6_HPP

#include <string>
#include <vector>
#include <set>
#include <map>

#include "generatingFormula.hpp"
#include "term.hpp"
#include "gramma.hpp"
#include "algorithm_4_5.hpp"

std::pair<std::map<std::pair<std::string, std::string>, GeneratingFormula>, std::map<std::pair<std::string, std::string>, GeneratingFormula> > construct2(Gramma gramma);

#endif