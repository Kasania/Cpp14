#pragma once
#include <string>
class SpreadsheetCell
{
public:
	SpreadsheetCell();
	~SpreadsheetCell();
	void setValue(double);
	void setString(const std::string&);
	double getValue() const;
	const std::string getString() const;

private:
	std::string doubleToString(double) const;
	double stringToDouble(const std::string&) const;
	double mValue;
	std::string mString;
	void printCell(const SpreadsheetCell&);
};

