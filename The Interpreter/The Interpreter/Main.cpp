#include "AST.h"
#include "Foura.h"
#include "Includes.h"
#include "Lexer.h"
#include "Parser.h"
#include "Scope.h"
#include "Value.h"

int main()
{
	string input;
	getline(cin, input);
	try {
		Lexer * lexer = new Lexer(input);
		Parser *parser = new Parser(lexer);
		Foura *foura = new Foura(parser);
		foura->Evaluate_expressions();
		while (foura->has_Values())
		{
			Value *res = foura->NextVal();
			if (res != nullptr)
			{
				if (res->GetType() == PRINT_VALUE)
					cout << res->ToString() << endl;
			}
		}
	}
	catch (Error *e)
	{
		cout << e->Message << endl;
	}

}