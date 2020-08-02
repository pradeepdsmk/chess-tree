#pragma once
#include "Square.h"
#include "Board.h"
namespace chess {

	class MoveBuilder {
		Pieces::PieceTypes pieceType;
		Square* srcSquare;
		List<Move>* list;

		Board* board;

	public:
		MoveBuilder(Board* _board);

		void init(Pieces::PieceTypes _pieceType, size_t row, size_t col);

		void to(size_t row, size_t col);

		void ray(size_t x, size_t y);
	};
}