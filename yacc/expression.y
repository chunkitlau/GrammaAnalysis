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