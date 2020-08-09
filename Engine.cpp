#include "Engine.h"

namespace chess {

	Engine::Engine() {
		board = new Board();
		playerWhite = new Player(board, White);
		playerBlack = new Player(board, Black);
		isForceMode = false;

		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		generator = std::mt19937(rd()); //Standard mersenne_twister_engine seeded with rd()
		distribution = std::uniform_int_distribution<int>(1, 10000);
	}

	Engine::~Engine() {
		delete playerWhite;
		playerWhite = nullptr;

		delete playerBlack;
		playerBlack = nullptr;

		delete board;
		board = nullptr;
	}
	
	void Engine::newboard() {
		board->clear();
		board->set(Board::StartposFen);
		colorOnMove = White;
		playerEngine = playerBlack;
		playerUser = playerWhite;
		isForceMode = false;
	}

	void Engine::force() {
		isForceMode = true;
	}

	void Engine::go(std::string& output) {
		if (colorOnMove == White) {
			playerEngine = playerWhite;
			playerUser = playerBlack;
		}
		else {
			playerEngine = playerBlack;
			playerUser = playerWhite;
		}

		isForceMode = false;

		enginemove(output);
	}

	void Engine::usermove(const std::string& input, std::string& output) {
		Move* move = board->buildMove(input.c_str());

		if (!playerUser->executeMove(move)) {
			output = "Illegal move";
			return;
		}
		colorOnMove = !colorOnMove;

		if (isForceMode) {
			output = "";
			return;
		}

		enginemove(output);
	}

	void Engine::enginemove(std::string& output) {
		if (((colorOnMove == White) && (playerEngine == playerBlack))
			|| ((colorOnMove == Black) && (playerEngine == playerWhite ))) {
			output = "";
			return;
		}

		Tree* legalMoves = playerEngine->legalMoves();		

		short maxDamage = -200, damage;		
		for (TreeNode* p1 = legalMoves->tree->right;p1; p1 = p1->right) {
			damage = p1->move->score - p1->children->maxScore;
			if (damage > maxDamage) {
				maxDamage = damage;
			}
		}

		for (TreeNode* p2 = legalMoves->tree->right;p2; p2 = p2->right) {
			damage = p2->move->score - p2->children->maxScore;
			if (damage < maxDamage) {
				p2 = legalMoves->remove(p2);
			}
		}
		if (legalMoves->length > 0) {
			int movePos = distribution(generator) % legalMoves->length;
			Move* replyMove = legalMoves->getAt(movePos)->move;

			playerEngine->executeMove(replyMove);
			output = "move " + replyMove->toLAN();
			colorOnMove = !colorOnMove;
		}
		else {	
			if (playerEngine->isInCheck()) {
				if (playerEngine == playerWhite) {
					output = "0-1 { Checkmate }";
				}
				else {
					output = "1-0 { Checkmate }";
				}
			}
			else {
				output = "1/2-1/2 { Stalemate }";
			}			
		}

		delete legalMoves;
	}
}