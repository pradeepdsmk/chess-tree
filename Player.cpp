#include <random>
#include "Player.h"

namespace chess {
	Player::Player(Board* _board) : board(_board) {
	}

	void Player::setOpponent(Player* player) {
		opponent = player;
	}

	void Player::init(Color _color) {
		color = _color;
		if (color == White) {
			mySquares = board->whitePieceSquares;
			yourSquares = board->blackPieceSquares;
			myPiecesStr = board->whitePiecesStr;
			yourPiecesStr = board->blackPiecesStr;
		}
		else {
			mySquares = board->blackPieceSquares;
			yourSquares = board->whitePieceSquares;
			myPiecesStr = board->blackPiecesStr;
			yourPiecesStr = board->whitePiecesStr;
		}
	}

	Move* Player::bestMove() {	
		Tree* availableMoves = board->findAvailableMoves(mySquares, yourPiecesStr);

		//List<Move>* legalMoves = new List<Move>();
		const char king = (color == White) ? 'K' : 'k';
		unsigned short numMoves = 0;
		for (TreeNode* p1 = availableMoves->tree->right;p1; p1 = p1->right) {
			Move* move = p1->move;
			board->executeMove(move);

			bool legal = true;
			Tree* opponentMoves = board->findAvailableMoves(yourSquares, myPiecesStr);
			
			for (TreeNode* p2 = opponentMoves->tree->right;p2; p2 = p2->right) {
				Move* move2 = p2->move;
				if (board->square[move2->dstRow][move2->dstCol]->piece == king) {
					legal = false;
					break;
				}
			}

			board->revertMove(move);			

			if (legal) {
				//p1->setChildren(opponentMoves);
				numMoves++;
			}
			else {
				p1 = availableMoves->remove(p1);
				//delete opponentMoves;
			}			
			delete opponentMoves;
		}

		Move* replyMove = nullptr;

		if (numMoves > 0) {
			std::default_random_engine generator;
			std::uniform_int_distribution<int> distribution(0, numMoves - 1);
			int movePos = distribution(generator);

			replyMove = availableMoves->getAt(movePos)->move->clone();
		}
		
		delete availableMoves;

		return replyMove;
	}

	bool Player::executeMove(Move* move) {
		return board->executeMove(move);
	}

	Player::~Player() {
		
	}
}
