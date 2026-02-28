%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern FILE *yyin;
void yyerror(const char *s);
extern int yylineno;
%}

%define parse.error verbose

%token INPUT OUTPUT IF THEN ELSE END DEF RETURN MATRIX T
%token BEGIN_KW
%token ID CONST
%token PLUS MINUS TIMES DOT CROSS ASSIGN
%token EQ NEQ GT LT GE LE
%token LPAREN RPAREN LBRACKET RBRACKET COMMA

%left PLUS MINUS
%left TIMES DOT CROSS
%right ASSIGN

%%

program:
    statement_list
;

statement_list:
      statement statement_list
    | /* epsilon */
;

statement:
      input_stmt
    | output_stmt
    | if_stmt
    | def_stmt
    | return_stmt
    | assignment_stmt
    | expr_stmt
;

input_stmt: INPUT ID ;
output_stmt: OUTPUT expression expression_tail ;
expression_tail: COMMA expression expression_tail | /* epsilon */ ;
return_stmt: RETURN expression ;
assignment_stmt: ID ASSIGN expression ;
if_stmt: IF condition THEN statement_list else_part END ;
else_part: ELSE statement_list | /* epsilon */ ;
def_stmt: DEF ID LPAREN parameters_opt RPAREN BEGIN_KW statement_list END ;
parameters_opt: parameters | /* epsilon */ ;
parameters: ID parameters_tail ;
parameters_tail: COMMA ID parameters_tail | /* epsilon */ ;
expr_stmt: expression ;
expression: term expression_rest ;
expression_rest:
      PLUS term expression_rest
    | MINUS term expression_rest
    | TIMES term expression_rest
    | DOT term expression_rest
    | CROSS term expression_rest
    | /* epsilon */
;
term: base_term postfix_opt ;
postfix_opt: T | /* epsilon */ ;
base_term:
      ID
    | CONST
    | LBRACKET vector_elements RBRACKET
    | MATRIX LPAREN matrix_rows RPAREN
    | LPAREN expression RPAREN
    | function_call
;
vector_elements: expression vector_tail ;
vector_tail: COMMA expression vector_tail | /* epsilon */ ;
matrix_rows: LBRACKET vector_elements RBRACKET matrix_row_tail ;
matrix_row_tail: COMMA LBRACKET vector_elements RBRACKET matrix_row_tail | /* epsilon */ ;
function_call: ID LPAREN arguments_opt RPAREN ;
arguments_opt: arguments | /* epsilon */ ;
arguments: expression arguments_tail ;
arguments_tail: COMMA expression arguments_tail | /* epsilon */ ;
condition:
      expression EQ expression
    | expression NEQ expression
    | expression GT expression
    | expression LT expression
    | expression GE expression
    | expression LE expression
;
%%

void yyerror(const char *s) {
    extern char *yytext;
    fprintf(stderr, "Syntax error at line %d near '%s': %s\n", yylineno, yytext, s);
}

int main(int argc, char **argv) {
    extern FILE *outFile;

    if(argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if(!file) { perror("File open error"); return 1; }
        yyin = file;
    }

    outFile = fopen("output.txt", "w");
    if(!outFile) { perror("Cannot open output.txt"); return 1; }

    int result = yyparse();
    fclose(outFile);

    if(result == 0)
        printf("Syntactically correct: YES\n");
    else
        printf("Syntactically correct: NO\n");

    return result;
}
