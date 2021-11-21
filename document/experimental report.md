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

closure(I)的构造过程：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_4.png)

构造文法LR(0)项目集规范族：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_5_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_5_2.png)

通过go函数得出识别该文法所有活前缀的DFA。

#### 构造该文法的 LR 分析表

构造文法的SLR(1)分析表：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_6_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_6_2.png)

#### 编程实现算法 4.3，构造 LR 分析程序

LR分析程序：

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_3_1.png)

![](C:\Users\chunk\Documents\Repositories\GrammaAnalysis\document\algorithm_4_3_2.png)

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

## 源程序

### YACC

#### expression.y

```
%{
    #include<stdio.h>
    #include<ctype.h>
%}
%token NUM
%%
S: S E '\n'       {printf("ans = %d\n",$2);}
 ;
E: E '+' T      {$$ = $1 + $3; printf("E -> E + T\n");}
 | E '-' T      {$$ = $1 - $3; printf("E -> E - T\n");}
 | T            {$$ = $1; printf("E -> T\n");}
 ;
T: T '*' F      {$$ = $1 * $3; printf("T -> T * F\n");}
 | T '/' F      {$$ = $1 / $3; printf("T -> T / F\n");}
 | F            {$$ = $1; printf("T -> F\n");}
 ;
F: '(' E ')'    {$$ = $2; printf("F -> ( E )\n");}
 | NUM          {$$ = $1; printf("F -> num\n");}
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

### YACC

可执行程序为./yacc/expression。在Linux下运行，在根目录./下执行：

```
cd yacc
./expression
```

## 测试报告

### YACC

#### 输入

#### 运行结果

#### 分析说明