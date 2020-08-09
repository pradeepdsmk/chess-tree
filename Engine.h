#pragma once

#include <string>
#include <random>
#include "Board.h"
#include "Player.h"
#include "Tree.h"

namespace chess {
	
	class Engine
	{
		Board* board;
		Player* playerWhite;
		Player* playerBlack;
		Player* playerEngine;
		Player* playerUser;
		Color colorOnMove;
		bool isForceMode;

		std::mt19937 generator;
		std::uniform_int_distribution<int> distribution;
	public:
		Engine();
		~Engine();
		void usermove(const std::string& input, std::string& output);
		void newboard();
		void go(std::string& output);
		void enginemove(std::string& output);
		void force();
	};
}