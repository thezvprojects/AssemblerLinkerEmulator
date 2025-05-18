%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Line.h"

// Declare external vector to store parameters
extern std::vector<ParametersElement> parameters;
extern int variable_type;
extern std::vector<Line> lines;

// Function prototype
void yyerror(const char *s);
int yylex(void);
extern FILE *yyin;  // Input file for lexer

// Counters for asm d and c
int count_asmd = 0;
int count_asmc = 0;
int lineCount = 0;
%}

%union {
    char *str;  // string values type
    ParametersElement* paramElements;
}

%token ASMD_GLOBAL ASMD_EXTERN ASMD_SECTION ASMD_WORD ASMD_SKIP ASMD_END
%token ASMC_HALT ASMC_INT ASMC_IRET ASMC_RET ASMC_CALL
%token ASMC_JMP ASMC_BEQ ASMC_BNE ASMC_BGT ASMC_PUSH ASMC_POP ASMC_XCHG
%token ASMC_ADD ASMC_SUB ASMC_MUL ASMC_DIV ASMC_NOT ASMC_AND ASMC_OR ASMC_XOR
%token ASMC_SHL ASMC_SHR ASMC_LD ASMC_ST ASMC_CSRRD ASMC_CSRWR
%token COMMA NEWLINE

%token <str> LABEL PARAMETER LITERAL VALUE_OPERAND MEM_REG_OPERAND REG_VALUE CSR_VALUE HEXA_LITERAL

%type <paramElements> parameter_list parameter reg_value_operand csr_value_operand symbol_and_literal operand

%type <str> label
%%

program:
    /* Empty program */
    | program_lines
    ;

program_lines:
    program_line
    | program_lines program_line
    ;

program_line:
    nonlabelled_line
    | labelled_line
    ;

nonlabelled_line:
    base_line { parameters.clear(); }
    | NEWLINE
    ;

labelled_line:
    label label_newlines base_line
    ;

base_line:
    directive { parameters.clear(); } NEWLINE
    | command { parameters.clear(); } NEWLINE
    ;


label_newlines:
    /* Zero or more new lines */
    | label_newlines NEWLINE
    ;

label:
    LABEL 
    { 
        lines.back().setLabel(yylval.str);
        free(yylval.str);  
    }
    ;


directive:
    global parameter_list { lines.emplace_back(lineCount++, "directive", "global", parameters); }
    | extern parameter_list { lines.emplace_back(lineCount++, "directive", "extern", parameters); }
    | section section_name { lines.emplace_back(lineCount++, "directive", "section", parameters); }
    | word symbol_and_literal_list { lines.emplace_back(lineCount++, "directive", "word", parameters); }
    | skip parameter_list { lines.emplace_back(lineCount++, "directive", "skip", parameters); }
    | end
    {
        lines.emplace_back(lineCount++, "directive", "end", parameters);
        YYACCEPT; 
    }
    ;

/* zapamti da ovde ide jednom parameter sve ostalo list */
parameter_list:
    parameter_list COMMA parameter { parameters.push_back(*$3); delete $3; }
    | parameter { parameters.push_back(*$1); delete $1; }
    ;

symbol_and_literal_list:
    symbol_and_literal_list COMMA symbol_and_literal { parameters.push_back(*$3); delete $3; }
    | symbol_and_literal { parameters.push_back(*$1); delete $1; }
    ;

symbol_and_literal:
    parameter { parameters.push_back(*$1); }
    | LITERAL { $$ = new ParametersElement(ParametersElement::HEXA_LITERAL, std::string($1)); }
    | HEXA_LITERAL { $$ = new ParametersElement(ParametersElement::HEXA_LITERAL, std::string($1)); }
    ;

section_name:
    parameter { parameters.push_back(*$1); delete $1; }
    ;

parameter: PARAMETER { $$ = new ParametersElement(ParametersElement::SYMBOL, std::string($1)); }
    ;

global:
    ASMD_GLOBAL { count_asmd++; }
    ;

extern:
    ASMD_EXTERN { count_asmd++; }
    ;

section:
    ASMD_SECTION { count_asmd++; }
    ;

word:
    ASMD_WORD { count_asmd++; }
    ;

skip:
    ASMD_SKIP{ count_asmd++; }
    ;

end:
    ASMD_END { count_asmd++; }
    ;

