#include "EvenSequence.h"
#include <stdexcept>


EvenSequence::EvenSequence()
{
}

EvenSequence::EvenSequence(std::initializer_list<double> args)
{
	if (args.size() % 2 != 0) {
		throw std::invalid_argument("initial_list should " "contains even number of elements.");
	}
	mSequence.insert(std::cend(mSequence), std::cbegin(args), std::cend(args));
	//for (auto value : args) {
	//	mSequence.push_back(value);
	//}
	
}


EvenSequence::~EvenSequence()
{
}
