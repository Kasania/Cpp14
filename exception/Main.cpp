#include "Exceptions.h"
#include "ioErrorClass.h"
#include <iostream>

auto main() -> int {

	try {
		ioErrorClass iec;
		iec.runIStream().runOStream();
		iec.runIStream().runOStream();
	}
	catch (const iStreamException& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (const oStreamException& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (const ioException& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}