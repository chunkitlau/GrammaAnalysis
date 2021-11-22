# 语法分析程序的设计与实现实验报告



[TOC]

## 实验内容及要求

编写语法分析程序，实现对算术表达式的语法分析。
要求所分析算数表达式由如下的文法产生。 
E -> E + T | E – T | T 
T -> T * F | T / F | F 
F -> ( E ) | num 

## 实现方法要求

方法 1：编写递归调用程序实现自顶向下的分析。 **（已实现）**

方法 2：编写 LL(1)语法分析程序，要求如下。 **（已实现）**

(1) 编程实现算法 4.2，为给定文法自动构造预测分析表。 

(2) 编程实现算法 4.1，构造 LL(1)预测分析程序 。 

方法 3：编写语法分析程序实现自底向上的分析，要求如下。**（已实现）**

(1) 构造识别该文法所有活前缀的 DFA。

(2) 构造该文法的 LR 分析表。

(3) 编程实现算法 4.3，构造 LR 分析程序。 

方法 4：利用 YACC 自动生成语法分析程序，调用 LEX 自动生成的词法分析程序。 **（已实现）**

## 程序设计说明

### 方法 1：编写递归调用程序实现自顶向下的分析

构造文法的预测分析程序状态转换图
E -> E + T | E – T | T 
T -> T * F | T / F | F 
F -> ( E ) | num 

首先，改写文法，消除文法中存在的左递归
E -> T E'
E' -> + T E' | - T E' | ε
T -> F T'
T' -> * F T' | / F T' | ε
F -> ( E ) | num

构造递归调用预测分析程序状态转换图

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\预测分析程序状态转换图.jpg)

化简后递归调用预测分析程序状态转换图

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\化简后预测分析程序状态转换图.jpg)

递归调用预测分析程序主体

```
void procE(void) {
    procT();
    if (token == "+" || token == "-") {
        forward pointer;
        procE();
    }
}

void procT(void) {
    procF();
    if (token == "*" || token == "/") {
        forward pointer;
        procT();
    }
}

void procF(void) {
    if (token == "(") {
        forward pointer;
        procE();
        if (token == ")") {
            forward pointer;
        }
        else error();
    }
    else if (token == "num") {
        forward pointer;
    }
    else error();
}
```

### 方法 2：编写 LL(1)语法分析程序

#### 编程实现算法 4.2，为给定文法自动构造预测分析表

##### 预测分析表构造方法：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_2.png)

##### FIRST集合及其构造

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\first_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\first_2.png)

##### FOLLOW集合及其构造

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\follow.png)

##### 编译运行

在Linux下编译运行，在根目录./下执行：

```
g++ -I./include ./source/algorithm_4_2.cpp ./source/gramma.cpp ./source/generatingFormula.cpp -o ./build/algorithm_4_2
./build/algorithm_4_2
```

##### 运行结果

```
M[E,(]=E -> T E' 
M[E,num]=E -> T E' 
M[E',)]=E' -> EPSILON 
M[E',+]=E' -> + T E' 
M[E',-]=E' -> - T E' 
M[E',ENDSYMBOL]=E' -> EPSILON 
M[F,(]=F -> ( E ) 
M[F,num]=F -> num 
M[T,(]=T -> F T' 
M[T,num]=T -> F T' 
M[T',)]=T' -> EPSILON 
M[T',*]=T' -> * F T' 
M[T',+]=T' -> EPSILON 
M[T',-]=T' -> EPSILON 
M[T',/]=T' -> / F T' 
M[T',ENDSYMBOL]=T' -> EPSILON
```

#### 编程实现算法 4.1，构造 LL(1)预测分析程序

##### 非递归预测分析方法：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_1_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_1_2.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_1_3.png)

##### 编译运行

在Linux下编译运行，在根目录./下执行：

```
g++ -I./include ./source/algorithm_4_1.cpp ./source/algorithm_4_2.cpp ./source/gramma.cpp ./source/generatingFormula.cpp -o ./build/algorithm_4_1
./build/algorithm_4_1
```

##### 待分析符号串

```
( num + num ) * num - num / num
```

##### 运行结果

```
E -> T E' 
T -> F T' 
F -> ( E ) 
E -> T E' 
T -> F T' 
F -> num 
T' -> EPSILON 
E' -> + T E' 
T -> F T' 
F -> num 
T' -> EPSILON 
E' -> EPSILON 
T' -> * F T' 
F -> num 
T' -> EPSILON 
E' -> - T E' 
T -> F T' 
F -> num 
T' -> / F T' 
F -> num 
T' -> EPSILON 
E' -> EPSILON
```

