#ifndef __Parser_H__
#define __Parser_H__

#include "Lexer.h"
#include "AST.h"
#include "Includes.h"

class Parser
{
	Lexer *lexer;
	Token NextTok;
	int index;
	vector <Exp *> expressions;

	Exp *Expr();
	Exp *CompExpr();
	Exp *ArithExpr();
	Exp *Term();
	Exp *Primary();
	void Consume(string lexeme);
	void Consume(TType tokenType);
public:
	void fill_expression();
	bool has_expressions();
	Exp* NextExp();
	Parser(Lexer*);
};
#endif
