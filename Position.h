#pragma once
#include <vector>

typedef unsigned char byte;

namespace chess {

	class Move;

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


