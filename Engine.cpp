#include <string>
#include "Engine.h"

void chess::Engine::onMove(const std::string& input, std::string& output)
{
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
