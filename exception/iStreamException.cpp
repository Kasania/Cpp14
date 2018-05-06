#include "iStreamException.h"

iStreamException::iStreamException() : ioException("")
{
}

iStreamException::iStreamException(const char * inMessage) : ioException(inMessage)
{
	setMessage(inMessage);
}


iStreamException::iStreamException(const std::string & inMessage) : ioException(inMessage)
{
	setMessage(inMessage);
}

void iStreamException::setMessage(const std::string & inmessage)
{
	message = inmessage;
}
const char * iStreamException::what() const noexcept
{
	return message.c_str();
}
iStreamException::~iStreamException()
{
}
