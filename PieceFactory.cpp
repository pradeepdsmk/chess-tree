#include "PieceFactory.h"

namespace chess {
	PieceFactory::PieceFactory() {
		pieces = new List<Piece>();
	}

	Piece* PieceFactory::createPiece(Pieces::PieceTypes pt, bool isWhite) {
		Piece* p = new Piece(pt, isWhite);
		pieces->append(p);
		return p;
	}

	void PieceFactory::clear() {
		if (pieces) {
			delete pieces;
			pieces = nullptr;
		}		
	}

	PieceFactory::~PieceFactory() {
		if (pieces) {
			delete pieces;
			pieces = nullptr;
		}		
	}
}