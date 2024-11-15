#include "Calculator.h"

Calculator::Calculator() : results{ 0 }, op{ "=" }, 
precision{12}, isDouble{false}, 
divByZero{false}, firstOp{ true }, 
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

const char* Calculator::parse(char input[]) 
{
	static char tempOperand[256] = "";
	memset(tempOperand, 0, sizeof(tempOperand));
	/*if (sendEquals) {
		op = '=';
		calculate(0);
	}*/
	for (unsigned int i = 0; i < strlen(input); ++i) 
	{
		if (input[i] == '.') isDouble = true;

		if (input[i] >= '0' && input[i] <= '9' || input[i] == '.' || input[0] == '-') 
		{
			// Build the operand
			tempOperand[i] = input[i];
		} else 
		{
			tempOperand[strlen(tempOperand)] = '\0';

			if (trig) 
			{
				build_operator(input, i);
				isDouble = true;
				
				// Converts input to radians if necessary.
				if (!radians) snprintf(tempOperand, sizeof(tempOperand), "%.15f", atof(tempOperand) * (M_PI / 180.0));
				const char* result = calculate(atof(tempOperand));
				
				
				strncpy_s(tempOperand, sizeof(tempOperand), result, _TRUNCATE);
				trig = false;
				isDouble = false;


			} 
			else if (firstOp) 
			{
				results = atof(tempOperand);
				firstOp = false;
				// Builds operator (for case testing)
				build_operator(input, i);

			} 
			else 
			{
				const char* result = calculate(atof(tempOperand));
				calculated = true;
				strncpy_s(tempOperand, sizeof(tempOperand), result, _TRUNCATE);
				// Builds operator (for case testing)
				build_operator(input, i);
			}
			return tempOperand;
		}
	}
}

void Calculator::get_results(char (&buffer)[256]) 
{
	// Formats the answer in the form of a C-String to be displayed via ImGui
	if (isDouble) 
	{
		snprintf(buffer, sizeof(buffer), "%.*f", precision, results);
	} else 
	{
		snprintf(buffer, sizeof(buffer), "%.0f", results);
	}
	return;
}

const char* Calculator::calculate(double operand) 
{
	char buffer[256];
	switch ((op)[0]) 
	{
	case '=':
		get_results(buffer);
		sendEquals = true;
		return buffer;
	case '+':
		add(operand);
		break;
	case '-':
		sub(operand);
		break;
	case '*':
		multiply(operand);
		break;
	case '/':
		divide(operand);
		if (divByZero) 
		{
			divByZero = false;
			return "Undefined";
		}
		break;
	}


	if (!strcmp(op, "sin")) sine(operand);
	else if (!strcmp(op, "cos")) cosine(operand);
	else if (!strcmp(op, "tan")) tangent(operand);

	get_results(buffer);
	return buffer;
}

void Calculator::build_operator(char* input, unsigned int i) 
{
	// Extracts the operator or math function to be used in calculation
	unsigned int j = i;
	for (; j < strlen(input); ++j) 
	{
		(op)[j - i] = input[j];
	}
	op[j - i] = '\0';
	return;
}

const char* Calculator::del(char input[]) 
{
	input[strlen(input) - 1] = '\0';
	return input;
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
	strcpy_s(op, "=");
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


