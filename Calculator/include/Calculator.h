#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdio>

class Calculator {
private:
	double results;
	char op;
	bool firstOp;
	bool isDouble;
	bool divByZero;

	//void del()
	void add(double input);
	void sub(double input);
	void multiply(double input);
	void divide(double input);
	const char* calculate(double operand);

public:
	Calculator();
	const char* parse(char input[]);
};