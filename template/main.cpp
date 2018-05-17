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
		v1.insert(12, 7);
		v1.insert(15, 10);

		for(auto i = v1.start(); i < v1.end();++i)
			std::cout << i << " : "<<v1.at(i) << std::endl;
		//v1.erase(10);
		v1.erase(7);
		for (auto i = v1.start(); i < v1.end(); ++i)
			std::cout << i << " : " << v1.at(i) << std::endl;

	}
	catch (std::length_error e) {
		std::cout << e.what() << std::endl;
	}

	
	return 0;
}

