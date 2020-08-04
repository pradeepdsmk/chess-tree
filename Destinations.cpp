#include "Destinations.h"

namespace chess {

	Destinations::Destinations() {
		diagRays = new List<List<Square>>();
		sideRays = new List<List<Square>>();
		knight = new List<Square>();
		whitePawn = new List<Square>();
		whitePawnAttack = new List<Square>();
		blackPawn = new List<Square>();
		blackPawnAttack = new List<Square>();
	}

	void Destinations::build(Board* board, unsigned char srcRow, unsigned char srcCol) { 
		
		// dstKnight
		if ((srcRow > 1) && (srcCol < 7)) ofKnight(board, srcRow - 2, srcCol + 1);
		if ((srcRow > 0) && (srcCol < 6)) ofKnight(board, srcRow - 1, srcCol + 2);
		if ((srcRow < 7) && (srcCol < 6)) ofKnight(board, srcRow + 1, srcCol + 2);
		if ((srcRow < 6) && (srcCol < 7)) ofKnight(board, srcRow + 2, srcCol + 1);
		if ((srcRow < 6) && (srcCol > 1)) ofKnight(board, srcRow + 2, srcCol - 1);
		if ((srcRow < 7) && (srcCol > 2)) ofKnight(board, srcRow + 1, srcCol - 2);
		if ((srcRow > 0) && (srcCol > 1)) ofKnight(board, srcRow - 1, srcCol - 2);
		if ((srcRow > 1) && (srcCol > 0)) ofKnight(board, srcRow - 2, srcCol - 1);

		// dstDiagRay
		ofRay(board, srcRow, srcCol, -1, 1);
		ofRay(board, srcRow, srcCol, 1, 1);
		ofRay(board, srcRow, srcCol, 1, -1);
		ofRay(board, srcRow, srcCol, -1, -1);

		// dstSideRay
		ofRay(board, srcRow, srcCol, 0, 1);
		ofRay(board, srcRow, srcCol, 0, -1);
		ofRay(board, srcRow, srcCol, 1, 0);
		ofRay(board, srcRow, srcCol, -1, 0);

		// dstWhitePawn, dstWhitePawnAttack
		if ((srcRow > 0) && (srcRow < 7)) {
			ofWhitePawn(board, srcRow - 1, srcCol);
			if (srcCol > 0) ofWhitePawnAttack(board, srcRow - 1, srcCol - 1);
			if (srcCol < 7) ofWhitePawnAttack(board, srcRow - 1, srcCol + 1);
		}
		if ((srcRow == 6)) ofWhitePawn(board, 4, srcCol);

		// dstBlackPawn, dstBlackPawnAttack
		if ((srcRow > 0) && (srcRow < 7)) {
			ofBlackPawn(board, srcRow + 1, srcCol);
			if (srcCol > 0) ofBlackPawnAttack(board, srcRow + 1, srcCol - 1);
			if (srcCol < 7) ofBlackPawnAttack(board, srcRow + 1, srcCol + 1);
		}
		if ((srcRow == 1)) ofBlackPawn(board, 3, srcCol);
	};

	void Destinations::ofKnight(Board* board, unsigned char dstRow, unsigned char dstCol) {
		knight->append(board->square[dstRow][dstCol]);
	}

	void Destinations::ofRay(Board* board, unsigned char srcRow, unsigned char srcCol, unsigned char y, unsigned char x) {
		List<Square>* list = new List<Square>();
		while (1) {
			srcRow = srcRow + y;
			srcCol = srcCol + x;
			if ((srcRow < 0) || (srcRow > 7) || (srcCol < 0) || (srcCol > 7)) {
				break;
			}
			list->append(board->square[srcRow][srcCol]);
		}
		if (list->nodes) {
			if ((x == 0) || (y == 0)) {
				sideRays->append(list);
			}
			else {
				diagRays->append(list);
			}
		}
	}

	void Destinations::ofWhitePawn(Board* board, unsigned char dstRow, unsigned char dstCol) {
		whitePawn->append(board->square[dstRow][dstCol]);
	}

	void Destinations::ofWhitePawnAttack(Board* board,  unsigned char dstRow, unsigned char dstCol) {
		whitePawnAttack->append(board->square[dstRow][dstCol]);
	}

	void Destinations::ofBlackPawn(Board* board, unsigned char dstRow, unsigned char dstCol) {
		blackPawn->append(board->square[dstRow][dstCol]);
	}

	void Destinations::ofBlackPawnAttack(Board* board, unsigned char dstRow, unsigned char dstCol) {
		blackPawnAttack->append(board->square[dstRow][dstCol]);
	}

	Destinations::~Destinations() {
		delete diagRays;
		delete sideRays;
		delete knight;
		delete whitePawn;
		delete whitePawnAttack;
		delete blackPawn;
		delete blackPawnAttack;
	}
}
