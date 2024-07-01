#include "Calculator.h"

Calculator::Calculator() : results{ 0 }, op{ "" }, precision{12}, isDouble{false}, divByZero{false},
firstOp{ true }, sendEquals{ false }, calculated{ false }, radians{ true }, trig{ false } {}

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


void Calculator::sine(double input) {
	this->results = std::sin(input);
}

void Calculator::cosine(double input) {
	this->results = std::cos(input);
}

void Calculator::tangent(double input) {
	this->results = std::tan(input);
}

std::string Calculator::parse(std::string input) {
	std::string tempOperand;

	for (char c : input) {
		if (c == '.') this->isDouble = true;

		if (c >= '0' && c <= '9' || c == '.' || (c == '-' && tempOperand.size() == 0)) { // 3rd OR term ensures that c is a negative sign and NOT subtraction operator
			// Build the operand
			// First checks to see if any of the current characters are part of the operand
			tempOperand.append(1, c);

		}
		else if (c == '=') {
			parse2(tempOperand);
			return tempOperand;
		}
		else if (!this->firstOp) {
			parse2(tempOperand);
			this->op.clear();
			this->op.append(1, c);
			return tempOperand;
		}
		else {
			// This needs to finish looping in case op is a trig/power function
			this->op.append(1, c);
		}
	}
	parse2(tempOperand);
	return tempOperand;
}

void Calculator::parse2(std::string& tempOperand) {

	if (this->trig) {
		this->isDouble = true;
		std::string result;

		// Convert input into radians if necessary. (Degrees or Radians can be specified by user under settings tab)
		if (!this->radians) {
			double tempOpRadians = std::stod(tempOperand) * (M_PI / 180.0);
			result = calculate(tempOpRadians);
		}
		else result = calculate(std::stod(tempOperand));

		tempOperand.assign(result);
		this->trig = false;
		this->isDouble = false;
		this->op.clear();
	}

	else if (this->firstOp) {
		this->results = std::stod(tempOperand);
		this->firstOp = false;
	}

	else {
		std::string result = calculate(std::stod(tempOperand));
		this->calculated = true;
		tempOperand.assign(result);
	}

}

void Calculator::get_results(std::string &buffer) {
	// Formats the answer to user-specified floating point precision using iomanip + sstream
	std::ostringstream oss;
	oss << std::fixed;
	if (this->isDouble) {
		oss << std::setprecision(this->precision) << this->results;
	} else {
		oss << std::setprecision(0) << this->results;
	}
	std::string formattedStr = oss.str();
	buffer.assign(formattedStr);
	return;
}

std::string Calculator::calculate(double operand) {
	std::string ret; // String to return

	if (this->op == "=") {
		get_results(ret);
		this->sendEquals = true;
		return ret;
	}
	else if (this->op == "+") add(operand);
	else if (this->op == "-") sub(operand);
	else if (this->op == "*") multiply(operand);
	else if (this->op == "/") divide(operand);
	else if (this->op == "sin") sine(operand);
	else if (this->op == "cos") cosine(operand);
	else if (this->op == "tan") tangent(operand);

	// Format precision for result
	get_results(ret);
	return ret;
}


std::string Calculator::del(std::string input) {
	input.clear();
	return input;
}

void Calculator::clr() {
	this->results = 0;
	this->isDouble = false;
	this->firstOp = true;
	this->divByZero = false;
	this->sendEquals = false;
	this->calculated = false;
	this->trig = false;
	this->op.clear();
	return;
}

void Calculator::set_precision(unsigned int x) {
	this->precision = x;
	return;
}

unsigned int Calculator::get_precision() {
	return this->precision;
}

void Calculator::set_trig(int selection) {
	if (selection == 0) this->radians = false;
	else this->radians = true;
	return;
}


