#pragma once

typedef unsigned char Chessman;

//
//           col 0 1 2 3 4 5 6 7
//	             _ _ _ _ _ _ _ _
//  row> 0    8 |_|_|_|_|_|_|_|_|
//       1    7 |_|_|_|_|_|_|_|_|
//       2    6 |_|_|_|_|_|_|_|_|
//       3    5 |_|_|_|_|_|_|_|_|
//       4    4 |_|_|_|_|_|_|_|_|
//       5    3 |_|_|_|_|_|_|_|_|
//       6    2 |_|_|_|_|_|_|_|_|
//       7    1 |_|_|_|_|_|_|_|_|
//		         a b c d e f g h


class Board {
	static const int ROWS = 8;
	static const int COLS = 8;

	Chessman square[Board::ROWS][Board::COLS];

	const char Symbol[16] = { '-', 'K', 'Q', 'B', 'N', 'R', 'P', '?', '?', 'k', 'q', 'b', 'n', 'r', 'p', '?' };

	// https://en.wikipedia.org/wiki/Chess_symbols_in_Unicode
	//wchar_t Pieces2[16] = { L'-', L'\u2654', L'\u2655', L'\u2657', L'\u2658', L'\u2656', L'\u2659', L'?', L'?', L'\u265A', L'\u265B', L'\u265D', L'\u265E', L'\u265C', L'\u265F', L'?' };

	class Coordinate {

	public:
		unsigned int row = 0xf, col = 0xf;
		bool isValid = false;

		Coordinate(const char* coordinate) {
			col = (unsigned int)(coordinate[0] - 'a');
			row = 7 - (unsigned int)(coordinate[1] - '1');
			isValid = (col < 8) && (row < 8);
		}
	};

public:

	static const Chessman COLOR_SEPERATION = 8;
	static const Chessman
		BLANK = 0,
		K = 1,
		Q = 2,
		B = 3,
		N = 4,
		R = 5,
		P = 6,
		k = Board::COLOR_SEPERATION + Board::K,
		q = Board::COLOR_SEPERATION + Board::Q,
		b = Board::COLOR_SEPERATION + Board::B,
		n = Board::COLOR_SEPERATION + Board::N,
		r = Board::COLOR_SEPERATION + Board::R,
		p = Board::COLOR_SEPERATION + Board::P;

	
	bool setChessman(Chessman c, const char* coordinate);
	Chessman getChessman(const char* coordinate);
	void clear();
	void startpos();
	void printToConsole();
	bool execute(const char* move);

};