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