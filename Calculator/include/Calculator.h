#pragma once
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
constexpr auto M_PI = 3.14159265358979323846;

class Calculator 
{
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
	std::string calculate(double operand);
	void build_operator(std::string input, unsigned int i);

public:
	bool calculated;
	bool trig;
	Calculator();
	std::string parse(std::string);
	void del(std::string &input);
	void clr();

	// Getters and setters
	void set_precision(unsigned int x);
	void set_trig(int selection);
	std::string get_precise(double input);
	std::string get_results();
	unsigned int get_precision() const;
};
