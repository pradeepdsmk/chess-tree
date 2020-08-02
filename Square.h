#pragma once

#include "Piece.h"
#include "Move.h"
#include "List.h"

namespace chess {	

	class Move;

	class Square
	{
	public:
		char name[3];
		Piece* piece;
		Square* adjSquares[8];
		unsigned char row;
		unsigned char col;

		List<Move>* movesTable[7];

		Square(unsigned char _row, unsigned char _col);

		~Square();
	};

}