#include "Calculator.h"

Calculator::Calculator() : results{ 0 }, isDouble{ false }, firstOp{ true }, divByZero{ false }, op{ '=' } {} // Default ctor

void Calculator::add(double input) {
	this->results += input;
}
void Calculator::sub(double input) {
	this->results -= input;
}
void Calculator::multiply(double input) {
	this->results *= input;
}
void Calculator::divide(double input) {
	if (input == 0) {
		// Division by 0
		this->divByZero = true;
		return;
	}
	if ((int)this->results % (int)input != 0) this->isDouble = true;
	else this->isDouble = false;
	this->results = (double)(this->results / input);
}

const char* Calculator::parse(char input[]) {
	static char tempOperand[256] = "";
	memset(tempOperand, 0, sizeof(tempOperand));

	for (unsigned int i = 0; i < strlen(input); ++i) {
		if (input[i] == '.') this->isDouble = true;

		if (input[i] >= '0' && input[i] <= '9' || input[i] == '.') {
			// Build the operand
			tempOperand[i] = input[i];
		} else {
			tempOperand[strlen(tempOperand)] = '\0';
			if (this->firstOp) {
				this->results = atof(tempOperand);
				this->firstOp = false;
				this->op = input[i];
				return tempOperand;
			} else {
				const char* result = calculate(atof(tempOperand));
				strncpy_s(tempOperand, sizeof(tempOperand), result, _TRUNCATE);
				this->op = input[i];
				return tempOperand;
			}
		}
	}
}

const char* Calculator::calculate(double operand) {
	char buffer[256];
	switch (this->op) {
	case '=':
		if (this->isDouble) {
			snprintf(buffer, sizeof(buffer), "%.6f", this->results);
			return buffer;
		} else {
			snprintf(buffer, sizeof(buffer), "%.0f", this->results);
			return buffer;
		}
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
		if (this->divByZero) {
			this->divByZero = false;
			return "Undefined";
		}
		break;
	}
	if (this->isDouble) {
		snprintf(buffer, sizeof(buffer), "%.6f", this->results);
		return buffer;
	}
	else {
		snprintf(buffer, sizeof(buffer), "%.0f", this->results);
		return buffer;
	}
}

const char* Calculator::del(char input[]) {
	input[strlen(input) - 1] = '\0';
	return input;
}

void Calculator::clr() {
	this->results = 0;
	this->isDouble = false;
	this->firstOp = true;
	this->divByZero = false;
	this->op = '=';

}