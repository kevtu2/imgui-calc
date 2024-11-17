#pragma once
#include <string>
#include <cmath>
#define M_PI 3.14159265358979323846

class Calculator 
{
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
	const char* del(char input[]);
	void clr();

	// Getters and setters
	void set_precision(unsigned int x);
	void set_trig(int selection);
	void get_results(char(&buffer)[256]);
	unsigned int get_precision() const;
};