### 方法 3：编写语法分析程序实现自底向上的分析

#### 构造识别该文法所有活前缀的 DFA

##### closure(I)的构造过程：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_4.png)

##### 构造文法LR(0)项目集规范族：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_5_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_5_2.png)

##### 编译运行

在Linux下编译运行，在根目录./下执行：

```
g++ -I./include ./source/algorithm_4_5.cpp ./source/algorithm_4_4.cpp ./source/gramma.cpp ./source/term.cpp ./source/generatingFormula.cpp -o ./build/algorithm_4_5
./build/algorithm_4_5
```

##### 运行结果

```
Set 0: { [S' -> .E], [E -> .E+T], [E -> .E-T], [E -> .T], [T -> .T*F], [T -> .T/F], [T -> .F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'E' -> set 3, 'T' -> set 4, 'F' -> set 5 
Set 1: { [F -> (.E)], [E -> .E+T], [E -> .E-T], [E -> .T], [T -> .T*F], [T -> .T/F], [T -> .F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'E' -> set 6, 'T' -> set 4, 'F' -> set 5 
Set 2: { [F -> num.] } 
Set 3: { [E -> E.+T], [E -> E.-T], [S' -> E.] } |    '+' -> set 7, '-' -> set 8 
Set 4: { [E -> T.], [T -> T.*F], [T -> T./F] } |    '*' -> set 9, '/' -> set 10 
Set 5: { [T -> F.] } 
Set 6: { [E -> E.+T], [E -> E.-T], [F -> (E.)] } |    '+' -> set 7, '-' -> set 8, ')' -> set 11 
Set 7: { [E -> E+.T], [T -> .T*F], [T -> .T/F], [T -> .F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'T' -> set 12, 'F' -> set 5 
Set 8: { [E -> E-.T], [T -> .T*F], [T -> .T/F], [T -> .F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'T' -> set 13, 'F' -> set 5 
Set 9: { [T -> T*.F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'F' -> set 14 
Set 10: { [T -> T/.F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'F' -> set 15 
Set 11: { [F -> (E).] } 
Set 12: { [E -> E+T.], [T -> T.*F], [T -> T./F] } |    '*' -> set 9, '/' -> set 10 
Set 13: { [E -> E-T.], [T -> T.*F], [T -> T./F] } |    '*' -> set 9, '/' -> set 10 
Set 14: { [T -> T*F.] } 
Set 15: { [T -> T/F.] } 
```

#### 构造该文法的 LR 分析表

##### 构造文法的SLR(1)分析表：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_6_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_6_2.png)

##### 运行结果

```
State                                action                             |          goto         |
        | $     +       -       *       /       (       )       num     | E     T       F       |
0       |                                       S1              S2      | 3     4       5       |
1       |                                       S1              S2      | 6     4       5       |
2       | R7    R7      R7      R7      R7              R7              |                       |
3       | ACC   S7      S8                                              |                       |
4       | R2    R2      R2      S9      S10             R2              |                       |
5       | R5    R5      R5      R5      R5              R5              |                       |
6       |       S7      S8                              S11             |                       |
7       |                                       S1              S2      |       12      5       |
8       |                                       S1              S2      |       13      5       |
9       |                                       S1              S2      |               14      |
10      |                                       S1              S2      |               15      |
11      | R6    R6      R6      R6      R6              R6              |                       |
12      | R0    R0      R0      S9      S10             R0              |                       |
13      | R1    R1      R1      S9      S10             R1              |                       |
14      | R3    R3      R3      R3      R3              R3              |                       |
15      | R4    R4      R4      R4      R4              R4              |                       |
```

#### 编程实现算法 4.3，构造 LR 分析程序

##### LR分析程序：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_3_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_3_2.png)

##### 编译运行

在Linux下编译运行，在根目录./下执行：

```
g++ -I./include ./source/algorithm_4_3.cpp ./source/gramma.cpp ./source/term.cpp ./source/generatingFormula.cpp -o ./build/algorithm_4_3
./build/algorithm_4_3
```

##### 运行结果

