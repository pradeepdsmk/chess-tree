#include "Engine.h"

namespace chess {

	Engine::Engine() {
		board = new Board();
	}

	Engine::~Engine() {
		delete board;
	}

	void Engine::usermove(const std::string& input, std::string& output) {
		board->usermove(input, output);
	}

	void Engine::newboard() {
		board->newboard();
	}
}