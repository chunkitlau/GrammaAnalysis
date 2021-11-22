#ifndef ALGORITHM_4_5_HPP
#define ALGORITHM_4_5_HPP

#include <cstdio>
#include <string>
#include <stack>
#include <queue>
#include <map>

#include "generatingFormula.hpp"
#include "term.hpp"
#include "gramma.hpp"
#include "algorithm_4_4.hpp"

std::set<std::set<Term> > construct(Gramma gramma);

#endif