#pragma once
#include <string>
//#include "Spreadsheet.h"
class SpreadsheetCell
{
public:
	SpreadsheetCell();
	//SpreadsheetCell() : mValue(0);
	//SpreadsheetCell() = delete; explicitly deleted ctor

	SpreadsheetCell(double inValue);
	SpreadsheetCell(const std::string& inValue);

	SpreadsheetCell(const SpreadsheetCell& src); //copy ctor
	
	~SpreadsheetCell() = default;

	SpreadsheetCell& operator =(const SpreadsheetCell& rhs);
		
	void setValue(double inValue);
	void setString(const std::string& inValue);
	double getValue() const;
	const std::string getString() const;

private:
	double mValue;
	std::string mString;

	std::string doubleToString(double inValue) const;
	double stringToDouble(const std::string& inValue) const;
	void printCell(const SpreadsheetCell& inCell);
};

