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
		char king;

		bool isShortCastleAllowed;
		bool isLongCastleAllowed;	

		Player* opponent;

	public:
		Player(Board* _board, Color _color);
		bool executeMove(Move* move);
		Tree* legalMoves();		
		bool isInCheck();
		~Player();
	};
}

