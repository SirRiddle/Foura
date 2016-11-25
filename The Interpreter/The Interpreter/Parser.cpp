#include "Includes.h"
#include "Parser.h"
map<TType, string> exceptions = { { Variable_Token,"Variable" },{ Number,"Number" },{ String,"String" } };
void Parser::fill_expression()
{
	while (!NextTok.Is(Eof))
	{
		Exp *expr = Expr();
		expressions.push_back(expr);
	}
}

bool Parser::has_expressions()
{
	return index < expressions.size();
}

Exp * Parser::NextExp()
{
	Exp * expr = expressions[index];
	index++;
	return expr;
}

Exp * Parser::Expr()
{
	Exp * t = CompExpr();
	while (NextTok.Is("&&") || NextTok.Is("||"))
	{
		string theOperator = NextTok.lexeme;
		Consume(NextTok.lexeme);
		Exp *t2 = CompExpr();
		t = new BiOperator(theOperator, t, t2);
	}
	return t;
}

Exp * Parser::CompExpr()
{
	Exp *t1 = ArithExpr();
	while (NextTok.Is("==") || NextTok.Is(">") || NextTok.Is("<"))
	{
		string theOperator = NextTok.lexeme;
		Consume(NextTok.lexeme);
		Exp *t2 = ArithExpr();
		t1 = new BiOperator(theOperator, t1, t2);
	}
	return t1;
}

Exp * Parser::ArithExpr()
{
	Exp *t1 = Term();
	while (NextTok.Is("+") || NextTok.Is("-"))
	{
		string theOperator = NextTok.lexeme;
		Consume(NextTok.lexeme);
		Exp *t2 = Term();
		t1 = new BiOperator(theOperator, t1, t2);
	}
	return t1;
}

Exp * Parser::Term()
{
	Exp *t1 = Primary();
	while (NextTok.Is("*") || NextTok.Is("/"))
	{
		string theOperator = NextTok.lexeme;
		Consume(NextTok.lexeme);
		Exp *t2 = Term();
		t1 = new BiOperator(theOperator, t1, t2);
	}
	return t1;
}

Exp * Parser::Primary()
{
	Exp *t1 = NULL;
	if (NextTok.Is("("))
	{
		Consume("(");
		t1 = Expr();
		Consume(")");
		return t1;
	}
	if (NextTok.Is(Number))
	{
		int value = atoi(NextTok.lexeme.c_str());
		Consume(Number);
		t1 = new IntLiteral(value);
		return t1;
	}
	if (NextTok.Is(String))
	{
		string value = NextTok.lexeme;
		Consume(String);
		value = value.substr(1, value.size() - 2);
		t1 = new StrLiteral(value);
		return t1;
	}
	if (NextTok.Is("if"))
	{
		vector<Exp*> then_exps;
		vector<Exp*> else_exps;
		Consume("if");
		Consume("(");
		Exp* condition = Expr();
		Consume(")");
		Consume("{");
		while (!NextTok.Is("}"))
		{
			Exp *thenExp = Expr();
			then_exps.push_back(thenExp);
		}
		Consume("}");
		if (NextTok.Is("else"))
		{
			Consume("else");
			Consume("{");
			while (!NextTok.Is("}"))
			{
				Exp *elseExp = Expr();
				else_exps.push_back(elseExp);
			}
			Consume("}");
		}
		t1 = new IfElseExp(condition, then_exps, else_exps);
		return t1;
	}
	if (NextTok.Is("write"))
	{
		vector<Exp *> exps;
		Consume("write");
		Consume("(");
		while (!NextTok.Is(")"))
		{
			Exp *write_exp = Expr();
			exps.push_back(write_exp);
		}
		Consume(")");
		t1 = new Write(exps);
		return t1;

	}
	if (NextTok.Is("while"))
	{
		vector< Exp *> exps;
		Consume("while");
		Consume("(");
		Exp* condition = Expr();
		Consume(")");
		Consume("{");

		while (!NextTok.Is("}"))
		{
			Exp *while_exp = Expr();
			exps.push_back(while_exp);
		}

		Consume("}");
		t1 = new While(condition, exps);
		return t1;
	}
	if (NextTok.Is(Variable_Token))
	{
		string name = NextTok.lexeme;
		Consume(Variable_Token);
		if (NextTok.Is("="))
		{
			Consume("=");
			Exp *var_new_value_exp = Expr();
			t1 = new Variable(name, var_new_value_exp);
		}
		else
			t1 = new VarCall(name);

		return t1;
	}
	throw new Error("Unregonized Expression");
}

Parser::Parser(Lexer *L)
{
	lexer = L;
	NextTok = L->Next();
	index = 0;
}

void Parser::Consume(string lexeme)
{
	if (NextTok.lexeme == lexeme)
	{
		if (!lexer->eof())
			NextTok = lexer->Next();

		else
			NextTok.type = Eof;
	}
	else
		throw new Error("Expected " + lexeme + " Found " + NextTok.lexeme);
}

void Parser::Consume(TType tokenType)
{
	if (NextTok.type == tokenType)
	{
		if (!lexer->eof())
			NextTok = lexer->Next();

		else
			NextTok.type = Eof;
	}
	else
	{
		throw new Error("Expected token of type " + exceptions[tokenType]);
	}
}