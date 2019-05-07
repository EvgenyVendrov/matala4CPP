#pragma once
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

namespace bullpgia
{
//this class is made to represent the output of the "calculateBullAndPgia" function more easily and aestheticly (as asked)
class calcFunOutput
{
public:
	uint bull, pgia;
	calcFunOutput(const uint bull, const uint pgia);
	void setBull(const uint bull);
	void setPgia(const uint pgia);
	friend std::ostream &operator<<(std::ostream &os, const calcFunOutput &arg);
};

calcFunOutput calculateBullAndPgia(const string choice, const string guess);

} // namespace bullpgia