```
F -> num
F = 1
T -> F
T = 1
E -> T
E = 1
F -> num
F = 2
T -> F
T = 2
E -> E + T
E = 3
F -> ( E )
F = 3
T -> F
T = 3
F -> num
F = 3
T -> T * F
T = 9
E -> T
E = 9
F -> num
F = 45
T -> F
T = 45
F -> num
F = 6
T -> T / F
T = 7
E -> E - T
E = 2
ans = 2
```

### 方法 4：利用 YACC 自动生成语法分析程序，调用 LEX 自动生成的词法分析程序

YACC程序由三部分组成

#### 说明部分

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\yacc_1.png)

#### 翻译规则部分

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\yacc_2_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\yacc_2_2.png)

#### 辅助过程部分

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\yacc_3.png)

#### 用LEX建立YACC的词法分析程序

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\yacc_4_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\yacc_4_2.png)

#### 编译运行

在Linux下安装依赖

```
sudo apt install flex
sudo apt install bison
```

在Linux下编译运行，在根目录./下执行：


```
cd yacc
flex expression.lex
bison -vdty expression.y
gcc -o expression y.tab.c lex.yy.c
./expression
```

或者

```
cd yacc
make
./expression
```

## 源程序

### 递归调用程序

```
void procE(void) {
    procT();
    if (token == "+" || token == "-") {
        forward pointer;
        procE();
    }
}

void procT(void) {
    procF();
    if (token == "*" || token == "/") {
        forward pointer;
        procT();
    }
}

void procF(void) {
    if (token == "(") {
        forward pointer;
        procE();
        if (token == ")") {
            forward pointer;
        }
        else error();
    }
    else if (token == "num") {
        forward pointer;
    }
    else error();
}
```

### LL(1)语法分析程序

#### algorithm_4_1.cpp

```
#include "algorithm_4_1.hpp"

#include <unistd.h>

int analyze(std::vector<std::string> symbleStringV, Gramma gramma, std::map<std::pair<std::string, std::string>, GeneratingFormula>analyzeTable) {
    std::stack<std::string> stack;
    stack.push(ENDSYMBOL);
    stack.push("E");
    std::queue<std::string, std::deque<std::string> > 
        symbleString(std::deque<std::string>(symbleStringV.begin(),symbleStringV.end()));
    symbleString.push(ENDSYMBOL);
    do {
        std::string stackTop = stack.top(), symbleFront = symbleString.front();
        if (gramma.isTerminator(stackTop) || (stackTop == ENDSYMBOL)) {
            if (stackTop == symbleFront) {
                stack.pop();
                symbleString.pop();
            }
            else error();
        }
        else {
            std::map<std::pair<std::string, std::string>, GeneratingFormula>::iterator 
                iter = analyzeTable.find({stackTop, symbleFront});
            if (iter != analyzeTable.end()) {
                stack.pop();
                iter->second.push(stack);
                if (stack.top() == EPSILON) {
                    stack.pop();
                }
                std::cout << iter->second.print() << std::endl;
            }
            else error();
        }
    } while (stack.top() != ENDSYMBOL);
    return 0;
}

void error() {
    std::cout << "ERROR" << std::endl;
}

int main() {
    Gramma gramma("./demo/arithmeticExpressionGramma1.txt");
    std::map<std::pair<std::string, std::string>, GeneratingFormula> analyzeTable = construct(gramma);
    std::ifstream expressionfile("./demo/arithmeticExpression1.txt"); 
    std::string symbleString;
    while(getline(expressionfile, symbleString)) {
        analyze(string2token(symbleString), gramma, analyzeTable);
    }
    return 0;
}
```

#### algorithm_4_1.hpp

```
#ifndef ALGORITHM_4_1_HPP
#define ALGORITHM_4_1_HPP

#include <cstdio>
#include <string>
#include <stack>
#include <queue>
#include <map>

#include "generatingFormula.hpp"
#include "gramma.hpp"
#include "algorithm_4_2.hpp"

void error();

#endif
```

#### algorithm_4_2.cpp

```
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

int main() {
    Gramma gramma("./demo/arithmeticExpressionGramma1.txt");
    std::map<std::pair<std::string, std::string>, GeneratingFormula> analyzeTable = construct(gramma);
    for (std::map<std::pair<std::string, std::string>, GeneratingFormula>::iterator iter = analyzeTable.begin();
        iter != analyzeTable.end(); ++iter) {
            std::cout << "M[" << iter->first.first << "," << iter->first.second << "]=" << iter->second.print() << std::endl;
        }
}
```

