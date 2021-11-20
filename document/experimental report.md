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

预测分析表构造方法：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_2.png)

FIRST集合及其构造

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\first_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\first_2.png)

FOLLOW集合及其构造

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\follow.png)

#### 编程实现算法 4.1，构造 LL(1)预测分析程序

非递归预测分析方法：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_1_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_1_2.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_1_3.png)

### 方法 3：编写语法分析程序实现自底向上的分析

#### 构造识别该文法所有活前缀的 DFA

#### 构造该文法的 LR 分析表

#### 编程实现算法 4.3，构造 LR 分析程序

### 方法 4：利用 YACC 自动生成语法分析程序，调用 LEX 自动生成的词法分析程序

## 源程序

## 可执行程序

## 测试报告

### 输入

### 运行结果

### 分析说明