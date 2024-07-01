#pragma once
#include <cstring>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#define M_PI 3.14159265358979323846

class Calculator {
private:
	double results;
	std::string op;
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
	void parse2(std::string& tempOperand);
	std::string calculate(double operand);

public:
	bool calculated;
	bool trig;
	Calculator();
	std::string parse(std::string input);
	void get_results(std::string &buffer);
	std::string del(std::string input);
	void clr();
	void set_precision(unsigned int x);
	unsigned int get_precision();
	void set_trig(int selection);
};
