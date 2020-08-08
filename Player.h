#pragma once
#include "Board.h"

namespace chess {
	class Player
	{
		Board* board;
		Color color;
		List<Square>* myPieceSquares;
		List<Square>* yourPieceSquares;

		const char* myPiecesStr;
		const char* yourPiecesStr;

		bool isShortCastleAllowed;
		bool isLongCastleAllowed;

		Player* opponent;

	public:
		Player(Board* _board);
		void setOpponent(Player* player);
		void init(Color color);
		bool executeMove(Move* move);

		//TreeContainer* findAvailableMoves();
		Move* bestMove();
		~Player();
	};
}

