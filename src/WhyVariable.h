#pragma once
#include <string>
#include <iostream>


template<typename VariableType>
class WhyVariable
{
public:
	WhyVariable() = default;
	~WhyVariable(); // clearing all the memory
	WhyVariable(int id, VariableType value);
private:
	int id; //may be changed to just var_id
	VariableType value;
};

template<typename VariableType>
inline WhyVariable<VariableType>::~WhyVariable()
{
}

template<typename VariableType>
inline WhyVariable<VariableType>::WhyVariable(int id, VariableType value)
	: id(id), value(value)
{

}