#pragma once

#include <string>
#include <vector>
#include "Square.h"
#include "Move.h"
#include "List.h"
#include "Destinations.h"
#include "Constants.h"
#include "Tree.h"

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


	class Square;
	class Move;
	struct Tree;

	class Board {
		friend class Destinations;
				
		char removePiece(Square* srcSquare);
		char placePiece(Square* dstSquare, char piece);		

	public:
		Square* square[8][8];
		static const char* StartposFen;
		unsigned char CASTLE_FLAGS;
		const unsigned char WHITE_KING_MOVED = 0x01;
		const unsigned char WHITE_KING_ROOK_MOVED = 0x02;
		const unsigned char WHITE_QUEEN_ROOK_MOVED = 0x04;
		const unsigned char BLACK_KING_MOVED = 0x08;
		const unsigned char BLACK_KING_ROOK_MOVED = 0x10;
		const unsigned char BLACK_QUEEN_ROOK_MOVED = 0x20;

		List<Square>* whitePieceSquares;
		List<Square>* blackPieceSquares;
		const char whitePiecesStr[7] = "PNBRQK";
		const char blackPiecesStr[7] = "pnbrqk";
				
		Board();
		void clear();
		Color set(const char* fen);	
		Move* buildMove(const char* strLAN);
		Move* buildMove(Square* src, Square* dst, char promotedTo);
		bool executeMove(Move* move, List<Square>* myPieceSquares, List<Square>* yourPieceSquares);
		bool revertMove(Move* move, List<Square>* myPieceSquares, List<Square>* yourPieceSquares);
		Tree* findAvailableMoves(List<Square>* mySquares, const char* yourPiecesStr);
		inline void identifyPieceColor(Move* move);
		void movePiece(Square* srcSquare, Square* dstSquare, List<Square>* myPieceSquares, List<Square>* yourPieceSquares, char promotedTo = NoPiece);
		void undoMovePiece(Square* srcSquare, Square* dstSquare, List<Square>* myPieceSquares, List<Square>* yourPieceSquares, char piece, char capturedPiece = NoPiece);

		void castle(Move* move, List<Square>* myPieceSquares, bool bForward = true);
		void setMoveScore(Move* move);

		Tree* findLegalMoves(List<Square>* myPieceSquares, List<Square>* yourPieceSquares, const char* myPiecesStr, const char* yourPiecesStr, char myKing);
		bool isKingInCheck(Tree* opponentMoves, char myKing);
		~Board();
	};
}