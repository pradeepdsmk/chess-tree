#pragma once
#include <vector>

typedef unsigned char byte;

namespace chess {

	class Move;

	class Position
	{

		int64_t occupancy;
		byte white[16];
		byte black[16];


		std::vector<chess::Move*> moves;
	public:
		void buildTree();
		bool isCheckMate() const;
		bool isStaleMate() const;
		bool isDraw() const;
		void buildMoves();
		void sortMoves() const;
	};
}


