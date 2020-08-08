#pragma once

#include <string>
#include "Board.h"
#include "Player.h"
#include "Tree.h"

namespace chess {
	
	class Engine
	{
		Board* board;
		Player* players[2];
	public:
		Engine();
		~Engine();
		void usermove(const std::string& input, std::string& output);
		void newboard();
	};
}