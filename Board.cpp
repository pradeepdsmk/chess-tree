#include "Board.h"
#include "Move.h"
//#include "MoveFactory.h"

namespace chess {

	const char* Board::StartposFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

	Board::Board() {
		unsigned char row, col;
		for (row = 0; row < 8; ++row) {
			for (col = 0; col < 8; ++col) {
				square[row][col] = new Square(row, col);
			}
		}

		// don't build destinations until all squares are created
		for (row = 0; row < 8; ++row) {
			for (col = 0; col < 8; ++col) {
				square[row][col]->dst->build(this, row, col);
			}
		}

		whitePieceSquares = new List<Square>();
		blackPieceSquares = new List<Square>();
	}

	Board::~Board() {
		unsigned char row, col;
		for (row = 0; row < 8; ++row) {
			for (col = 0; col < 8; ++col) {
				delete square[row][col];
				square[row][col] = nullptr;
			}
		}

		delete whitePieceSquares;
		whitePieceSquares = nullptr;

		delete blackPieceSquares;
		blackPieceSquares = nullptr;
	}

	void Board::clear() {
		for (unsigned char row = 0; row < 8; ++row) {
			for (unsigned char col = 0; col < 8; ++col) {
				square[row][col]->piece = NoPiece;
			}
		}

		whitePieceSquares->clear();
		blackPieceSquares->clear();
	}

	Color Board::set(const char* fen) {		
		const char* c = fen;
		bool parsingDone = false;
		Color colorToPlay = White;

		size_t fenLen = strlen(fen), i, row = 0, col = 0;
		for (i = 0;(i < fenLen) && (!parsingDone); ++i) {

			switch (*c) {
			case 'r':
			case 'n':
			case 'b':
			case 'q':
			case 'k':
			case 'p':
				blackPieceSquares->append(square[row][col]);
				square[row][col]->piece = *c;
				col++;
				break;

			case 'R':
			case 'N':
			case 'B':
			case 'Q':
			case 'K':
			case 'P':
				whitePieceSquares->append(square[row][col]);
				square[row][col]->piece = *c;
				col++;
				break;

			case '/':
				row++;
				col = 0;
				break;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				col += (1 + (*c - '1'));
				break;

			case ' ':
				parsingDone = true;
				break;
			}

			c++;
		}

		CASTLE_FLAGS = 0x0;

		// to-do: identify color to play from the fen
		return colorToPlay;
	}

	Move* Board::buildMove(const char* strLAN) {
		Move* move = new Move();
		move->fromLAN(strLAN);
		move->piece = square[move->srcRow][move->srcCol]->piece;
		move->capturedPiece = square[move->dstRow][move->dstCol]->piece;
		move->color = identifyPieceColor(move->piece);
		if ((move->promotedTo != NoPiece) && (move->color == White)) {
			move->promotedTo = move->promotedTo - 32;
		}
		return move;
	}

	Move* Board::buildMove(Square* src, Square* dst, char _promotedTo = NoPiece) {
		Move* move = new Move();
		move->srcRow = src->row;
		move->srcCol = src->col;
		move->dstRow = dst->row;
		move->dstCol = dst->col;
		move->piece = src->piece;
		move->capturedPiece = dst->piece;
		move->promotedTo = _promotedTo;
		move->color = identifyPieceColor(move->piece);
		// to-do: castling, en passant ???
		return move;
	}

	Color Board::identifyPieceColor(char piece) {
		return ((piece ^ 'P') & (piece ^ 'N') & (piece ^ 'B') & (piece ^ 'Q') & (piece ^ 'R') & (piece ^ 'K')) ? Black : White;
	}

	char Board::removePiece(Square* srcSquare) {
		char piece = srcSquare->piece;
		srcSquare->piece = NoPiece;		
		return piece;
	}

	char Board::placePiece(Square* dstSquare, char piece) {
		char capturedPiece = dstSquare->piece;
		dstSquare->piece = piece;
		return capturedPiece;
	}


