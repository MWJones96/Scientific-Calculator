#pragma once
#include <string>
#include <stack>
#include <vector>
#include <map>

/**
	A class whose sole duty is to convert a String from standard #
	mathematical infix notation to its Reverse Polish Notation (RPN) 
	equivalent
*/
class RPN
{
public:
	RPN();
	~RPN();
	std::vector<std::string> parseString(const std::string& exp);

	//Auxiliary functions
	static bool isNumericalToken(char c);
	static bool isOperator(char c);
	static bool isAlphaToken(char c);
	static int deltaPriority(char c, std::string& topOfStack);
	static bool isFunction(std::string& func);
protected:
private:
};