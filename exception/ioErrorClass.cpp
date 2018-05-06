#include "ioErrorClass.h"

ioErrorClass::ioErrorClass()
{
	
}

ioErrorClass::~ioErrorClass()
{
}

int ioErrorClass::run()
{
	throw ioException("error at ioErrorClass::run()");
	return 1;
}

ioErrorClass& ioErrorClass::runIStream()
{
	std::cin >> value;
	if (value == "error") {
		//throw iStreamException("iStreamException at ioErrorClass : runIStream, value : " + value);
	}
	return *this;
}

ioErrorClass& ioErrorClass::runOStream()
{
	if (value == "error") {
		throw oStreamException("oStreamException at ioErrorClass : runOStream, value : " + value);
	}
	std::cout << value << std::endl;
	return *this;
}
