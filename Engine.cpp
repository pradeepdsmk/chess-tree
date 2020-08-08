#include "Engine.h"

namespace chess {

	Engine::Engine() {
		board = new Board();
		players[0] = new Player(board); // engine
		players[1] = new Player(board); // user

		players[0]->setOpponent(players[1]);
		players[1]->setOpponent(players[0]);
	}

	Engine::~Engine() {
		delete players[0];
		players[0] = nullptr;

		delete players[1];
		players[1] = nullptr;

		delete board;
		board = nullptr;
	}
	
	void Engine::newboard() {
		board->clear();
		Color colorToPlay = board->set(Board::StartposFen);

		players[0]->init(!colorToPlay);
		players[1]->init(colorToPlay);
	}

	void Engine::usermove(const std::string& input, std::string& output) {
		Move* move = board->buildMove(input.c_str());

		if (!players[1]->executeMove(move)) {
			output = "Illegal move";
			return;
		}

		Move* replyMove = players[0]->bestMove();
		players[0]->executeMove(replyMove);
		output = "move " + replyMove->toLAN();
	}
}