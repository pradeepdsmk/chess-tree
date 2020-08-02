#include "Square.h"
#include <stdio.h>

namespace chess {
	Square::Square(unsigned char _row, unsigned char _col) {
		row = _row;
		col = _col;

		sprintf_s(name, "%c%c", 'a' + _col, 7 - _row + '1');

		piece = nullptr;

		for (size_t i = 0; i < 7; ++i) {
			movesTable[i] = new List<Move>();
		}
	}

	Square::~Square() {
		for (size_t i = 0; i < 7; ++i) {
			delete movesTable[i];
		}
	}
}