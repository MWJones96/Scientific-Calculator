#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include "RPN.h"

const std::string OPS = "^/*+-";											//Supported operations
const std::string FUNCTIONS[] = {"sin", "cos", "tan", "max", "e", "pi",		//Supported functions
								 "asin", "acos", "atan", "sinh", "cosh",
								 "tanh", "asinh", "acosh", "atanh", "ln",
								 "log", "sqrt", "cbrt", "ceil", "floor",
                                 "min", "abs", "phi"};

RPN::RPN()
{
}

RPN::~RPN()
{
}

/**
	Takes in a string in infix form and ouputs a vector of tokens
	correponding to the appropriate Reverse Polish Notation representation
*/
std::vector<std::string> RPN::parseString(const std::string& exp)
{
	std::string output = "";
	std::stack<std::string> opStack;
	opStack.push(" ");

	int i = 0;
	while (i < exp.length())
	{
		//Found a numerical value
		if (isNumericalToken(exp.at(i)))
		{
			int offset = 1;
			std::string token = std::string(1, exp.at(i));

			while (i + offset < exp.size() && isNumericalToken(exp.at(i + offset)))
			{
				token += exp.at(i + offset);
				offset++;
			}

			output += token;
			output += " ";
			i += offset;
			continue;
		}
		//Found a function
		else if (isAlphaToken(exp.at(i)))
		{
			int offset = 1;
			std::string token = std::string(1, exp.at(i));

			while (i + offset < exp.size() && isAlphaToken(exp.at(i + offset)))
			{
				token += exp.at(i + offset);
				offset++;
			}

			opStack.push(token);
			i += offset;
			continue;
		}
		//Found an operator
		else if (isOperator(exp.at(i)))
		{
			while (((isFunction(opStack.top())) ||
				    (deltaPriority(exp.at(i), opStack.top()) < 0)  ||
				    ((deltaPriority(exp.at(i), opStack.top()) == 0) && (exp.at(i) != '^'))) &&
				    (opStack.top() != "("))
			{
				output += opStack.top();
				output += " ";
				opStack.pop();
			}

			opStack.push(std::string(1, exp.at(i)));
		}
		//Left bracket
		else if (exp.at(i) == '(')
		{
			opStack.push(std::string(1, exp.at(i)));
		}
		//Right bracket
		else if (exp.at(i) == ')')
		{
			while (opStack.top() != "(")
			{
				output += opStack.top();
				output += " ";
				opStack.pop();
			}

			opStack.pop();
		}
		i++;
	}

	//When there are is no more infix input, empty the stack onto the output
	while (!opStack.empty())
	{
		output += opStack.top();
		output += " ";
		opStack.pop();
	}

	std::istringstream buf(output);
	std::istream_iterator<std::string> beg(buf), end;

	std::vector<std::string> outputTokens(beg, end);

	return outputTokens;

}

/**
	Determines if the given char c represents a character in
	a numerical token (i.e. a digit 0-9 or a decimal place)
*/
bool RPN::isNumericalToken(char c)
{
	int val = (int)c;
	return (val >= 48 && val <= 57) || (val == 46);
}

/**
	Determines if the char c is in the valid list of 
	operations specified
*/
bool RPN::isOperator(char c)
{
	for (int i = 0; i < OPS.length(); i++)
	{
		if (c == OPS.at(i))
			return true;
	}

	return false;
}

/**
	Determines if the char c represents an alphabetical character,
	as part of the name of a function
*/
bool RPN::isAlphaToken(char c)
{
	int val = (int)c;
	return (val >= 65 && val <= 90) || (val >= 97 && val <= 122);
}

/**
	Computes the difference in priority between the current operation c
	and the operation on the top of the stack

	A positive return value signals that the new char is of higher
	priority and vice versa
*/
int RPN::deltaPriority(char c, std::string& topOfStack)
{
	if (!isOperator(topOfStack[0]))
		return 100;

	std::map<char, int> OP_PRIORITY;

	OP_PRIORITY['^'] = 3;
	OP_PRIORITY['/'] = 2;
	OP_PRIORITY['*'] = 2;
	OP_PRIORITY['+'] = 1;
	OP_PRIORITY['-'] = 1;

	return OP_PRIORITY[c] - OP_PRIORITY[topOfStack[0]];
}

/**
	Determines if the function name given in the string is on
	the valid list of functions specified
*/
bool RPN::isFunction(std::string& func)
{
	for (int i = 0; i < sizeof(FUNCTIONS)/sizeof(FUNCTIONS[0]); i++)
	{
		if (func == FUNCTIONS[i])
			return true;
	}

	return false;
}
