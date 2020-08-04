#include "Board.h"
#include "Move.h"
#include "MoveFactory.h"

namespace chess {

	const char* Board::startposFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

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
	}

	void Board::clearBoard() {

		for (size_t row = 0; row < 8; ++row) {
			for (size_t col = 0; col < 8; ++col) {
				square[row][col]->piece = '\0';
			}
		}

		if (whitePieceSquares) {
			delete whitePieceSquares;
		}

		if (blackPieceSquares) {
			delete blackPieceSquares;
		}
	}

	void Board::parseFen(const char* fen) {
		const char* c = fen;
		bool parsingDone = false;

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
	}

	bool Board::executeMove(Move* move) {
		return true;
	}

	Move* Board::findReplyMove() {
		Move* move = MoveFactory::createMove("e5");
		return move;
	}

	Board::~Board() {
		unsigned char row, col;
		for (row = 0; row < 8; ++row) {
			for (col = 0; col < 8; ++col) {
				delete square[row][col];
			}
		}

		clearBoard();
	}

	void Board::newboard() {
		colorToPlay = White;
		setboard(startposFen);
	}

	void Board::setboard(const char* fen) {
		clearBoard();

		whitePieceSquares = new List<Square>();
		blackPieceSquares = new List<Square>();

		parseFen(fen);
	}

	void Board::usermove(const std::string& input, std::string& output)
	{
		Move* move = MoveFactory::createMove(input.c_str());
		if (!move) {
			output = "Illegal move";
			return;
		}

		if (!executeMove(move)) {
			output = "Illegal move";
			return;
		}

		Move* replyMove = findReplyMove();
		executeMove(replyMove);
		output = "move " + replyMove->toString();				
	}
}