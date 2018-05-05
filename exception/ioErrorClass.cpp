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
