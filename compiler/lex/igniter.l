%{

#include "lex.h"
#include <stdio.h>
#include <memory.h>
#include <string>
#include <assert.h>
#include "igniter.tab.hpp"

#define YY_DECL extern "C" int yylex()
#define SAVE_TOKEN(x) { yylval.str=strdup(yytext); return x; }

void commentLine(void);
void commentBlock(void);

int tokBrace(char);

%}

%option noyywrap
%option yylineno

%%

import				{ return TOK_IMPORT; }
fun					{ return TOK_FUN; }
if					{ return TOK_IF; }
else				{ return TOK_ELSE; }
val					{ return TOK_VAL; }
return				{ return TOK_RETURN; }
true				{ return TOK_TRUE; }
false				{ return TOK_FALSE; }
unit				{ return TOK_UNIT; }

\/\/				{ commentLine(); }
\/\*				{ commentBlock(); }
[ \t\r]+			{ }
[\n]				{ } /* { if (tokBrace('\n')) return TOK_SEP; } */
[()\[\]{}]			{ tokBrace(*yytext); return *yytext; }

-?[0-9]+\.[0-9]+	{ SAVE_TOKEN(TOK_NUMBER_DOUBLE); }
-?[0-9]+			{ SAVE_TOKEN(TOK_NUMBER_INT); }

[a-z][a-zA-Z0-9]*	{ SAVE_TOKEN(L_IDENTIFIER); }
[A-Z][a-zA-Z0-9]*	{ SAVE_TOKEN(U_IDENTIFIER); }

">="				{ return TOK_GE; }
"<="				{ return TOK_LE; }
"||"				{ return TOK_OR; }
"&&"				{ return TOK_AND; }


"!="				{ return TOK_NON_EQUAL; }
"=="				{ return TOK_EQUAL; }
"->"				{ return TOK_TO; }
"<-"				{ return TOK_FROM; }
"=>"				{ return TOK_DOUBLE_TO; }
"."					{ return TOK_DOT; }
[+-/*%!]			{ return *yytext; }


\"(\\.|[^\\"\n])*\"	{
	// yylval.expr = makeValue(yytext);
	return STR_LITERAL;
}


[;]					{ return TOK_SEP; }
.					{ return *yytext; }



%%
// 输出错误
void yyerror(const char* error) {
	printf("Line %d:  %s  at  '%s'  \n", yylineno, error, yytext);
}

void commentLine(void) {
	char c = '\0';
	while (true) {
		c = yyinput();
		if (c == '\n' || c == EOF) break;
	}
}

void commentBlock(void) { 
	char c[2] = {0, 0}; 
	char depth = 1;
	while (depth != 0) {
		c[0] = c[1];
		c[1] = yyinput();
		if (c[1] == EOF) {
			throw std::runtime_error("不完整的块状注释.");
		}
		if (c[0] == '/' && c[1] == '*') {
			depth++;
		} else if (c[0] == '*' && c[1] == '/') {
			depth--;
		}
	}
}

int tokBrace(char c) {
	static char stk[0x10] = { '(' };
	static int ptr = 0;
	switch(c) {
		case '[': case '(': case '{':
			stk[++ptr] = c; 
			return 0;
		case ']': case ')': case '}':
			ptr--; return 0;
		case '\n': 
			return stk[ptr] == '{';
	}
	return 0;
}
