#pragma once
#include "ioException.h"
class oStreamException : public ioException
{
public:
	oStreamException();
	oStreamException(const char * inMessage);
	oStreamException(const std::string& inMessage);
	virtual void setMessage(const std::string& inmessage);
	virtual const char* what() const noexcept override;
	~oStreamException();
private:
	std::string message;
};

