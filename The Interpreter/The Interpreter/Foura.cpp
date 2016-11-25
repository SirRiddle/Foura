#include "Foura.h"

Foura::Foura(Parser *parser)
{
	index = 0;
	this->parser = parser;
	Scope *empty = new Scope();
	Global = new Scope(empty);
}

void Foura::Evaluate_expressions()
{
	parser->fill_expression();
	while (parser->has_expressions())
	{
		Value *val = Evaluate(parser->NextExp(), Global);
		values.push_back(val);
	}
}

bool Foura::has_Values()
{
	return index < values.size();
}

Value * Foura::NextVal()
{
	Value * val = values[index];
	index++;
	return val;
}

Value * Foura::Evaluate(Exp * exp, Scope *scope)
{
	ExpType exp_type = exp->GetType();

	if (exp_type == Int_Literal)
	{
		IntLiteral * intliteral = (IntLiteral *)exp;
		return new IntVal(intliteral->value);
	}
	if (exp_type == String_Literal)
	{
		StrLiteral * strliteral = (StrLiteral *)exp;
		return new StringVal(strliteral->value);
	}
	if (exp_type == Identifier)
	{
		Variable *new_var = (Variable *)exp;
		if (scope->IsDefined(new_var->name))
			scope->SetValue(new_var->name, Evaluate(new_var->val, scope));
		else
			scope->AddValue(new_var->name, Evaluate(new_var->val, scope));

		return Evaluate(new_var->val, scope);
	}
	if (exp_type == IdentifierCall)
	{
		VarCall *var = (VarCall *)exp;
		return scope->GetValue(var->var_name);
	}
	if (exp_type == Bi_operator)
	{
		BiOperator *binOp = (BiOperator *)exp;
		Value *op1 = Evaluate(binOp->Operand1, scope);
		Value *op2 = Evaluate(binOp->Operand2, scope);

		return DoBiOperation(binOp->Operator, op1, op2);
	}
	if (exp_type == IF)
	{
		IfElseExp *ifelse = (IfElseExp *)exp;
		Value *condition = Evaluate(ifelse->conditionExp, scope);
		IntVal *conditionValue = (IntVal *)condition;
		if (conditionValue->Val != 0)
		{
			for (int i = 0; i < ifelse->thenExp.size(); i++)
				values.push_back(Evaluate(ifelse->thenExp[i], scope));
		}
		else
		{
			for (int i = 0; i < ifelse->elseExp.size(); i++)
				values.push_back(Evaluate(ifelse->elseExp[i], scope));
		}
	}
	if (exp_type == While_exp)
	{
		While *while_loop = (While *)exp;
		Value *condition = Evaluate(while_loop->conditionExp, scope);
		IntVal *conditionValue = (IntVal *)condition;
		while (conditionValue->Val)
		{
			for (int i = 0; i < while_loop->exps.size(); i++)
				values.push_back(Evaluate(while_loop->exps[i], scope));

			condition = Evaluate(while_loop->conditionExp, scope);
			conditionValue = (IntVal *)condition;
		}
	}
	if (exp_type == Write_exp)
	{
		Write *write = (Write*)exp;
		for (int i = 0; i < write->exps.size(); i++)
		{
			Print *print = new Print();
			print->val = Evaluate(write->exps[i], scope);
			values.push_back(print);
		}
	}
	return nullptr;
}

