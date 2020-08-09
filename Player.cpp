#include "Player.h"

namespace chess {
	Player::Player(Board* _board, Color _color) : board(_board) {
		color = _color;
		if (color == White) {
			myPieceSquares = board->whitePieceSquares;
			yourPieceSquares = board->blackPieceSquares;
			myPiecesStr = board->whitePiecesStr;
			yourPiecesStr = board->blackPiecesStr;
			king = 'K';
		}
		else {
			myPieceSquares = board->blackPieceSquares;
			yourPieceSquares = board->whitePieceSquares;
			myPiecesStr = board->blackPiecesStr;
			yourPiecesStr = board->whitePiecesStr;
			king = 'k';
		}
	}

	Tree* Player::legalMoves() {
		return board->findLegalMoves(myPieceSquares, yourPieceSquares, myPiecesStr, yourPiecesStr, king);		
	}

	bool Player::executeMove(Move* move) {
		return board->executeMove(move, myPieceSquares, yourPieceSquares);
	}

	bool Player::isInCheck() {
		Tree* opponentMoves = board->findAvailableMoves(yourPieceSquares, myPiecesStr);
		if (board->isKingInCheck(opponentMoves, king)) {
			return true;
		} 
		return false;
	}

	Player::~Player() {
		
	}
}
