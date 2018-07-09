#include <stack>
#include <map>
#include <cmath>
#include <iostream>
#include "RPNEvaluator.h"
#include "RPN.h"

RPNEvaluator::RPNEvaluator()
{
}

RPNEvaluator::~RPNEvaluator()
{
}

/**
	Takes in the list of tokens from the RPN class and performs
	the process of calculating the final value while following the Reverse
	Polish Notation algorithm
*/
long double RPNEvaluator::evaluateRPN(std::vector<std::string>& rpn)
{
	std::stack<long double> opStack;
	opStack.push(0.0);

	for (std::string token : rpn)
	{
		//Found operator
		if (RPN::isOperator(token[0]))
		{
			//Retrieve previous two operands
			long double operand2 = opStack.top();
			opStack.pop();

			long double operand1 = opStack.top();
			opStack.pop();

			//Perform relevant operation
			switch (token[0])
			{
				case '^': opStack.push(pow(operand1, operand2));  break;
				case '/': opStack.push(operand1 / operand2); break;
				case '*': opStack.push(operand1 * operand2); break;
				case '+': opStack.push(operand1 + operand2); break;
				case '-': opStack.push(operand1 - operand2); break;
			}
		}
		//Found function name
		else if (RPN::isFunction(token))
		{
			std::map<std::string, int> functionMap;
			functionMap["sin"] = 0;
			functionMap["cos"] = 1;
			functionMap["tan"] = 2;
			functionMap["max"] = 3;

			functionMap["e"] = 4;
			functionMap["pi"] = 5;

			functionMap["asin"] = 6;
			functionMap["acos"] = 7;
			functionMap["atan"] = 8;

			functionMap["sinh"] = 9;
			functionMap["cosh"] = 10;
			functionMap["tanh"] = 11;

			functionMap["asinh"] = 12;
			functionMap["acosh"] = 13;
			functionMap["atanh"] = 14;

			functionMap["ln"] = 15;
			functionMap["log"] = 16;

			functionMap["sqrt"] = 17;
			functionMap["cbrt"] = 18;

			functionMap["ceil"] = 19;
			functionMap["floor"] = 20;
			functionMap["min"] = 21;
			functionMap["abs"] = 22;

            functionMap["phi"] = 23;

			long double operand1;
			long double operand2;

			//Determine which function to perform; most take one operand, but some take 0 or 2 operands
			switch (functionMap[token])
			{
				case 0: operand1 = opStack.top(); opStack.pop();  opStack.push(sin(operand1));  break;
				case 1: operand1 = opStack.top(); opStack.pop(); opStack.push(cos(operand1));  break;
				case 2: operand1 = opStack.top(); opStack.pop();  opStack.push(tan(operand1));  break;
				case 3: operand2 = opStack.top(); opStack.pop();
					    operand1 = opStack.top(); opStack.pop();
						opStack.push(fmax(operand1, operand2));  
						break;

				case 4: opStack.push(2.718281828459045); break;
				case 5: opStack.push(3.141592653589793); break;

				case 6: operand1 = opStack.top(); opStack.pop(); opStack.push(asin(operand1));  break;
				case 7: operand1 = opStack.top(); opStack.pop(); opStack.push(acos(operand1));  break;
				case 8: operand1 = opStack.top(); opStack.pop(); opStack.push(atan(operand1));  break;

				case 9: operand1 = opStack.top(); opStack.pop(); opStack.push(sinh(operand1));  break;
				case 10: operand1 = opStack.top(); opStack.pop(); opStack.push(cosh(operand1));  break;
				case 11: operand1 = opStack.top(); opStack.pop();  opStack.push(tanh(operand1));  break;

				case 12: operand1 = opStack.top(); opStack.pop(); opStack.push(asinh(operand1));  break;
				case 13: operand1 = opStack.top(); opStack.pop(); opStack.push(acosh(operand1));  break;
				case 14: operand1 = opStack.top(); opStack.pop();  opStack.push(atanh(operand1));  break;

				case 15: operand1 = opStack.top(); opStack.pop(); opStack.push(log(operand1));  break;
				case 16: operand1 = opStack.top(); opStack.pop(); opStack.push(log10(operand1));  break;

				case 17: operand1 = opStack.top(); opStack.pop(); opStack.push(sqrt(operand1));  break;
				case 18: operand1 = opStack.top(); opStack.pop(); opStack.push(cbrt(operand1));  break;

				case 19: operand1 = opStack.top(); opStack.pop(); opStack.push(ceil(operand1));  break;
				case 20: operand1 = opStack.top(); opStack.pop(); opStack.push(floor(operand1));  break;
				case 21: operand2 = opStack.top(); opStack.pop();
						 operand1 = opStack.top(); opStack.pop();
					     opStack.push(fmin(operand1, operand2));  
						 break;
				case 22: operand1 = opStack.top(); opStack.pop(); opStack.push(fabs(operand1));  break;
                case 23: opStack.push(1.6180339887498948482); break;
			}
		}
		//If numerical value, push onto the stack
		else if (RPN::isNumericalToken(token[0]))
		{
			opStack.push(stold(token));
		}
	}

	//Retrieve the top element of the stack, which should represent the final simplified value
	return opStack.top();
}
