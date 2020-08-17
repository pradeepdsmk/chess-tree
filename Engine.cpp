#include "Engine.h"
#include <iostream>
#include <chrono>

namespace chess {

	Engine::Engine() {
		board = new Board();
		playerWhite = new Player(board, White);
		playerBlack = new Player(board, Black);
		isForceMode = false;
		maxTreeDepth = 4;

		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		generator = std::mt19937(rd()); //Standard mersenne_twister_engine seeded with rd()
		distribution = std::uniform_int_distribution<int>(1, 10000);
	}

	Engine::~Engine() {
		delete playerWhite;
		playerWhite = nullptr;

		delete playerBlack;
		playerBlack = nullptr;

		delete board;
		board = nullptr;
	}
	
	void Engine::newboard() {
		board->clear();
		board->set(Board::StartposFen);
		colorOnMove = White;
		playerEngine = playerBlack;
		playerUser = playerWhite;
		isForceMode = false;
	}

	void Engine::force() {
		isForceMode = true;
	}

	void Engine::go(std::string& output) {
		if (colorOnMove == White) {
			playerEngine = playerWhite;
			playerUser = playerBlack;
		}
		else {
			playerEngine = playerBlack;
			playerUser = playerWhite;
		}

		isForceMode = false;

		enginemove(output);
	}

	void Engine::usermove(const std::string& input, std::string& output) {
		Move* move = board->buildMove(input.c_str());

		bool executeSuccess = playerUser->executeMove(move);
		//delete move;

		if (!executeSuccess) {
			output = "Illegal move";		
			return;
		}

		colorOnMove = !colorOnMove;

		if (isForceMode) {
			output = "";			
			return;
		}

		enginemove(output);
	}

	void Engine::enginemove(std::string& output) {
		if (((colorOnMove == White) && (playerEngine == playerBlack))
			|| ((colorOnMove == Black) && (playerEngine == playerWhite ))) {
			output = "";
			return;
		}

		//Tree* legalMoves = playerEngine->legalMoves();		
		Tree* legalMoves = moveTree();

		short maxDamage = -200, damage;		
		for (TreeNode* p1 = legalMoves->tree->right;p1; p1 = p1->right) {
			damage = p1->move->score - p1->children->maxScore;
			if (damage > maxDamage) {
				maxDamage = damage;
			}
		}

		for (TreeNode* p2 = legalMoves->tree->right;p2; p2 = p2->right) {
			damage = p2->move->score - p2->children->maxScore;
			if (damage < maxDamage) {
				p2 = legalMoves->remove(p2);
			}
		}
		if (legalMoves->length > 0) {
			int movePos = distribution(generator) % legalMoves->length;
			Move* replyMove = legalMoves->getAt(movePos)->move;

			playerEngine->executeMove(replyMove);
			output = "move " + replyMove->toLAN();
			colorOnMove = !colorOnMove;
		}
		else {	
			if (playerEngine->isKingInCheck()) {
				if (playerEngine == playerWhite) {
					output = "0-1 { Checkmate }";
				}
				else {
					output = "1-0 { Checkmate }";
				}
			}
			else {
				output = "1/2-1/2 { Stalemate }";
			}			
		}

		delete legalMoves;
	}

	Tree* Engine::moveTree() {
		Player* player = playerEngine;
		Player* opponent = playerUser;
		Tree* availableMoves = player->availableMoves();
		Tree* moveTree = availableMoves;
		unsigned depth = 1;
		unsigned executedMoveCount = 0; // just for tracking

		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

		while (1) {
			// if there is no another move, go up
			if (availableMoves->current->right == nullptr) {
				// if there is no up, then we are done
				if (availableMoves->parent == nullptr) {
					break;
				}

				availableMoves = availableMoves->parent->thisTree;
				swapPlayers(&player, &opponent);
				depth--;

				// revert move in the up, if move is valid (first node in tree is dummy, remmeber?)
				if (availableMoves->current->move != nullptr) {
					player->revertMove(availableMoves->current->move);
				}			

				continue;
			}			

			// go to next move and execute			
			availableMoves->current = availableMoves->current->right;
			Move* move = availableMoves->current->move;
			player->executeMove(move);
			executedMoveCount++;

			// find opponent moves and add them as children
			Tree* opponentMoves = opponent->availableMoves();
			availableMoves->current->setChildren(opponentMoves);

			// if this is not a legal move, revert this move, remove it
			if (player->isKingInCheck(opponentMoves)) {
				player->revertMove(move);
				//delete opponentMoves; // remove will delete entire tree
				availableMoves->current = availableMoves->remove(availableMoves->current);
				continue;
			}			
			
			// if we can not go deep, revert move
			if (depth == maxTreeDepth - 1) {
				player->revertMove(move);
				continue;
			}			

			// go deep, 
			swapPlayers(&player, &opponent);
			//availableMoves = availableMoves->current->children; // faster? use opponentMoves
			availableMoves = opponentMoves;
			depth++;
		}	

		auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();
		std::cout << executedMoveCount << " moves executed in " << timeDiff << " milliseconds" << std::endl;

		return moveTree;
	}

	void Engine::swapPlayers(Player** player1, Player** player2) {
		Player* temp = *player1;
		*player1 = *player2;
		*player2 = temp;
	}
}