	void Board::castle(Move* move, List<Square>* myPieceSquares, bool bForward) {		
		unsigned char rookRow = move->dstRow; // same as king's
		unsigned char srcRookCol, dstRookCol;
		unsigned char flagsToUpdate = 0x00;
		if (move->isShortCastle) {
			srcRookCol = 7;
			dstRookCol = move->dstCol - 1;
			if (move->dstRow == 0) {
				flagsToUpdate = (BLACK_KING_MOVED | BLACK_KING_ROOK_MOVED);
			}
			else {
				flagsToUpdate = (WHITE_KING_MOVED | WHITE_KING_ROOK_MOVED);
			}
		}
		else {
			srcRookCol = 0;
			dstRookCol = move->dstCol + 1;
			if (move->dstRow == 0) {
				flagsToUpdate = (BLACK_KING_MOVED | BLACK_QUEEN_ROOK_MOVED);
			}
			else {
				flagsToUpdate = (WHITE_KING_MOVED | WHITE_QUEEN_ROOK_MOVED);
			}
		}

		Square* srcSquare = square[move->srcRow][move->srcCol];
		Square* dstSquare = square[move->dstRow][move->dstCol];
		Square* srcRookSquare = square[rookRow][srcRookCol];
		Square* dstRookSquare = square[rookRow][dstRookCol];

		if (bForward) {
			dstSquare->piece = srcSquare->piece;
			dstRookSquare->piece = srcRookSquare->piece;
			CASTLE_FLAGS |= flagsToUpdate;
			myPieceSquares->replace(srcSquare, dstSquare);
			myPieceSquares->replace(srcRookSquare, dstRookSquare);
		}
		else {
			srcSquare->piece = dstSquare->piece;
			srcRookSquare->piece = dstRookSquare->piece;
			CASTLE_FLAGS &= ~flagsToUpdate;
			myPieceSquares->replace(dstSquare, srcSquare);
			myPieceSquares->replace(dstRookSquare, srcRookSquare);
		}
	}


	void Board::movePiece(Square* srcSquare, Square* dstSquare, List<Square>* myPieceSquares, List<Square>* yourPieceSquares, char promotedTo) {
		char capturedPiece = dstSquare->piece;
		if (capturedPiece != NoPiece) {
			yourPieceSquares->remove(dstSquare);
		}

		if (promotedTo != NoPiece) {
			dstSquare->piece = promotedTo;
		}
		else {
			dstSquare->piece = srcSquare->piece;
		}
		srcSquare->piece = NoPiece;

		myPieceSquares->replace(srcSquare, dstSquare);		
	}

	void Board::undoMovePiece(Square* srcSquare, Square* dstSquare, List<Square>* myPieceSquares, List<Square>* yourPieceSquares, char piece, char capturedPiece) {
		if (capturedPiece != NoPiece) {
			dstSquare->piece = capturedPiece;
			yourPieceSquares->append(dstSquare);
		}
		else {
			dstSquare->piece = NoPiece;
		}
		
		srcSquare->piece = piece;
		myPieceSquares->replace(dstSquare, srcSquare);
	}

	bool Board::executeMove(Move* move, List<Square>* myPieceSquares, List<Square>* yourPieceSquares) {		
		if (move->isShortCastle || move->isLongCastle) {
			castle(move, myPieceSquares);
		}
		else {
			movePiece(square[move->srcRow][move->srcCol], square[move->dstRow][move->dstCol], myPieceSquares, yourPieceSquares, move->promotedTo);
		}

		return true;
	}

	bool Board::revertMove(Move* move, List<Square>* myPieceSquares, List<Square>* yourPieceSquares) {						
		if (move->isShortCastle || move->isLongCastle) {
			castle(move, myPieceSquares, false);
		}
		else {
			undoMovePiece(square[move->srcRow][move->srcCol], square[move->dstRow][move->dstCol], myPieceSquares, yourPieceSquares, move->piece, move->capturedPiece);
		}

		return true;
	}

