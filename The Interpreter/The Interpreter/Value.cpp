#include "Value.h"
#include "Includes.h"

IntVal::IntVal(int Val)
{
	this->Val = Val;
}

ValueType IntVal::GetType()
{
	return INT_VALUE;
}

string IntVal::ToString()
{
	return to_string(this->Val);
}

StringVal::StringVal(string Val)
{
	this->Val = Val;
}
ValueType StringVal::GetType()
{
	return STRING_VALUE;
}

string StringVal::ToString()
{
	return this->Val;
}

ValueType Print::GetType()
{
	return PRINT_VALUE;
}

string Print::ToString()
{
	return val->ToString();
}
