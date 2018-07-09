#pragma once
#include <string>
#include <vector>

/**
	A class whose sole job is to take in a list of tokens generated
	from the RPN class, and to perform all the required calculations
	to produce one solitary output value
*/
class RPNEvaluator
{
public:
	RPNEvaluator();
	~RPNEvaluator();
	long double evaluateRPN(std::vector<std::string>& rpn);
protected:
private:
};