#### algorithm_4_2.hpp

```
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
```

#### gramma.cpp

```
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
```

#### gramma.hpp

```
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
```

#### generatingFormula.cpp

```
#include "generatingFormula.hpp"

GeneratingFormula::GeneratingFormula() {
    std::string left;
    std::vector<std::string> right;
    _left = left;
    _right = right;
}

GeneratingFormula::GeneratingFormula(std::string left, std::vector<std::string> right) {
    _left = left;
    _right = right;
}

std::string GeneratingFormula::getLeft() {
    return _left;
}

std::vector<std::string> GeneratingFormula::getRight() {
    return _right;
}

std::string GeneratingFormula::print() {
    std::string string = _left + " -> ";
    for (std::vector<std::string>::iterator iter = _right.begin();
        iter != _right.end(); ++iter) {
            string += *iter + " ";
        }
    return string;
}

void GeneratingFormula::push(std::stack<std::string> &stack) {
    for (std::vector<std::string>::reverse_iterator iter = _right.rbegin(); 
        iter != _right.rend(); ++iter ) {
            stack.push(*iter);
        }
}
```

#### generatingFormula.hpp

```
#ifndef GENERATINGFORMULA_HPP
#define GENERATINGFORMULA_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stack>

class GeneratingFormula{
public:
    GeneratingFormula();
    GeneratingFormula(std::string left, std::vector<std::string> right);
    std::string getLeft();
    std::vector<std::string> getRight();
    std::string print();
    void push(std::stack<std::string> &stack);
private:
    std::string _left;
    std::vector<std::string> _right;
};

#endif
```

### SLR语法分析程序

#### algorithm_4_3.cpp

```
#include "algorithm_4_3.hpp"

int analyze(std::queue<std::string> symbolString, std::map<std::pair<std::string, std::string>, std::pair<std::string, GeneratingFormula> > actionTable, std::map<std::pair<std::string, std::string>, std::string> gotoTable) {
    std::stack<std::string> stateStack, symbolStack;
    stateStack.push(STARTSTATE);
    symbolString.push(ENDSYMBOL);
    do {
        std::string stackTop = stateStack.top(), symbolFront = symbolString.front();
        std::map<std::pair<std::string, std::string>, std::pair<std::string, GeneratingFormula> >::iterator
            iter = actionTable.find({stackTop, symbolFront});
        if (iter != actionTable.end()) {
            if ((iter->second.first) == SHIFT) {
                symbolStack.push(symbolFront);
                stateStack.push(iter->second.second.getLeft());
                symbolString.pop();
            }
            else if (iter->second.first == REDUCE) {
                for (int k = iter->second.second.getRight().size(); k; --k) {
                    symbolStack.pop();
                }
                symbolStack.push(iter->second.second.getLeft());
                stateStack.push(gotoTable[{stateStack.top(), iter->second.second.getLeft()}]);
                iter->second.second.print();
            }
            else error();
        }
        else error();
    } while (1);
}

void error() {
    std::cout << "ERROR" << std::endl;
}
```

#### algorithm_4_4.hpp

```
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
```

#### algorithm_4_4.cpp

```
#include "algorithm_4_4.hpp"

std::set<Term> closure(Gramma gramma, std::set<Term> termSetI) {
    std::set<Term> termSetJ = termSetI, termSetJNew;
    std::vector<std::string> empty;
    std::vector<GeneratingFormula> generatingFormula = gramma.getGeneratingFormula();
    do {
        termSetJNew = termSetJ;
        for (std::set<Term>::iterator termIter = termSetJNew.begin();
            termIter != termSetJNew.end(); ++termIter) {
                std::vector<std::string> rightRight = (*termIter).getRightRight();
                if (!rightRight.empty() && !gramma.isTerminator(rightRight.front())) {
                    for (std::vector<GeneratingFormula>::iterator formulaIter = generatingFormula.begin();
                    formulaIter != generatingFormula.end(); ++formulaIter) {
                        if (formulaIter->getLeft() == rightRight.front()) {
                            Term newTerm(formulaIter->getLeft(), empty, formulaIter->getRight());
                            termSetJ.insert(newTerm);
                        }
                    }
                }
                
            }
    } while (termSetJNew.size() != termSetJ.size());
    return termSetJ;
}

void error() {
    std::cout << "ERROR" << std::endl;
}
```

