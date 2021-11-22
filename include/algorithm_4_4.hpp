#ifndef ALGORITHM_4_4_HPP
#define ALGORITHM_4_4_HPP

#include <cstdio>
#include <string>
#include <stack>
#include <queue>
#include <map>

#include "generatingFormula.hpp"
#include "term.hpp"
#include "gramma.hpp"

std::set<Term> closure(Gramma gramma, std::set<Term> termSetI);

#endif