#pragma once

#include "Pieces.h"

namespace chess {

	class Square;

	class Piece
	{
	public:

		Pieces::PieceTypes name;
		bool isWhite;
		Square* square;

		Piece(Pieces::PieceTypes _name, bool _isWhite) {
			name = _name;
			isWhite = _isWhite;
			square = nullptr;
		}
	};

}