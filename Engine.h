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
		bool isAnalyzeMode;
		unsigned short maxTreeDepth;

		std::mt19937 generator;
		std::uniform_int_distribution<int> distribution;

		Tree* moveTree();
		void swapPlayers(Player** player1, Player** player2);
	public:
		Engine();
		~Engine();
		void usermove(const std::string& input, std::string& output);
		void newboard();
		void go(std::string& output);
		void enginemove(std::string& output);
		void force();	
		void setboard(const std::string& input, std::string& output);
		void analyze();
		void exit();

		int watchMoveScores(Tree* legalMoves);
		int thinkingOutput(Tree* legalMoves);

		long long treeBuildTime;
		unsigned long long executedMoveCount;
		
	};
}