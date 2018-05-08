#include <iostream>
#include <string>
#include <utility>
#include "myvector.h"

auto main() -> int {
	vector<std::string> v1;
	
	v1.insert("0");
	v1.insert("1");
	v1.insert("2");
	v1.insert("3");
	v1.insert("4");
	v1.insert("5");
	v1.insert("6");
	v1.insert("7");
	v1.insert("8");
	v1.insert("9");
	std::cout << v1.at(9) << std::endl;
	
	std::cout << v1.cap() << std::endl;
	v1.insert("a");
	std::cout << v1.at(10) << std::endl;
	std::cout << v1.cap() << std::endl;

	vector<std::string> v2 = v1;
	std::cout << v2.at(10) << std::endl;
	std::cout << v2.cap() << std::endl;
	


	return 0;
}