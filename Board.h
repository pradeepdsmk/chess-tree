#pragma once

#include <string>
#include "Square.h"
#include "Move.h"
#include "List.h"
#include "Destinations.h"


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


	class Square;
	class Move;

	class Board {
		
		Square* square[8][8];
		bool colorToPlay;
		
		unsigned char numWhitePieces;
		unsigned char numBlackPieces;
		unsigned char numWhitePawns;
		unsigned char numBlackPawns;
		
		static const char* startposFen;

		List<Square>* whitePieceSquares;
		List<Square>* blackPieceSquares;

		friend class Destinations;

		void clearBoard();
		void parseFen(const char* fen);
		bool executeMove(Move* move);
		Move* findReplyMove();

	public:
		Board();	

		void newboard();
		void setboard(const char* fen);
		void usermove(const std::string& input, std::string& output);

		~Board();
	};
}