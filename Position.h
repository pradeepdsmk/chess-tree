#pragma once

#include <vector>
#include "Move.h"

typedef unsigned char byte;

namespace chess {

	class Position
	{
		int64_t occupancy;
		byte whitePieces[16];
		byte blackPieces[16];
		byte whitePiecesCount;
		byte blackPiecesCount;

		std::vector<chess::Move*> moves;
	public:
		void buildTree();
		bool isCheckMate() const;
		bool isStaleMate() const;
		bool isDraw() const;
		void buildMoves();
		void sortMoves() const;
	};
}