Value * Foura::DoBiOperation(string operation, Value *op1, Value *op2)
{
	if (operation == "+")
	{
		if (op1->GetType() == INT_VALUE && op2->GetType() == INT_VALUE)
		{
			IntVal *val1 = (IntVal *)op1;
			IntVal *val2 = (IntVal *)op2;
			int result = val1->Val + val2->Val;
			return new IntVal(result);
		}

		else if (op1->GetType() == STRING_VALUE && op2->GetType() == STRING_VALUE)
		{
			StringVal *val1 = (StringVal *)op1;
			StringVal *val2 = (StringVal *)op2;
			string result = val1->Val + val2->Val;
			return new StringVal(result);
		}
		else
			throw new Error("Cannot preform this operation.");
	}
	if (operation == "-")
	{
		if (op1->GetType() == INT_VALUE && op2->GetType() == INT_VALUE)
		{
			IntVal *val1 = (IntVal *)op1;
			IntVal *val2 = (IntVal *)op2;
			int result = val1->Val - val2->Val;
			return new IntVal(result);
		}
		else
			throw new Error("Cannot preform this operation.");
	}
	if (operation == "/")
	{
		if (op1->GetType() == INT_VALUE && op2->GetType() == INT_VALUE)
		{
			IntVal *val1 = (IntVal *)op1;
			IntVal *val2 = (IntVal *)op2;
			int result = val1->Val / val2->Val;
			return new IntVal(result);
		}
		else
			throw new Error("Cannot preform this operation.");
	}
	if (operation == "*")
	{
		if (op1->GetType() == INT_VALUE	&& op2->GetType() == INT_VALUE)
		{
			IntVal *val1 = (IntVal *)op1;
			IntVal *val2 = (IntVal *)op2;
			int result = val1->Val * val2->Val;
			return new IntVal(result);
		}
		else
			throw new Error("Cannot preform this operation.");
	}
	if (operation == "==")
	{
		if (op1->GetType() == INT_VALUE && op2->GetType() == INT_VALUE)
		{
			IntVal *val1 = (IntVal *)op1;
			IntVal *val2 = (IntVal *)op2;
			int result = val1->Val == val2->Val;
			return new IntVal(result);
		}
		else if (op1->GetType() == STRING_VALUE && op2->GetType() == STRING_VALUE)
		{
			StringVal *val1 = (StringVal *)op1;
			StringVal *val2 = (StringVal *)op2;
			int result = val1->Val == val2->Val;
			return new IntVal(result);
		}
		else
			throw new Error("Cannot preform this operation.");
	}
	if (operation == "<")
	{
		if (op1->GetType() == INT_VALUE && op2->GetType() == INT_VALUE)
		{
			IntVal *val1 = (IntVal *)op1;
			IntVal *val2 = (IntVal *)op2;
			int result = val1->Val < val2->Val;
			return new IntVal(result);
		}
		else if (op1->GetType() == STRING_VALUE && op2->GetType() == STRING_VALUE)
		{
			StringVal *val1 = (StringVal *)op1;
			StringVal *val2 = (StringVal *)op2;
			int result = val1->Val < val2->Val;
			return new IntVal(result);
		}
		else
			throw new Error("Cannot preform this operation.");
	}
	if (operation == ">")
	{
		if (op1->GetType() == INT_VALUE && op2->GetType() == INT_VALUE)
		{
			IntVal *val1 = (IntVal *)op1;
			IntVal *val2 = (IntVal *)op2;
			int result = val1->Val > val2->Val;
			return new IntVal(result);
		}
		else if (op1->GetType() == STRING_VALUE && op2->GetType() == STRING_VALUE)
		{
			StringVal *val1 = (StringVal *)op1;
			StringVal *val2 = (StringVal *)op2;
			int result = val1->Val > val2->Val;
			return new IntVal(result);
		}
		else
			throw new Error("Cannot preform this operation.");
	}
	if (operation == "&&")
	{
		if (op1->GetType() == INT_VALUE && op2->GetType() == INT_VALUE)
		{
			IntVal *val1 = (IntVal *)op1;
			IntVal *val2 = (IntVal *)op2;
			int result = val1->Val && val2->Val;
			return new IntVal(result);
		}
		else
			throw new Error("Cannot preform this operation.");
	}
	if (operation == "||")
	{
		if (op1->GetType() == INT_VALUE && op2->GetType() == INT_VALUE)
		{
			IntVal *val1 = (IntVal *)op1;
			IntVal *val2 = (IntVal *)op2;
			int result = val1->Val || val2->Val;
			return new IntVal(result);
		}
		else
			throw new Error("Cannot preform this operation.");
	}
}

