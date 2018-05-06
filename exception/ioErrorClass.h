#pragma once
#include "Exceptions.h"
#include <iostream>
#include <string>
class ioErrorClass
{
public:
	ioErrorClass();
	~ioErrorClass();
	virtual int run();
	virtual ioErrorClass& runIStream();
	virtual ioErrorClass& runOStream();
private :
	std::string value;
};

