#pragma once

#include "List.h"
#include "Piece.h"

namespace chess {

	class PieceFactory
	{	
		List<Piece>* pieces;

	public:
		PieceFactory();
		Piece* createPiece(Pieces::PieceTypes pt, bool isWhite);
		void clear();
		~PieceFactory();
	};

}