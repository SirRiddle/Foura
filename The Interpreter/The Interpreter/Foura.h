#ifndef _FOURA_H_
#define _FOURA_H_
#include "Includes.h"
#include "Scope.h"
#include "Value.h"
#include "Parser.h"
#include "AST.h"

class Foura
{
	vector <Value * > values;
	int index;
	Parser *parser;
	Value *Evaluate(Exp * ,Scope *);
	Value *DoBiOperation(string, Value*, Value*);
	Scope *Global;
public:

	Foura(Parser*);
	void Evaluate_expressions();
	bool has_Values();
	Value* NextVal();
};

#endif
