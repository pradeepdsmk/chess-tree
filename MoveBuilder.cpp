#include "MoveBuilder.h"
namespace chess {
	MoveBuilder::MoveBuilder(Board* _board) : board(_board) {
	};

	void MoveBuilder::init(Pieces::PieceTypes _pieceType, size_t row, size_t col) {
		pieceType = _pieceType;
		srcSquare = board->square[row][col];
		list = board->movesTable[pieceType][row][col];
	}

	void MoveBuilder::to(size_t row, size_t col) {
		list->append(board->moveFactory.createMove(pieceType, srcSquare, board->square[row][col]));
	}

	void MoveBuilder::ray(size_t y, size_t x) {
		size_t row = srcSquare->row;
		size_t col = srcSquare->col;
		while (1) {
			row = row + y;
			col = col + x;
			if ((row < 0) || (row > 7) || (col < 0) || (col > 7)) {
				break;
			}
			list->append(board->moveFactory.createMove(pieceType, srcSquare, board->square[row][col]));
		}		
	}
}