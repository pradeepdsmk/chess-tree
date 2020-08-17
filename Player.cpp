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

	Tree* Player::availableMoves() {
		return board->findAvailableMoves(myPieceSquares, yourPiecesStr);
	}

	bool Player::executeMove(Move* move) {
		return board->executeMove(move, myPieceSquares, yourPieceSquares);
	}

	bool Player::revertMove(Move* move) {
		return board->revertMove(move, myPieceSquares, yourPieceSquares);
	}

	bool Player::isKingInCheck() {
		Tree* opponentMoves = board->findAvailableMoves(yourPieceSquares, myPiecesStr);
		if (board->isKingInCheck(opponentMoves, king)) {
			return true;
		} 
		return false;
	}

	bool Player::isKingInCheck(Tree* opponentMoves) {		
		if (board->isKingInCheck(opponentMoves, king)) {
			return true;
		}
		return false;
	}

	Player::~Player() {
		
	}
}
