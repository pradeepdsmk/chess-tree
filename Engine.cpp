#include "Engine.h"

namespace chess {

	Engine::Engine() {
		board = new Board();
		playerWhite = new Player(board, White);
		playerBlack = new Player(board, Black);
		isForceMode = false;
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

		Move* replyMove = playerEngine->bestMove();
		if (!replyMove) {
			std::string result;
			if (playerEngine == playerWhite) {
				result = "0-1 { Checkmate }";
			}
			else {
				result = "1-0 { Checkmate }";
			}
			output = "result " + result;
		}
		else {
			playerEngine->executeMove(replyMove);
			output = "move " + replyMove->toLAN();
		}

		colorOnMove = !colorOnMove;
	}
}