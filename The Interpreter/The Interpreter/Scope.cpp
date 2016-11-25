#include "Scope.h"
#include "Includes.h"
#include "Value.h"

Scope::Scope()
{
	empty = true;
	parent = NULL;
}
Scope::Scope(Scope *parent)
{
	this->empty = false;
	this->parent = parent;
}
Value * Scope::GetValue(string variable)
{
	if (empty)
		throw new Error(variable + " is undefined.");
	if (!empty && variables.count(variable))
		return this->variables[variable];

	return parent->GetValue(variable);
}
void Scope::AddValue(string Var_name, Value * val)
{
	this->variables[Var_name] = val;
}
void Scope::SetValue(string variable, Value * newVal)
{
	Scope * valueScope = FindScope(variable);
	valueScope->variables[variable] = newVal;
}
Scope *Scope::FindScope(string variable)
{
	if (empty)
		throw new Error(variable +" is undefined.");
	if (!empty && this->variables.count(variable))
		return this;

	return parent->FindScope(variable);
}

bool Scope::IsDefined(string name)
{
	if (variables.empty())
		return false;
	if (variables.count(name))
		return true;

	return parent->IsDefined(name);
}
