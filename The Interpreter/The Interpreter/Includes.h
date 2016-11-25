#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#define _CRT_SECURE_NO_WARNING

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <list>
#include <iomanip>



using namespace std;

enum States {
	ready, accept, fail,
	variable,
	number,
	astring,
	equalty,
	andand,
	oror,
	increment,
	decrement
};
enum TType {
	Variable_Token,
	Number,
	String,
	Eof,
	Operator,
	Lbraces,
	Rbraces,
	Lparentheses,
	Rparentheses,
	And,
	Or,
	Equalty,
	Bthan,
	Sthan,
	Skip,
	assign,

};
enum ExpType {
	Int_Literal,
	String_Literal,
	Bi_operator,
	Identifier,
	IdentifierCall,
	IF,
	FUNC,
	FUN_CALL,
	While_exp,
	Write_exp
};
enum ValueType
{
	INT_VALUE,
	STRING_VALUE,
	PRINT_VALUE
};
class Error
{
public:
	string Message;
	Error(string msg)
	{
		Message = msg;
	}
};
#endif