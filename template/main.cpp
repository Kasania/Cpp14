#include <iostream>
#include "myvector.h"

auto main() -> int {
	vector<int> v1;
	std::cout << v1.cap() << std::endl;
	vector<int> v2(15);
	std::cout << v2.cap() << std::endl;
	v1 = v2;
	std::cout << v1.cap() << std::endl;
	std::cout << v2.cap() << std::endl;
	return 0;
}