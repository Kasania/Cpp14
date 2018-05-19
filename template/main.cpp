#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include <chrono>
#include "myvector.h"

auto main() -> int {
	long long time = 0;
	int number = 100000000;
	int rep = 100;

	for (int i = 0; i < rep; ++i) {

		vector<int> v1(10);

		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		
		for (int i = 0; i < number;++i) {
			v1.insert(i);
		}

		std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
		std::chrono::milliseconds dur = 
			std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		//std::cout << number << " elements : " <<dur.count()<< " milliSec" << std::endl;
		time += dur.count();
	}
	std::cout << "insert " << number << " elements : Avg : " << time / rep << " milliSecond" << std::endl;
	return 0;
}

