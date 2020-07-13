#include "Position.h"
#include "Move.h"
#include <vector>


void chess::Position::buildTree()
{
	if (isCheckMate() || isStaleMate() || isDraw()) {
		return;
	}

	buildMoves();
	
	for(Move* move: moves) {
		move->execute();
		move->evaluate();
	}
	sortMoves();
	for(Move* move: moves) {
		move->getNextPosition()->buildTree();
	}
}

bool chess::Position::isCheckMate() const
{
	return false;
}

bool chess::Position::isStaleMate() const
{
	return false;
}

bool chess::Position::isDraw() const
{
	return false;
}

void chess::Position::buildMoves() 
{
	Move* move = new Move(new Position(), "e2e4");
	moves.push_back(move);
	// return moves.size();
}

void chess::Position::sortMoves() const
{
}
