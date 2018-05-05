#pragma once
#include <initializer_list>
#include <vector>
class EvenSequence
{
public:
	EvenSequence();
	EvenSequence(std::initializer_list<double> args);
	~EvenSequence();

private:
	std::vector<double> mSequence;
};