#### algorithm_4_4.hpp

```
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
```

#### algorithm_4_5.cpp

```
#include "algorithm_4_5.hpp"

std::set<Term> go(std::set<Term> I, std::string token) {
    std::set<Term> result;
    for (std::set<Term>::iterator termIter = I.begin();
        termIter != I.end(); ++termIter) {
            std::vector<std::string> rightRight = termIter->getRightRight();
            if (rightRight.front() == token) {
                std::vector<std::string> rightLeft = termIter->getRightLeft();
                rightLeft.push_back(rightRight.front());
                rightRight.erase(rightRight.begin());
                Term newTerm(termIter->getLeft(), rightLeft, rightRight);
                result.insert(newTerm);
            }
        }
    return result;
}

std::string print(std::set<Term> set) {
    std::string string;
    string = "{";
    for (std::set<Term>::iterator termIter = set.begin();
        termIter != set.end(); ++termIter) {
            string += termIter->getLeft() + " -> " + 
                termIter->getRightLeft().print() + " . " + 
                termIter->getRightRight().print() + " ";
        }
    string += "}";
    return string;
}

std::set<std::set<Term> > construct(Gramma gramma) {
    std::vector<std::string> empty, E(1);
    E[0] = "E";
    Term initTerm("E'", empty, E);
    std::set<std::set<Term> > C, newC;
    std::set<Term> init;
    init.insert(initTerm);
    C.insert(closure(gramma, init));
    std::set<std::string> token = gramma.getToken();
    do {
        newC = C;
        for (std::set<std::set<Term> >::iterator closureIter = newC.begin();
            closureIter != newC.end(); ++closureIter) {
                for (std::set<std::string>::iterator tokenIter = token.begin();
                    tokenIter != token.end(); ++tokenIter) {
                        std::set<Term> newSet = closure(gramma, go(*closureIter, *tokenIter));
                        std::cout << print(*closureIter) << " read " << *tokenIter << " goto " << print(newSet) << std::endl;
                        if (!newSet.empty()) {
                            C.insert(newSet);
                        }
                    }
                
            }
    } while (newC.size() != C.size());
    return C;
}

void error() {
    std::cout << "ERROR" << std::endl;
}
```

#### algorithm_4_5.hpp

```
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
```

#### algorithm_4_6.cpp

```
#include "algorithm_4_6.hpp"

std::pair<std::map<std::pair<std::string, std::string>, GeneratingFormula>, std::map<std::pair<std::string, std::string>, GeneratingFormula> > construct2(Gramma gramma) {
    std::set<std::set<Term> > closureTable = construct(gramma);
    std::map<std::pair<std::string, std::string>, GeneratingFormula> actionTable, gotoTable;
    std::vector<GeneratingFormula> generatingFormula = gramma.getGeneratingFormula();
    for (std::vector<GeneratingFormula>::iterator iter = generatingFormula.begin();
        iter != generatingFormula.end(); ++iter) {
            std::set<std::string> firstSet = gramma.getFirstSet(iter->getRight());
            for (std::set<std::string>::iterator tokenIter = firstSet.begin();
                tokenIter != firstSet.end(); ++tokenIter) {
                    if (gramma.isTerminator(*tokenIter) && !gramma.isEpsilon(*tokenIter)) {
                        actionTable[{iter->getLeft(), *tokenIter}] = *iter;
                    }
                    if (gramma.isEpsilon(*tokenIter)){
                        std::set<std::string> followSet = gramma.getFollowSet(iter->getLeft());
                        for (std::set<std::string>::iterator followTokenIter = followSet.begin();
                            followTokenIter != followSet.end(); ++followTokenIter) {
                                gotoTable[{iter->getLeft(), *followTokenIter}] = *iter;
                            }
                    }
                }
        }
    return {actionTable, gotoTable};
}
```

#### algorithm_4_6.hpp

```
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
```

#### term.cpp

```
#include "term.hpp"

Term::Term() {
    std::string left;
    std::vector<std::string> rightLeft, rightRight;
    _left = left;
    _rightLeft = rightLeft;
    _rightRight = rightRight;
}

Term::Term(std::string left, std::vector<std::string> rightLeft, std::vector<std::string> rightRight) {
    _left = left;
    _rightLeft = rightLeft;
    _rightRight = rightRight;
}

std::string Term::getLeft() const {
    return _left;
}

std::vector<std::string> Term::getRightLeft() const {
    return _rightLeft;
}

std::vector<std::string> Term::getRightRight() const {
    return _rightRight;
}
```

