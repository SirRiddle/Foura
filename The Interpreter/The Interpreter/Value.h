#ifndef _VALUE_H_
#define _VALUE_H_
#include "Includes.h"
class Exp;
class Value
{
public:
	virtual ValueType GetType() = 0;
	virtual string ToString() = 0;
};
class IntVal : public Value
{
public:
	int Val;
	IntVal(int Val);
	ValueType GetType();
	string ToString();
};
class StringVal : public Value
{
public:
	string Val;
	StringVal(string Val);
	ValueType GetType();
	string ToString();
};
class Print : public Value
{
public:
	Value * val;
	ValueType GetType();
	string ToString();
};
#endif
