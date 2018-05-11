#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include "myvector.h"

auto main() -> int {
	vector<int> v1;
	vector<int> v2{ 1,2,3,4,5 };
	try {
		std::cout << v2.at(3) << std::endl;
		v1 = v2;
		v1.insert(6);
		v1.insert(7);
		v1.insert(8);
		v1.insert(9);
		v1.insert(10);
		v1.reserve(30);
		//v1.insert(11);
		//std::cout << v1.at(10) << std::endl;
	}
	catch (std::length_error e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