	Tree* Board::findAvailableMoves(List<Square>* myPieceSquares, const char* yourPiecesStr) {
		
		Tree* availableMoves = new Tree();

		for (auto srcNode = myPieceSquares->nodes; srcNode; srcNode = srcNode->next) {
			Square* srcSquare = srcNode->item;

			switch (srcSquare->piece) {
			case 'p':
				// to-do: en passant, piece promotion not implemented
				for (auto dstNode = srcSquare->dst->blackPawn->nodes; dstNode; dstNode = dstNode->next) {
					Square* dstSquare = dstNode->item;
					if (dstSquare->piece == NoPiece) {
						availableMoves->add(buildMove(srcSquare, dstSquare));
					}
					else {
						break;
					}
				}
				for (auto dstNode = srcSquare->dst->blackPawnAttack->nodes; dstNode; dstNode = dstNode->next) {
					Square* dstSquare = dstNode->item;
					if (strchr(yourPiecesStr, dstSquare->piece)) {
						availableMoves->add(buildMove(srcSquare, dstSquare));
					}
				}
				break;
			case 'P':
				// to-do: en passant, piece promotion not implemented
				for (auto dstNode = srcSquare->dst->whitePawn->nodes; dstNode; dstNode = dstNode->next) {
					Square* dstSquare = dstNode->item;
					if (dstSquare->piece == NoPiece) {
						availableMoves->add(buildMove(srcSquare, dstSquare));
					}
					else {
						break;
					}
				}
				for (auto dstNode = srcSquare->dst->whitePawnAttack->nodes; dstNode; dstNode = dstNode->next) {
					Square* dstSquare = dstNode->item;
					if (strchr(yourPiecesStr, dstSquare->piece)) {
						availableMoves->add(buildMove(srcSquare, dstSquare));
					}
				}
				break;
			case 'r':
			case 'R':
				for (auto rayList = srcSquare->dst->sideRays->nodes; rayList; rayList = rayList->next) {
					for (auto dstNode = rayList->item->nodes; dstNode; dstNode = dstNode->next) {
						Square* dstSquare = dstNode->item;
						if (dstSquare->piece == NoPiece) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
						}
						else if (strchr(yourPiecesStr, dstSquare->piece)) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
							break;
						}
						else {
							break;
						}
					}
				}
				break;
			case 'n':
			case 'N':
				for (auto dstNode = srcSquare->dst->knight->nodes; dstNode; dstNode = dstNode->next) {
					Square* dstSquare = dstNode->item;
					if (dstSquare->piece == NoPiece) {
						availableMoves->add(buildMove(srcSquare, dstSquare));
					}
					else if (strchr(yourPiecesStr, dstSquare->piece)) {
						availableMoves->add(buildMove(srcSquare, dstSquare));
					}
				}
				break;
			case 'b':
			case 'B':
				for (auto rayList = srcSquare->dst->diagRays->nodes; rayList; rayList = rayList->next) {
					for (auto dstNode = rayList->item->nodes; dstNode; dstNode = dstNode->next) {
						Square* dstSquare = dstNode->item;
						if (dstSquare->piece == NoPiece) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
						}
						else if (strchr(yourPiecesStr, dstSquare->piece)) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
							break;
						}
						else {
							break;
						}
					}
				}
				break;
			case 'q':
			case 'Q':
				for (auto rayList = srcSquare->dst->sideRays->nodes; rayList; rayList = rayList->next) {
					for (auto dstNode = rayList->item->nodes; dstNode; dstNode = dstNode->next) {
						Square* dstSquare = dstNode->item;
						if (dstSquare->piece == NoPiece) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
						}
						else if (strchr(yourPiecesStr, dstSquare->piece)) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
							break;
						}
						else {
							break;
						}
					}
				}
				for (auto rayList = srcSquare->dst->diagRays->nodes; rayList; rayList = rayList->next) {
					for (auto dstNode = rayList->item->nodes; dstNode; dstNode = dstNode->next) {
						Square* dstSquare = dstNode->item;
						if (dstSquare->piece == NoPiece) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
						}
						else if (strchr(yourPiecesStr, dstSquare->piece)) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
							break;
						}
						else {
							break;
						}
					}
				}
				break;
			case 'k':
			case 'K':
				// to-do: castling not implemented
				for (auto rayList = srcSquare->dst->sideRays->nodes; rayList; rayList = rayList->next) {
					if (auto dstNode = rayList->item->nodes) {
						Square* dstSquare = dstNode->item;
						if (dstSquare->piece == NoPiece) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
						}
						else if (strchr(yourPiecesStr, dstSquare->piece)) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
						}
					}
				}
				for (auto rayList = srcSquare->dst->diagRays->nodes; rayList; rayList = rayList->next) {
					if (auto dstNode = rayList->item->nodes) {
						Square* dstSquare = dstNode->item;
						if (dstSquare->piece == NoPiece) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
						}
						else if (strchr(yourPiecesStr, dstSquare->piece)) {
							availableMoves->add(buildMove(srcSquare, dstSquare));
						}
					}
				}
				break;
			}
		}

		return availableMoves;
	}
}