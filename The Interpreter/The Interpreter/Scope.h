#ifndef _SCOPE_H_
#define _SCOPE_H_
#include "Includes.h"
class Value;
class Scope
{
	map < string, Value* >variables;
	Scope * parent;
	bool empty;
public:
	Scope();
	Scope(Scope *);
	Value *GetValue(string);
	void SetValue(string, Value*);
	void AddValue(string, Value *);
	Scope *FindScope(string);
	bool IsDefined(string);

};
#endif

