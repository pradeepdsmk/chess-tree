#include "Position.h"

namespace chess {

	void Position::buildTree()
	{
		if (isCheckMate() || isStaleMate() || isDraw()) {
			return;
		}

		buildMoves();

		for (Move* move : moves) {
			//move->execute();
			//move->evaluate();
		}
		sortMoves();
		for (Move* move : moves) {
			//move->getNextPosition()->buildTree();
		}
	}

	bool Position::isCheckMate() const
	{
		return false;
	}

	bool Position::isStaleMate() const
	{
		return false;
	}

	bool Position::isDraw() const	
	{
		return false;
	}

	void Position::buildMoves()
	{
		//Move* move = new Move(new Position(), "e2e4");
		//moves.push_back(move);
		// return moves.size();
	}

	void Position::sortMoves() const
	{
	}
}