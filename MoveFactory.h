#pragma once

#include "List.h"
#include "Move.h"

namespace chess {
	class MoveFactory
	{
		List<Move>* moves;

		MoveFactory();
		static MoveFactory* thisInstance;

		bool parseStr(const char* str, Move* move);

	public:		
		static Move* createMove(const char* str = nullptr);
		~MoveFactory();
	};
}


