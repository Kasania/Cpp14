#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include "myvector.h"

auto main() -> int {
	vector<int> v1;
	try {


		for (int i = 0; i < 100000000;++i) {
			v1.insert(i);
		}
		std::cout << v1.cap() << std::endl;
		//for(auto i = v1.start(); i < v1.end();++i)
			//std::cout << i << " : "<<v1.at(i) << std::endl;
		//for (auto i = v1.start(); i < v1.end(); ++i)
		//	std::cout << i << " : " << v1.at(i) << std::endl;

			}
	catch (std::length_error e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}

