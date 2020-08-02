#pragma once
#include "Move.h"

namespace chess {
	class MoveFactory
	{
		List<Move>* moves;

	public:
		MoveFactory();
		Move* createMove(Pieces::PieceTypes pieceType, Square* srcSquare, Square* dstSquare);
		~MoveFactory();
	};
}


