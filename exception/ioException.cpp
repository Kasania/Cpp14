#include "ioException.h"

ioException::ioException() : std::runtime_error("") {

}

ioException::ioException(const char * inMessage) : std::runtime_error(inMessage)
{
	setMessage(inMessage);
}

ioException::ioException(const std::string & inMessage) : std::runtime_error(inMessage)
{
	setMessage(inMessage);
	
}


void ioException::setMessage(const std::string & inMessage) 
{
	message = inMessage;
}

const char * ioException::what() const noexcept 
{
	return message.c_str();
}

ioException::~ioException()
{
}
