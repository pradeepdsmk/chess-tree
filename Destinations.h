#pragma once

#include "Square.h"
#include "Board.h"
#include "List.h"

namespace chess {

	class Board;
	class Square;

	class Destinations
	{
	public:
		List<List<Square>>* diagRays;
		List<List<Square>>* sideRays;
		List<Square>* knight;
		List<Square>* whitePawn;
		List<Square>* whitePawnAttack;
		List<Square>* blackPawn;
		List<Square>* blackPawnAttack;					

		Destinations();

		void build(Board* _board, unsigned char srcRow, unsigned char srcCol);

		void ofKnight(Board* _board, unsigned char dstRow, unsigned char dstCol);

		void ofRay(Board* _board, unsigned char srcRow, unsigned char srcCol, unsigned char y, unsigned char x);

		void ofWhitePawn(Board* _board, unsigned char dstRow, unsigned char dstCol);

		void ofWhitePawnAttack(Board* _board, unsigned char dstRow, unsigned char dstCol);

		void ofBlackPawn(Board* _board, unsigned char dstRow, unsigned char dstCol);

		void ofBlackPawnAttack(Board* _board, unsigned char dstRow, unsigned char dstCol);

		~Destinations();
	};

}