#pragma once

#include <string>
#include "Board.h"

namespace chess {
	
	class Engine
	{
		Board* board;
	public:
		Engine();
		~Engine();
		void usermove(const std::string& input, std::string& output);
		void newboard();
	};
}