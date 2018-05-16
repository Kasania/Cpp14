#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include "myvector.h"

auto main() -> int {
	vector<int> v1;
	vector<int> v2{ 1,2,3,4,5 };
	try {
		v1 = {1,2,3,4,5};
		v1.reserve(20);

		std::cout << v1.at(3) << std::endl;
	}
	catch (std::length_error e) {
		std::cout << e.what() << std::endl;
	}


	return 0;
}

