#include "Lexer.h"

Token::Token() {}

Token::Token(TType type, string lexeme)
{
	this->type = type;
	this->lexeme = lexeme;
}

bool Token::Is(string lexeme)
{
	return this->lexeme == lexeme;
}

bool Token::Is(TType type)
{
	return this->type == type;
}

Lexer::Lexer(string input)
{
	ptr1 = ptr2 = 0;
	state = ready;
	input += '\n';
	this->Input = input;
}

States Lexer::SwitchState(char c, States state, TType & a_type)
{
	switch (state)
	{
	case ready:
		return SwitchState_ready(c, state, a_type);
	case variable:
		return SwitchState_variable(c, state, a_type);
	case number:
		return SwitchState_number(c, state, a_type);
	case astring:
		return SwitchState_string(c, state, a_type);
	case equalty:
		return SwitchState_equality(c, state, a_type);
	case andand:
		return SwitchState_and(c, state, a_type);
	case oror:
		return SwitchState_or(c, state, a_type);
	}
}

Token Lexer::Next()
{
	char curr_c;
	TType a_type;
	while (!eof())
	{
		curr_c = read();
		state = SwitchState(curr_c, state, a_type);
		if (state == accept)
		{
			Token Tok = Accept(a_type);
			if (a_type == Skip)
				continue;

			return Tok;
		}
	}
	if (state == ready)
		return Token(Eof, "");
}

bool Lexer::eof()
{
	return !(ptr2 < Input.size());
}

void Lexer::retract()
{
	ptr2--;
}

void Lexer::reset()
{
	ptr2 = ptr1;
}

char Lexer::read()
{
	char c = Input[ptr2];
	ptr2++;
	return c;
}

Token Lexer::Accept(TType type)
{
	string lexeme = Input.substr(ptr1, ptr2 - ptr1);
	ptr1 = ptr2;
	state = ready;
	return Token(type, lexeme);
}

States Lexer::SwitchState_ready(char c, States state, TType & a_type)
{
	if (isalpha(c))
		state = variable;
	else if (isdigit(c))
		state = number;
	else if (c == '"')
		state = astring;
	else if (c == '=')
		state = equalty;
	else if (c == '&')
		state = andand;
	else if (c == '|')
		state = oror;
	else if (c == '+')
		state = increment;
	else if (c == '-')
		state = decrement;
	else if (c == '*' || c == '/')
	{
		state = accept;
		a_type = Operator;
	}
	else if (c == '(')
	{
		state = accept;
		a_type = Lparentheses;
	}
	else if (c == ')')
	{
		state = accept;
		a_type = Rparentheses;
	}
	else if (c == '{')
	{
		state = accept;
		a_type = Lbraces;
	}
	else if (c == '}')
	{
		state = accept;
		a_type = Rbraces;
	}
	else if (c == '<')
	{
		state = accept;
		a_type = Sthan;
	}
	else if (c == '>')
	{
		state = accept;
		a_type = Bthan;
	}
	else if (c == ' ' || c == '\n')
	{
		state = accept;
		a_type = Skip;
	}
	else
	{
		throw new Error(string(c + " is an unregonized token"));
	}
	return state;
}

States Lexer::SwitchState_variable(char c, States state, TType & a_type)
{
	if (isalpha(c) || isdigit(c))
		state = variable;
	else
	{
		retract();
		state = accept;
		a_type = Variable_Token;
	}
	return state;
}

States Lexer::SwitchState_number(char c, States state, TType & a_type)
{
	if (isdigit(c))
		state = number;
	else
	{
		retract();
		state = accept;
		a_type = Number;
	}
	return state;
}

States Lexer::SwitchState_string(char c, States state, TType & a_type)
{
	if (c == '"')
	{
		state = accept;
		a_type = String;
	}
	return state;
}

States Lexer::SwitchState_equality(char c, States state, TType & a_type)
{
	if (c == '=')
	{
		state = accept;
		a_type = Equalty;
	}
	else
	{
		retract();
		state = accept;
		a_type = assign;
	}
	return state;
}

States Lexer::SwitchState_and(char c, States state, TType & a_type)
{
	if (c == '&')
	{
		state = accept;
		a_type = And;
	}
	return state;
}

States Lexer::SwitchState_or(char c, States state, TType & a_type)
{
	if (c == '|')
	{
		state = accept;
		a_type = Or;
	}
	return state;
}
