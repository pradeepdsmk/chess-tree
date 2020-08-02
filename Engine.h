#pragma once
#include "Board.h"

namespace chess {
	
	class Engine
	{
		Board* board;
	public:
		Engine();
		~Engine();
		void onMove(const std::string& input, std::string& output);
		void newGame();
	};
}