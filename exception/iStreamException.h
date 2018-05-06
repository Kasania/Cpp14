#pragma once
#include "ioException.h"
class iStreamException : public ioException
{
public:
	iStreamException();
	iStreamException(const char * inMessage);
	iStreamException(const std::string& inMessage);
	virtual void setMessage(const std::string& inmessage);
	virtual const char* what() const noexcept override;
	~iStreamException();
private:
	std::string message;
};