#### term.hpp

```
#ifndef TERM_HPP
#define TERM_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stack>

class Term{
public:
    Term();
    Term(std::string left, std::vector<std::string> rightLeft, std::vector<std::string> rightRight);
    std::string getLeft() const;
    std::vector<std::string> getRightLeft() const;
    std::vector<std::string> getRightRight() const;
    //std::string print();
    //void push(std::stack<std::string> &stack);
private:
    std::string _left;
    std::vector<std::string> _rightLeft;
    std::vector<std::string> _rightRight;
};

#endif
```

### YACC

#### expression.y

```
%{
    #include<stdio.h>
    #include<ctype.h>
%}
%token NUM
%%
S: E '\n'       {printf("ans = %d\n",$1);}
 ;
E: E '+' T      {$$ = $1 + $3; printf("E -> E + T\nE = %d\n", $$);}
 | E '-' T      {$$ = $1 - $3; printf("E -> E - T\nE = %d\n", $$);}
 | T            {$$ = $1; printf("E -> T\nE = %d\n", $$);}
 ;
T: T '*' F      {$$ = $1 * $3; printf("T -> T * F\nT = %d\n", $$);}
 | T '/' F      {$$ = $1 / $3; printf("T -> T / F\nT = %d\n", $$);}
 | F            {$$ = $1; printf("T -> F\nT = %d\n", $$);}
 ;
F: '(' E ')'    {$$ = $2; printf("F -> ( E )\nF = %d\n", $$);}
 | NUM          {$$ = $1; printf("F -> num\nF = %d\n", $$);}
 ;
%%
int main() {
    return yyparse();
}
void yyerror(char *s) {
    printf("%s\n", s);
}
```

#### expression.lex

```
%{
    #include "y.tab.h"
%}
%%
[0-9]+                  {yylval = atoi(yytext); return NUM;}
[-/+*()\n]              {return yytext[0];}
.                       {return 0;}
%%
int yywrap(void) { 
    return 1;
}
```

## 可执行程序

### LL(1)语法分析程序

可执行程序为./build/algorithm_4_1和./build/algorithm_4_2。在Linux下运行，在根目录./下执行：

```
./build/algorithm_4_1
./build/algorithm_4_2
```

### YACC

可执行程序为./yacc/expression。在Linux下运行，在根目录./下执行：

```
cd yacc
./expression
```

## 测试报告

### LL(1)语法分析程序

#### 输入

##### 待分析文法

```
E -> T E'
E' -> + T E' | - T E' | EPSILON
T -> F T'
T' -> * F T' | / F T' | EPSILON
F -> ( E ) | num
```

##### 待分析串

```
( num + num ) * num - num / num
```

#### 运行结果

##### 预测分析表

```
M[E,(]=E -> T E' 
M[E,num]=E -> T E' 
M[E',)]=E' -> EPSILON 
M[E',+]=E' -> + T E' 
M[E',-]=E' -> - T E' 
M[E',ENDSYMBOL]=E' -> EPSILON 
M[F,(]=F -> ( E ) 
M[F,num]=F -> num 
M[T,(]=T -> F T' 
M[T,num]=T -> F T' 
M[T',)]=T' -> EPSILON 
M[T',*]=T' -> * F T' 
M[T',+]=T' -> EPSILON 
M[T',-]=T' -> EPSILON 
M[T',/]=T' -> / F T' 
M[T',ENDSYMBOL]=T' -> EPSILON
```

##### 待分析串最左推导

```
E -> T E' 
T -> F T' 
F -> ( E ) 
E -> T E' 
T -> F T' 
F -> num 
T' -> EPSILON 
E' -> + T E' 
T -> F T' 
F -> num 
T' -> EPSILON 
E' -> EPSILON 
T' -> * F T' 
F -> num 
T' -> EPSILON 
E' -> - T E' 
T -> F T' 
F -> num 
T' -> / F T' 
F -> num 
T' -> EPSILON 
E' -> EPSILON
```

#### 分析说明

分析程序读入输入串，按照栈顶状态和分析表处理，并在归约的时候输出规约所使用的生成式。

### 分析程序实现自底向上的分析

#### 运行结果

##### 识别该文法所有活前缀的 DFA