command: 
        halt { lines.emplace_back(lineCount++, "command", "halt", parameters); }
        | int { lines.emplace_back(lineCount++, "command", "int", parameters); }
        | iret { lines.emplace_back(lineCount++, "command", "iret", parameters); }
        | call { lines.emplace_back(lineCount++, "command", "call", parameters); }
        | ret { lines.emplace_back(lineCount++, "command", "ret", parameters); }
        | jmp { lines.emplace_back(lineCount++, "command", "jmp", parameters); }
        | beq { lines.emplace_back(lineCount++, "command", "beq", parameters); }
        | bne { lines.emplace_back(lineCount++, "command", "bne", parameters); }
        | bgt { lines.emplace_back(lineCount++, "command", "bgt", parameters); }
        | push { lines.emplace_back(lineCount++, "command", "push", parameters); }
        | pop { lines.emplace_back(lineCount++, "command", "pop", parameters); }
        | xchg { lines.emplace_back(lineCount++, "command", "xchg", parameters); }
        | add { lines.emplace_back(lineCount++, "command", "add", parameters); }
        | sub { lines.emplace_back(lineCount++, "command", "sub", parameters); }
        | mul { lines.emplace_back(lineCount++, "command", "mul", parameters); }
        | div { lines.emplace_back(lineCount++, "command", "div", parameters); }
        | not { lines.emplace_back(lineCount++, "command", "not", parameters); }
        | and { lines.emplace_back(lineCount++, "command", "and", parameters); }
        | or { lines.emplace_back(lineCount++, "command", "or", parameters); }
        | xor { lines.emplace_back(lineCount++, "command", "xor", parameters); }
        | shl { lines.emplace_back(lineCount++, "command", "shl", parameters); }
        | shr { lines.emplace_back(lineCount++, "command", "shr", parameters); }
        | ld { lines.emplace_back(lineCount++, "command", "ld", parameters); }
        | st { lines.emplace_back(lineCount++, "command", "st", parameters); }
        | csrrd { lines.emplace_back(lineCount++, "command", "csrrd", parameters); }
        | csrwr { lines.emplace_back(lineCount++, "command", "csrwr", parameters); }
;

operand:
    VALUE_OPERAND { $$ = new ParametersElement(ParametersElement::VALUEOPERAND, std::string($1));}
    | MEM_REG_OPERAND { $$ = new ParametersElement(ParametersElement::MEMREGOPERAND, std::string($1)); }
    ;

reg_value_operand:
    REG_VALUE { $$ = new ParametersElement(ParametersElement::REGISTER, std::string($1)); }

csr_value_operand:
    CSR_VALUE { $$ = new ParametersElement(ParametersElement::REGISTER, std::string($1)); }

halt:
    ASMC_HALT { count_asmc++; }
    ;

int:
    ASMC_INT { count_asmc++; }
    ;

iret:
    ASMC_IRET { count_asmc++; }
    ;

call:
    ASMC_CALL { count_asmc++; } operand
    ;

ret:
    ASMC_RET { count_asmc++; }
    ;

jmp:
    ASMC_JMP { count_asmc++; } operand 
    ;

beq:
    ASMC_BEQ { count_asmc++; } reg_value_operand COMMA reg_value_operand COMMA operand
    ;

bne:
    ASMC_BNE { count_asmc++; } reg_value_operand COMMA reg_value_operand COMMA operand
    ;

bgt:
    ASMC_BGT { count_asmc++; } reg_value_operand COMMA reg_value_operand COMMA operand
    ;

push:
    ASMC_PUSH { count_asmc++; } reg_value_operand
    ;

pop:
    ASMC_POP { count_asmc++; } reg_value_operand
    ;

xchg:
    ASMC_XCHG { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

add:
    ASMC_ADD { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

sub:
    ASMC_SUB { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

mul:
    ASMC_MUL { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

div:
    ASMC_DIV { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

not:
    ASMC_NOT { count_asmc++; } reg_value_operand
    ;

and:
    ASMC_AND { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

or:
    ASMC_OR { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

xor:
    ASMC_XOR { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

shl:
    ASMC_SHL { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

shr:
    ASMC_SHR { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

ld:
    ASMC_LD { count_asmc++; } operand COMMA reg_value_operand
    ;

st:
    ASMC_ST { count_asmc++; } reg_value_operand COMMA reg_value_operand
    ;

csrrd:
    ASMC_CSRRD { count_asmc++; } csr_value_operand COMMA reg_value_operand
    ;

csrwr:
    ASMC_CSRWR { count_asmc++; } reg_value_operand COMMA csr_value_operand
    ;


%%

void yyerror(const char *s) {
    extern int yylineno;  // Provided by Lex/Flex for line numbers
    extern char *yytext;  // The current token text (Lex/Flex)
    
    // Print detailed error information
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
    fprintf(stderr, "Offending token: '%s'\n", yytext);
}
