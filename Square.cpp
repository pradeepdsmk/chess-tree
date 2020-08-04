#include "Square.h"


namespace chess {
	Square::Square(unsigned char _row, unsigned char _col) {
		row = _row;
		col = _col;
		dst = new Destinations();
	}

	const std::string Square::name() {
		char name[3];
		sprintf_s(name, "%c%c", 'a' + col, 7 - row + '1');
		return std::string(name);
	}

	Square::~Square() {
		delete dst;
	}
}