```
Set 0: { [S' -> .E], [E -> .E+T], [E -> .E-T], [E -> .T], [T -> .T*F], [T -> .T/F], [T -> .F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'E' -> set 3, 'T' -> set 4, 'F' -> set 5 
Set 1: { [F -> (.E)], [E -> .E+T], [E -> .E-T], [E -> .T], [T -> .T*F], [T -> .T/F], [T -> .F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'E' -> set 6, 'T' -> set 4, 'F' -> set 5 
Set 2: { [F -> num.] } 
Set 3: { [E -> E.+T], [E -> E.-T], [S' -> E.] } |    '+' -> set 7, '-' -> set 8 
Set 4: { [E -> T.], [T -> T.*F], [T -> T./F] } |    '*' -> set 9, '/' -> set 10 
Set 5: { [T -> F.] } 
Set 6: { [E -> E.+T], [E -> E.-T], [F -> (E.)] } |    '+' -> set 7, '-' -> set 8, ')' -> set 11 
Set 7: { [E -> E+.T], [T -> .T*F], [T -> .T/F], [T -> .F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'T' -> set 12, 'F' -> set 5 
Set 8: { [E -> E-.T], [T -> .T*F], [T -> .T/F], [T -> .F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'T' -> set 13, 'F' -> set 5 
Set 9: { [T -> T*.F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'F' -> set 14 
Set 10: { [T -> T/.F], [F -> .(E)], [F -> .num] } |    '(' -> set 1, 'num' -> set 2, 'F' -> set 15 
Set 11: { [F -> (E).] } 
Set 12: { [E -> E+T.], [T -> T.*F], [T -> T./F] } |    '*' -> set 9, '/' -> set 10 
Set 13: { [E -> E-T.], [T -> T.*F], [T -> T./F] } |    '*' -> set 9, '/' -> set 10 
Set 14: { [T -> T*F.] } 
Set 15: { [T -> T/F.] } 
```

##### 该文法的 LR 分析表

```
State                                action                             |          goto         |
        | $     +       -       *       /       (       )       num     | E     T       F       |
0       |                                       S1              S2      | 3     4       5       |
1       |                                       S1              S2      | 6     4       5       |
2       | R7    R7      R7      R7      R7              R7              |                       |
3       | ACC   S7      S8                                              |                       |
4       | R2    R2      R2      S9      S10             R2              |                       |
5       | R5    R5      R5      R5      R5              R5              |                       |
6       |       S7      S8                              S11             |                       |
7       |                                       S1              S2      |       12      5       |
8       |                                       S1              S2      |       13      5       |
9       |                                       S1              S2      |               14      |
10      |                                       S1              S2      |               15      |
11      | R6    R6      R6      R6      R6              R6              |                       |
12      | R0    R0      R0      S9      S10             R0              |                       |
13      | R1    R1      R1      S9      S10             R1              |                       |
14      | R3    R3      R3      R3      R3              R3              |                       |
15      | R4    R4      R4      R4      R4              R4              |                       |
```

##### LR 分析程序结果

```
F -> num
F = 1
T -> F
T = 1
E -> T
E = 1
F -> num
F = 2
T -> F
T = 2
E -> E + T
E = 3
F -> ( E )
F = 3
T -> F
T = 3
F -> num
F = 3
T -> T * F
T = 9
E -> T
E = 9
F -> num
F = 45
T -> F
T = 45
F -> num
F = 6
T -> T / F
T = 7
E -> E - T
E = 2
ans = 2
```

#### 分析说明

运行程序得到识别该文法所有活前缀的 DFA，该文法的 LR 分析表和LR 分析程序结果。

### YACC

#### 输入

```
(1+2)*3-45/6
```

#### 运行结果

```
F -> num
F = 1
T -> F
T = 1
E -> T
E = 1
F -> num
F = 2
T -> F
T = 2
E -> E + T
E = 3
F -> ( E )
F = 3
T -> F
T = 3
F -> num
F = 3
T -> T * F
T = 9
E -> T
E = 9
F -> num
F = 45
T -> F
T = 45
F -> num
F = 6
T -> T / F
T = 7
E -> E - T
E = 2
ans = 2
```

#### 分析说明

分析程序识别1，识别2，识别1+2，计算得到3，再识别()，识别3，识别3*3，计算得到9，识别45，识别6，识别45/6，计算得到7，识别9-7，计算得到2并输出。