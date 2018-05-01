#include "SpreadsheetCell.h"
#include <iostream>
#include <memory>
auto main() -> int {
	SpreadsheetCell cell1,cell2;
	cell1.setValue(6);
	cell2.setString("3.2");
	std::cout << cell1.getValue() << std::endl;
	std::cout << cell2.getString() << std::endl;

	SpreadsheetCell* cell3 = new SpreadsheetCell();
	cell3->setValue(3.7);
	std::cout << cell3->getString() << std::endl;
	delete cell3;
	cell3 = nullptr;

	auto cell4 = std::make_unique<SpreadsheetCell>();
	cell4->setValue(3.8);
	std::cout << cell4->getValue() << std::endl;

	std::unique_ptr<SpreadsheetCell> cell5(new SpreadsheetCell());
	cell5->setString("4.9");
	std::cout << cell5->getValue() << std::endl;
}