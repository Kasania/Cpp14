#include "Exceptions.h"
#include "ioErrorClass.h"
#include <iostream>

auto main() -> int {

	try {
		ioErrorClass iec;
		iec.run();
		
	}
	catch (const ioException& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}