
#include "Engine.h"

namespace chess {

	Engine::Engine() {
		board = new Board();
	}

	Engine::~Engine() {
		delete board;
	}

	void Engine::onMove(const std::string& input, std::string& output)
	{
		/*if (board.execute(input.c_str()) == false) {
			output = "Illegal move: " + input;
			return;
		}*/

		if (input.compare("e2e4") == 0) {
			output = "move e7e5";
		}
		else if (input.compare("d2d4") == 0) {
			output = "move c7c5";
		}
		else {
			output = "resign";
		}
	}

	void Engine::newGame()
	{
		board->newBoard();
	}
}