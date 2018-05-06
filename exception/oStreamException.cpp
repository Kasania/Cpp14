#include "oStreamException.h"

oStreamException::oStreamException() : ioException("")
{
}

oStreamException::oStreamException(const char * inMessage) : ioException(inMessage)
{
	setMessage(inMessage);
}


oStreamException::oStreamException(const std::string & inMessage) : ioException(inMessage)
{
	setMessage(inMessage);
}

void oStreamException::setMessage(const std::string & inmessage)
{
	message = inmessage;
}
const char * oStreamException::what() const noexcept
{
	return message.c_str();
}

oStreamException::~oStreamException()
{
}
