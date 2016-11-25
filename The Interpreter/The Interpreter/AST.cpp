#include "Includes.h"
#include "Parser.h"
#include "AST.h"

Exp::Exp() {}

BiOperator::BiOperator(string op, Exp * exp1, Exp * exp2)
{
	Operator = op;
	Operand1 = exp1;
	Operand2 = exp2;
}

ExpType BiOperator::GetType()
{
	return Bi_operator;
}

IntLiteral::IntLiteral(int value)
{
	this->value = value;
}

ExpType IntLiteral::GetType()
{
	return Int_Literal;
}

StrLiteral::StrLiteral(string value)
{
	this->value = value;
}

ExpType StrLiteral::GetType()
{
	return String_Literal;
}

Variable::Variable(string name , Exp * val)
{
	this->name = name;
	this->val = val;
}

ExpType Variable::GetType()
{
	return Identifier;
}

IfElseExp::IfElseExp(Exp * condition, vector<Exp*> thenExp, vector<Exp*> elseExp)
{
	this->conditionExp = condition;
	this->thenExp = thenExp;
	this->elseExp = elseExp;
}

ExpType IfElseExp::GetType()
{
	return IF;
}

VarCall::VarCall(string var_name)
{
	this->var_name = var_name;
}

ExpType VarCall::GetType()
{
	return IdentifierCall;
}

While::While(Exp * condition, vector<Exp *> exps)
{
	this->conditionExp = condition;
	this->exps = exps;
}

ExpType While::GetType()
{
	return While_exp;
}

Write::Write(vector<Exp * > exps)
{
	this->exps = exps;
}

ExpType Write::GetType()
{
	return Write_exp;
}
