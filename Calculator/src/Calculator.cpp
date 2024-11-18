#include "Calculator.h"

Calculator::Calculator() : 
results{ 0 }, op{ "=" }, 
precision{ 12 }, isDouble{ false }, 
divByZero{ false }, firstOp{ true }, 
sendEquals{ false }, calculated{ false }, 
radians{ true }, trig{ false } {}

void Calculator::add(double input) 
{
	results += input; 
}
void Calculator::sub(double input) 
{
	results -= input;
}
void Calculator::multiply(double input) 
{
	results *= input;
}
void Calculator::divide(double input) 
{
	if (input == 0) 
	{
		// Division by 0
		divByZero = true;
		return;
	}
	if ((int)results % (int)input != 0) isDouble = true;
	else isDouble = false;
	results = (double)(results / input);
}


void Calculator::sine(double input) 
{
	results = std::sin(input);
}

void Calculator::cosine(double input) 
{
	results = std::cos(input);
}

void Calculator::tangent(double input) 
{
	results = std::tan(input);
}

std::string Calculator::parse(std::string input) 
{
	std::string temp_operand = "";
	for (int i = 0; i < input.length(); ++i) 
	{
		if (input[i] == '.') isDouble = true;

		if (input[i] >= '0' && input[i] <= '9' || input[i] == '.' || input[0] == '-') 
		{
			// Build the operand
			temp_operand += input[i];
		} else 
		{
			if (trig) 
			{
				build_operator(input, i);
				isDouble = true;
				
				// Converts input to radians if necessary.
				if (!radians) 
				{
					std::stringstream ss;
					ss << std::fixed << std::setprecision(15) << std::stof(temp_operand)*(M_PI / 180.0);
					temp_operand.assign(ss.str());
				}
				std::string result = calculate(std::stof(temp_operand));
				
				temp_operand.assign(result);
				trig = false;
				isDouble = false;

			} 
			else if (firstOp) 
			{
				results = std::stof(temp_operand);
				firstOp = false;
				// Builds operator (for case testing)
				build_operator(input, i);

			} 
			else 
			{
				std::string result = calculate(std::stof(temp_operand));
				calculated = true;
				// Builds operator (for case testing)
				build_operator(input, i);
			}
			return temp_operand;
		}
	}
}

std::string Calculator::get_precise(double input) 
{	
	std::stringstream ss;
	// Formats the answer based on the set precision of the calculator
	if (isDouble)
	{ // TODO: add option to use scientific notation (remove std::fixed)
		ss << std::fixed << std::setprecision(precision) << input;
	}
	else
	{
		(int)input;
	}
	return std::to_string(input);
}

std::string Calculator::get_results()
{
	return std::to_string(results);
}


std::string Calculator::calculate(double operand) 
{
	if (op == "=")
	{
		sendEquals = true;
		return get_precise(results);
	}
	else if (op == "+")
		add(operand);
	else if (op == "-")
		sub(operand);
	else if (op == "*")
		multiply(operand);
	else if (op == "/")
	{
		divide(operand);
		if (divByZero)
		{
			divByZero = false;
			return "Undefined";
		}
	}
	else if (op == "sin")
		sine(operand);
	else if (op == "cos")
		cosine(operand);
	else if (op == "tan")
		tangent(operand);

	return get_precise(results);
}

void Calculator::build_operator(std::string input, unsigned int i) 
{
	// Extracts the operator or math function to be used in calculation
	unsigned int j = i;
	for (; j < input.length(); ++j) 
	{
		(op)[j - i] = input[j];
	}
	return;
}

void Calculator::del(std::string &input) 
{
	// TODO: Change calls to this function to immediately call std::string::pop_back
	input.pop_back();
}

void Calculator::clr() 
{
	results = 0;
	isDouble = false;
	firstOp = true;
	divByZero = false;
	sendEquals = false;
	calculated = false;
	trig = false;
	op.assign("=");
	return;
}

void Calculator::set_precision(unsigned int x) 
{
	precision = x;
	return;
}

unsigned int Calculator::get_precision() const
{
	return precision;
}

void Calculator::set_trig(int selection) 
{
	if (selection == 0) radians = false;
	else radians = true;
	return;
}


