#ifndef __AST_H__
#define __AST_H__
#include "Includes.h"
class Value;

class Exp
{
public:
	Exp();
	virtual ExpType GetType() = 0;
};

class BiOperator : public Exp
{
public:
	string Operator;
	Exp *Operand1;
	Exp *Operand2;

	BiOperator(string, Exp *, Exp *);

	virtual ExpType GetType();
};
class IntLiteral : public Exp
{

public:
	int value;

	IntLiteral(int);

	virtual ExpType GetType();
};

class StrLiteral : public Exp
{

public:
	string value;

	StrLiteral(string);

	virtual ExpType GetType();
};

class VarCall : public Exp
{
public:
	string var_name;

	VarCall(string);

	virtual ExpType GetType();
};

class Variable : public Exp
{

public:
	string name;
	Exp * val;

	Variable(string, Exp*);

	virtual ExpType GetType();
};

class IfElseExp : public Exp
{

public:
	Exp *conditionExp;
	vector<Exp*> thenExp, elseExp;

	IfElseExp(Exp *condition, vector<Exp*> thenExp, vector<Exp*> elseExp);

	virtual ExpType GetType();
};

class While : public Exp
{

public:
	Exp *conditionExp;
	vector<Exp * > exps;

	While(Exp *condition, vector<Exp * > exp);

	virtual ExpType GetType();
};

class Write : public Exp
{

public:
	vector<Exp * > exps;

	Write(vector<Exp * > exp);

	virtual ExpType GetType();
};

#endif