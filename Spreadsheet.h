#pragma once
#include "SpreadsheetCell.h"
class Spreadsheet
{
public:
	Spreadsheet();
	Spreadsheet(int inWidth, int inHeight);
	Spreadsheet(const Spreadsheet& src);
	Spreadsheet& operator = (const Spreadsheet& rhs);
	~Spreadsheet();

	void setcellAt(int x, int y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(int x, int y);

private:
	bool inRange(int val, int upper);
	int mWidth, mHeight;
	SpreadsheetCell** mCells;
};

