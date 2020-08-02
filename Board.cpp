#include "Board.h"
#include <string.h>
#include "MoveBuilder.h"

namespace chess {

	const char* Board::startposFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

	Board::Board() {
		size_t pieceType, row, col;
		for (row = 0; row < 8; ++row) {
			for (col = 0; col < 8; ++col) {
				square[row][col] = new Square((unsigned char)row, (unsigned char)col);
			}
		}

		for (pieceType = 0; pieceType < 7; ++pieceType) {
			for (row = 0; row < 8; ++row) {
				for (col = 0; col < 8; ++col) {
					movesTable[pieceType][row][col] = new List<Move>();
				}
			}
		}

		buildMovesTable();
	}

	void Board::newBoard() {
		colorToPlay = White;
		setBoard(startposFen);
	}

	void Board::setBoard(const char* fen) {
		clearBoard();

		whitePieces = new List<Piece>();
		blackPieces = new List<Piece>();

		parseFen(fen);
	}

	void Board::clearBoard() {
		if (whitePieces) {
			delete whitePieces;
		}

		if (blackPieces) {
			delete blackPieces;
		}

		pieceFactory.clear();
	}

	Board::~Board() {
		size_t pieceType, row, col;
		for (row = 0; row < 8; ++row) {
			for (col = 0; col < 8; ++col) {
				delete square[row][col];
				square[row][col] = nullptr;
			}
		}

		for (pieceType = 0; pieceType < 7; ++pieceType) {
			for (row = 0; row < 8; ++row) {
				for (col = 0; col < 8; ++col) {
					delete movesTable[pieceType][row][col];
					movesTable[pieceType][row][col] = nullptr;
				}
			}
		}

		clearBoard();
	}

	void Board::buildMovesTable() {
		size_t row, col, pieceTypeVal;

		MoveBuilder mb(this);

		for (pieceTypeVal = 0; pieceTypeVal < 7; pieceTypeVal++) {
			for (row = 0; row < 8; ++row) {
				for (col = 0; col < 8; ++col) {
					Pieces::PieceTypes pieceType = static_cast<Pieces::PieceTypes>(pieceTypeVal);
					mb.init(pieceType, row, col);

					switch (pieceType) {

					case Pieces::PieceTypes::king:
						if (row > 0) mb.to(row - 1, col);
						if ((row > 0) && (col < 7)) mb.to(row - 1, col + 1);
						if ((col < 7)) mb.to(row, col + 1);
						if ((row < 7) && (col < 7)) mb.to(row + 1, col + 1);
						if ((row < 7)) mb.to(row + 1, col);
						if ((row < 7) && (col > 0)) mb.to(row + 1, col - 1);
						if ((col > 0)) mb.to(row, col - 1);
						if ((row > 0) && (col > 0)) mb.to(row - 1, col - 1);
						break;

					case Pieces::PieceTypes::queen:
						mb.ray(-1, 1);
						mb.ray(1, 1);
						mb.ray(1, -1);
						mb.ray(-1, -1);
						mb.ray(0, 1);
						mb.ray(0, -1);
						mb.ray(1, 0);
						mb.ray(-1, 0);
						break;

					case Pieces::PieceTypes::bishop:
						mb.ray(-1, 1);
						mb.ray(1, 1);
						mb.ray(1, -1);
						mb.ray(-1, -1);
						break;

					case Pieces::PieceTypes::knight:
						if ((row > 1) && (col < 7)) mb.to(row - 2, col + 1);
						if ((row > 0) && (col < 6)) mb.to(row - 1, col + 2);
						if ((row < 7) && (col < 6)) mb.to(row + 1, col + 2);
						if ((row < 6) && (col < 7)) mb.to(row + 2, col + 1);
						if ((row < 6) && (col > 1)) mb.to(row + 2, col - 1);
						if ((row < 7) && (col > 2)) mb.to(row + 1, col - 2);
						if ((row > 0) && (col > 1)) mb.to(row - 1, col - 2);
						if ((row > 1) && (col > 0)) mb.to(row - 2, col - 1);
						break;

					case Pieces::PieceTypes::rook:
						mb.ray(0, 1);
						mb.ray(0, -1);
						mb.ray(1, 0);
						mb.ray(-1, 0);
						break;

					case Pieces::PieceTypes::whitePawn:
						if ((row > 0) && (row < 7)) {
							mb.to(row - 1, col);
							if (col > 0) mb.to(row - 1, col - 1);
							if (col < 7) mb.to(row - 1, col + 1);
						}
						if ((row == 6)) mb.to(4, col);
						break;

					case Pieces::PieceTypes::blackPawn:
						if ((row > 0) && (row < 7)) {
							mb.to(row + 1, col);
							if (col > 0) mb.to(row + 1, col - 1);
							if (col < 7) mb.to(row + 1, col + 1);
						}
						if ((row == 1)) mb.to(3, col);
						break;
					}
				}
			}
		}
	}

	void Board::parseFen(const char* fen) {
		const char* c = fen;
		Piece* piece;
		bool parsingDone = false;

		size_t fenLen = strlen(fen), i, row = 0, col = 0;
		for (i = 0;(i < fenLen) && (!parsingDone); ++i) {

			square[row][col]->piece = nullptr;

			switch (*c) {
			case 'r':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::rook, false);
				blackPieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;
			case 'n':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::knight, false);
				blackPieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;
			case 'b':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::bishop, false);
				blackPieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;
			case 'q':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::queen, false);
				blackPieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;
			case 'k':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::king, false);
				blackPieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;
			case 'p':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::blackPawn, false);
				blackPieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;

			case 'R':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::rook, false);
				whitePieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;
			case 'N':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::knight, false);
				whitePieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;
			case 'B':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::bishop, false);
				whitePieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;
			case 'Q':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::queen, false);
				whitePieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;
			case 'K':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::king, false);
				whitePieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;
			case 'P':
				piece = pieceFactory.createPiece(Pieces::PieceTypes::whitePawn, false);
				whitePieces->append(piece);
				square[row][col]->piece = piece;
				piece->square = square[row][col];
				col++;
				break;

			case '/':
				row++;
				col = 0;
				break;

			case '1':
				col += 1;
				break;
			case '2':
				col += 2;
				break;
			case '3':
				col += 3;
				break;
			case '4':
				col += 4;
				break;
			case '5':
				col += 5;
				break;
			case '6':
				col += 6;
				break;
			case '7':
				col += 7;
				break;
			case '8':
				col += 8;
				break;

			case ' ':
				parsingDone = true;
				break;
			}

			c++;
		}
	}
}