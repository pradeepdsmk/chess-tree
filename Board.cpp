#include "Board.h"
#include <string.h>
#include <iostream>

bool Board::setChessman(Chessman c, const char* coordinate) {
	Coordinate co(coordinate);

	if (co.isValid) {
		square[co.row][co.col] = c;
	}

	return co.isValid;
}


Chessman Board::getChessman(const char* coordinate) {
	Coordinate co(coordinate);

	if (co.isValid) {
		return square[co.row][co.col];
	}
	else {
		return Board::BLANK;
	}
}


void Board::clear() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			square[i][j] = Board::BLANK;
		}
	}
}

void Board::startpos() {
	clear();

	setChessman(Board::R, "a1");
	setChessman(Board::N, "b1");
	setChessman(Board::B, "c1");
	setChessman(Board::Q, "d1");
	setChessman(Board::K, "e1");
	setChessman(Board::B, "f1");
	setChessman(Board::N, "g1");
	setChessman(Board::R, "h1");

	setChessman(Board::P, "a2");
	setChessman(Board::P, "b2");
	setChessman(Board::P, "c2");
	setChessman(Board::P, "d2");
	setChessman(Board::P, "e2");
	setChessman(Board::P, "f2");
	setChessman(Board::P, "g2");
	setChessman(Board::P, "h2");

	setChessman(Board::p, "a7");
	setChessman(Board::p, "b7");
	setChessman(Board::p, "c7");
	setChessman(Board::p, "d7");
	setChessman(Board::p, "e7");
	setChessman(Board::p, "f7");
	setChessman(Board::p, "g7");
	setChessman(Board::p, "h7");

	setChessman(Board::r, "a8");
	setChessman(Board::n, "b8");
	setChessman(Board::b, "c8");
	setChessman(Board::q, "d8");
	setChessman(Board::k, "e8");
	setChessman(Board::b, "f8");
	setChessman(Board::n, "g8");
	setChessman(Board::r, "h8");
}

void Board::printToConsole() {
	std::cout << std::endl;
	for (int row = 7; row >= 0; row--) {
		for (int col = 0; col < 8; col++) {
			std::cout << Symbol[square[row][col]] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool Board::execute(const char* move) {
	char dstChessman = Board::BLANK, srcChessman = Board::BLANK;
	size_t len = strlen(move);

	if (len < 4) {
		return false;
	}

	Coordinate src = Coordinate(move);
	if (!src.isValid) {
		return false;
	}

	Coordinate dst = Coordinate(move + 2);
	if (!dst.isValid) {
		return false;
	}

	dstChessman = square[src.row][src.col];

	if (len == 5) {
		char dstPromotedTo = Board::BLANK;

		if (move[4] == 'r') {
			dstPromotedTo = Board::R;
		}
		else if (move[4] == 'n') {
			dstPromotedTo = Board::N;
		}
		else if (move[4] == 'b') {
			dstPromotedTo = Board::B;
		}
		else if (move[4] == 'q') {
			dstPromotedTo = Board::Q;
		}
		else {
			return false;
		}

		if (dstChessman > Board::COLOR_SEPERATION) {
			dstPromotedTo += Board::COLOR_SEPERATION;
		}

		dstChessman = dstPromotedTo;
	}

	square[dst.row][dst.col] = dstChessman;
	square[src.row][src.col] = Board::BLANK;

	return true;
}