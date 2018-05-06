#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
class ioException : public std::runtime_error
{
public:
	ioException();
	
	ioException(const char * inMessage);
	ioException(const std::string& inMessage);
	virtual void setMessage(const std::string& message);
	virtual const char* what() const noexcept override;
	~ioException();

private :
	std::string message;

};

