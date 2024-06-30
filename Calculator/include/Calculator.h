#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#define M_PI 3.14159265358979323846

class Calculator {
private:
	double results;
	char op[5];
	unsigned int precision;
	bool isDouble;
	bool divByZero;
	bool firstOp;
	bool sendEquals;
	bool radians;

	void add(double input);
	void sub(double input);
	void multiply(double input);
	void divide(double input);
	void sine(double input);
	void cosine(double input);
	void tangent(double input);
	const char* calculate(double operand);
	void build_operator(char* input, unsigned int i);

public:
	bool calculated;
	bool trig;
	Calculator();
	const char* parse(char input[]);
	void get_results(char(&buffer)[256]);
	const char* del(char input[]);
	void clr();
	void set_precision(unsigned int x);
	unsigned int get_precision();
	void set_trig(int selection);
};
