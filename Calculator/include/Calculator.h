#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdio>

class Calculator {
private:
	double results;
	char op;
	unsigned int precision;
	bool isDouble;
	bool divByZero;
	bool firstOp;
	bool sendEquals;

	void add(double input);
	void sub(double input);
	void multiply(double input);
	void divide(double input);
	const char* calculate(double operand);

public:
	bool calculated;
	Calculator();
	const char* parse(char input[]);
	void get_results(char(&buffer)[256]);
	const char* del(char input[]);
	void clr();
	void set_precision(unsigned int x);
};
