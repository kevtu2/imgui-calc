#include "Calculator.h"

Calculator::Calculator() : results{ 0 }, op{ "=" }, 
precision{12}, isDouble{false}, 
divByZero{false}, firstOp{ true }, 
sendEquals{ false }, calculated{ false }, 
radians{ true }, trig{ false } {}

void Calculator::add(double input) 
{
	this->results += input; 
}
void Calculator::sub(double input) 
{
	this->results -= input;
}
void Calculator::multiply(double input) 
{
	this->results *= input;
}
void Calculator::divide(double input) 
{
	if (input == 0) 
	{
		// Division by 0
		this->divByZero = true;
		return;
	}
	if ((int)this->results % (int)input != 0) this->isDouble = true;
	else this->isDouble = false;
	this->results = (double)(this->results / input);
}


void Calculator::sine(double input) 
{
	this->results = std::sin(input);
}

void Calculator::cosine(double input) 
{
	this->results = std::cos(input);
}

void Calculator::tangent(double input) 
{
	this->results = std::tan(input);
}

const char* Calculator::parse(char input[]) 
{
	static char tempOperand[256] = "";
	memset(tempOperand, 0, sizeof(tempOperand));
	/*if (this->sendEquals) {
		this->op = '=';
		this->calculate(0);
	}*/
	for (unsigned int i = 0; i < strlen(input); ++i) 
	{
		if (input[i] == '.') this->isDouble = true;

		if (input[i] >= '0' && input[i] <= '9' || input[i] == '.' || input[0] == '-') 
		{
			// Build the operand
			tempOperand[i] = input[i];
		} else 
		{
			tempOperand[strlen(tempOperand)] = '\0';

			if (this->trig) 
			{
				build_operator(input, i);
				this->isDouble = true;
				
				// Converts input to radians if necessary.
				if (!this->radians) snprintf(tempOperand, sizeof(tempOperand), "%.15f", atof(tempOperand) * (M_PI / 180.0));
				const char* result = calculate(atof(tempOperand));
				
				
				strncpy_s(tempOperand, sizeof(tempOperand), result, _TRUNCATE);
				this->trig = false;
				this->isDouble = false;


			} 
			else if (this->firstOp) 
			{
				this->results = atof(tempOperand);
				this->firstOp = false;
				// Builds operator (for case testing)
				build_operator(input, i);

			} 
			else 
			{
				const char* result = calculate(atof(tempOperand));
				this->calculated = true;
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
	if (this->isDouble) {
		snprintf(buffer, sizeof(buffer), "%.*f", this->precision, this->results);
	} else {
		snprintf(buffer, sizeof(buffer), "%.0f", this->results);
	}
	return;
}

const char* Calculator::calculate(double operand) 
{
	char buffer[256];
	switch ((this->op)[0]) 
	{
	case '=':
		get_results(buffer);
		this->sendEquals = true;
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
		if (this->divByZero) 
		{
			this->divByZero = false;
			return "Undefined";
		}
		break;
	}


	if (!strcmp(this->op, "sin")) sine(operand);
	else if (!strcmp(this->op, "cos")) cosine(operand);
	else if (!strcmp(this->op, "tan")) tangent(operand);

	get_results(buffer);
	return buffer;
}

void Calculator::build_operator(char* input, unsigned int i) 
{
	// Extracts the operator or math function to be used in calculation
	unsigned int j = i;
	for (; j < strlen(input); ++j) 
	{
		(this->op)[j - i] = input[j];
	}
	this->op[j - i] = '\0';
	return;
}

const char* Calculator::del(char input[]) 
{
	input[strlen(input) - 1] = '\0';
	return input;
}

void Calculator::clr() 
{
	this->results = 0;
	this->isDouble = false;
	this->firstOp = true;
	this->divByZero = false;
	this->sendEquals = false;
	this->calculated = false;
	this->trig = false;
	strcpy_s(this->op, "=");
	return;
}

void Calculator::set_precision(unsigned int x) 
{
	this->precision = x;
	return;
}

unsigned int Calculator::get_precision() 
{
	return this->precision;
}

void Calculator::set_trig(int selection) 
{
	if (selection == 0) this->radians = false;
	else this->radians = true;
	return;
}


