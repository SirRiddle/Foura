#ifndef __LEXER_H__
#define __LEXER_H__
#include "Includes.h"

struct Token
{
	Token();
	TType type;
	string lexeme;
	Token(TType, string);
	bool Is(string lexeme);
	bool Is(TType type);
};

class Lexer
{
	string Input;
	int ptr1, ptr2;
	States state;
public:
	vector<Token> input_tokens;
	Token Next();
	Token Accept(TType type);
	Lexer(string);
	void retract();
	void reset();
	bool eof();
	char read();
	States SwitchState(char, States, TType&);
	States SwitchState_ready(char, States, TType&);
	States SwitchState_variable(char, States, TType&);
	States SwitchState_number(char, States, TType&);
	States SwitchState_string(char, States, TType&);
	States SwitchState_equality(char, States, TType&);
	States SwitchState_and(char, States, TType&);
	States SwitchState_or(char, States, TType&);
};
#endif