%{
#include "Line.h"
#include "parser.tab.h"
%}

digit         [0-9]
letter        [a-zA-Z]
hexa          [0-9a-fA-F]

%%


,           { yylval.str = strdup(yytext); return COMMA; }
[ \t]+      ; 
\n          { return NEWLINE; }
.           { return *yytext; }


".global"       { return ASMD_GLOBAL; }
".extern"       { return ASMD_EXTERN; }
".section"      { return ASMD_SECTION; }
".word"         { return ASMD_WORD; }
".skip"         { return ASMD_SKIP; }
".end"          { return ASMD_END; }

"halt"         { return ASMC_HALT; }
"int"          { return ASMC_INT; }
"iret"         { return ASMC_IRET; }
"call"         { return ASMC_CALL; }
"ret"          { return ASMC_RET; }

"jmp"          { return ASMC_JMP; }
"beq"          { return ASMC_BEQ; }
"bne"          { return ASMC_BNE; }
"bgt"          { return ASMC_BGT; }

"push"         { return ASMC_PUSH; }
"pop"          { return ASMC_POP; }

"xchg"         { return ASMC_XCHG; }

"add"          { return ASMC_ADD; }
"sub"          { return ASMC_SUB; }
"mul"          { return ASMC_MUL; }
"div"          { return ASMC_DIV; }

"not"          { return ASMC_NOT; }

"and"          { return ASMC_AND; }
"or"           { return ASMC_OR; }
"xor"          { return ASMC_XOR; }
"shl"          { return ASMC_SHL; }
"shr"          { return ASMC_SHR; }

"ld"           { return ASMC_LD; }
"st"           { return ASMC_ST; }

"csrrd"        { return ASMC_CSRRD; }
"csrwr"        { return ASMC_CSRWR; }

\[(%r([0-9]|1[0-5])|%sp|%pc)[[:space:]]*\+[[:space:]]*[0-9]+\] {
    yylval.str = strdup(yytext);
    return MEM_REG_OPERAND;
}

%r([0-9]|1[0-5])|%sp|%pc {
    yylval.str = strdup(yytext + 1);
    return REG_VALUE;
}

%(status|handler|cause) {
    yylval.str = strdup(yytext + 1);
    return CSR_VALUE;
}

{letter}({letter}|{digit})*\: {
    yylval.str = strdup(yytext);
    return LABEL;
}

${letter}({letter}|{digit})* {
    yylval.str = strdup(yytext + 1);
    return VALUE_OPERAND;
}

{letter}({letter}|{digit})* {
    yylval.str = strdup(yytext);
    return PARAMETER;
}


0[xX]{hexa}+ {
    yylval.str = strdup(yytext);
    return HEXA_LITERAL;
}


{digit}+ {
    yylval.str = strdup(yytext);
    return LITERAL;
}


%%

int yywrap() {
    return 1;
}
