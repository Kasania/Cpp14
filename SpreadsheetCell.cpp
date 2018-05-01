#include "SpreadsheetCell.h"
#include <iostream>
#include <sstream>
SpreadsheetCell::SpreadsheetCell()
{
}

SpreadsheetCell::~SpreadsheetCell()
{
}
//returnvalue namespace::name const
void SpreadsheetCell::setValue(double inValue) {
	mValue = inValue;
	mString = doubleToString(mValue);
	//printCell(*this);
}
void SpreadsheetCell::setString(const std::string & inValue)
{
	mString = inValue;
	mValue = stringToDouble(mString);
	//printCell(*this);
}
double SpreadsheetCell::getValue() const{
	return mValue;
}

const std::string SpreadsheetCell::getString() const
{
	return mString;
}

std::string SpreadsheetCell::doubleToString(double inValue) const
{
	std::ostringstream ostr;
	ostr << inValue;
	return ostr.str();
}

double SpreadsheetCell::stringToDouble(const std::string & inString) const
{
	double temp;
	std::istringstream istr(inString);
	istr >> temp;
	if (istr.fail() || !istr.eof()) {
		return 0;
	}
	return temp;
}

void SpreadsheetCell::printCell(const SpreadsheetCell & inCell)
{
	std::cout << inCell.getString() << std::endl;
}


