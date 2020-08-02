#pragma once
#include "Square.h"
#include "Move.h"
#include "PieceFactory.h"
#include "List.h"
#include "Piece.h"
#include "MoveFactory.h"

#define White true
#define Black false

namespace chess {


	//
	//           col 0 1 2 3 4 5 6 7
	//	             _ _ _ _ _ _ _ _
	//  row> 0    8 |_|_|_|_|_|_|_|_|
	//       1    7 |_|_|_|_|_|_|_|_|
	//       2    6 |_|_|_|_|_|_|_|_|
	//       3    5 |_|_|_|_|_|_|_|_|
	//       4    4 |_|_|_|_|_|_|_|_|
	//       5    3 |_|_|_|_|_|_|_|_|
	//       6    2 |_|_|_|_|_|_|_|_|
	//       7    1 |_|_|_|_|_|_|_|_|
	//		         a b c d e f g h

	class Board {
		
		Square* square[8][8];
		bool colorToPlay;
		
		unsigned char numWhitePieces;
		unsigned char numBlackPieces;
		unsigned char numWhitePawns;
		unsigned char numBlackPawns;
		
		static const char* startposFen;
		List<Piece>* whitePieces;
		List<Piece>* blackPieces;		
		List<Move>* movesTable[7][8][8];
		PieceFactory pieceFactory;
		MoveFactory moveFactory;

		friend class MoveBuilder;		

		void clearBoard();
		void parseFen(const char* fen);

		void buildMoves(Pieces::PieceTypes pieceType, size_t row, size_t col);
		void buildQueenMoves(size_t row, size_t col);
		void buildBishopMoves(size_t row, size_t col);
		void buildKnightMoves(size_t row, size_t col);
		void buildRookMoves(size_t row, size_t col);
		void buildWhitePawnMoves(size_t row, size_t col);
		void buildBlackPawnMoves(size_t row, size_t col);

		

	public:
		Board();	

		void newBoard();
		void setBoard(const char* fen);

		void buildMovesTable();

		~Board();

	};
}