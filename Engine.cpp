#include "Engine.h"
#include <iostream>
#include <chrono>
#include <sstream>

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

	void Engine::setboard(const std::string& input, std::string& output) {
		std::string fen = input.substr(9);
		board->clear();
		board->set(fen.c_str());
	}

	void Engine::force() {
		isForceMode = true;
	}

	void Engine::analyze() {
		isAnalyzeMode = true;
	}

	void Engine::exit() {
		isAnalyzeMode = false;
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
		
		if (isForceMode) {
			if (colorOnMove == White) {
				playerEngine = playerBlack;
				playerUser = playerWhite;				
			}
			else {
				playerEngine = playerWhite;
				playerUser = playerBlack;
			}
		}

		Move* move = board->buildMove(input.c_str());
		bool executeSuccess = playerUser->executeMove(move);
		delete move;

		if (!executeSuccess) {
			output = "Illegal move";		
			return;
		}

		colorOnMove = !colorOnMove;

		if (isForceMode) {
			if (isAnalyzeMode) {
				enginemove(output);
			}
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

		//thinkingOutput(legalMoves);
		
		//watchMoveScores(legalMoves);

		//short maxDamage = -200, damage;		
		//for (TreeNode* p1 = legalMoves->tree->right;p1; p1 = p1->right) {
		//	//damage = p1->move->score - p1->children->maxScore;
		//	damage = p1->maxCumulativeDamage;
		//	if (damage > maxDamage) {
		//		maxDamage = damage;
		//	}
		//}

		//for (TreeNode* p2 = legalMoves->tree->right;p2; p2 = p2->right) {
		//	//damage = p2->move->score - p2->children->maxScore;
		//	damage = p2->maxCumulativeDamage;
		//	if (damage < maxDamage) {
		//		p2 = legalMoves->remove(p2);
		//	}
		//}

		
		int maxMinDamage = -128;
		/*const int PBEST_MAX = 255;
		const int NBEST_MIN = -256;
		int minDamage, pBest = PBEST_MAX, nBest = NBEST_MIN;
		for (TreeNode* p1 = legalMoves->tree->right;p1; p1 = p1->right) {
			minDamage = p1->minCumulativeDamage;
			if (minDamage >= 0) {
				if (minDamage < pBest) {
					pBest = minDamage;
				}
			}
			else {
				if (minDamage > nBest) {
					nBest = minDamage;					
				}
			}
		}
		if (pBest < PBEST_MAX) {
			maxMinDamage = pBest;
		}
		else {
			maxMinDamage = nBest;
		}	*/	
		for (TreeNode* p1 = legalMoves->tree->right;p1; p1 = p1->right) {
			if (maxMinDamage < p1->minCumulativeDamage) {
				maxMinDamage = p1->minCumulativeDamage;
			}
		}
		for (TreeNode* p2 = legalMoves->tree->right;p2; p2 = p2->right) {
			if (p2->minCumulativeDamage != maxMinDamage) {
				p2 = legalMoves->remove(p2);
			}
		}

		//thinkingOutput(legalMoves);

		int maxDamage = -128;
		for (TreeNode* p3 = legalMoves->tree->right;p3; p3 = p3->right) {
			if (p3->maxCumulativeDamage > maxDamage) {
				maxDamage = p3->maxCumulativeDamage;
			}
		}

		for (TreeNode* p4 = legalMoves->tree->right;p4; p4 = p4->right) {
			if (p4->maxCumulativeDamage != maxDamage) {
				p4 = legalMoves->remove(p4);
			}
		}

		thinkingOutput(legalMoves);

		if (!isForceMode) {
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
		}

		delete legalMoves;
	}

	Tree* Engine::moveTree() {
		Player* player = playerEngine;
		Player* opponent = playerUser;
		Tree* availableMoves = player->availableMoves();
		Tree* moveTree = availableMoves;
		unsigned depth = 1;

		executedMoveCount = 0; // just for tracking
		treeBuildTime = 0;
		const char SCORE_CHECKMATE = 105;

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
				if (availableMoves->current->children->length == 0) {
					availableMoves->current->move->score = SCORE_CHECKMATE;
					availableMoves->updateDamage(depth);
				}
				//if (availableMoves->current->move == nullptr) {
				//	continue;
				//}
				//if (availableMoves->current->move != nullptr) {
					player->revertMove(availableMoves->current->move);
				//}		
										
				delete availableMoves->current->children;
				availableMoves->current->children = nullptr;
					

				continue;
			}			

			// go to next move and execute						
			availableMoves->current = availableMoves->current->right;			
			Move* move = availableMoves->current->move;
			player->executeMove(move);
			executedMoveCount++;

			// find opponent moves and add them as children
			Tree* opponentMoves = opponent->availableMoves();
			// if this is not a legal move, revert this move, remove it
			if (player->isKingInCheck(opponentMoves)) {
				player->revertMove(move);
				delete opponentMoves;
				availableMoves->current = availableMoves->remove(availableMoves->current);
				continue;
			}		

			// set children only if current move is valid
			availableMoves->current->setChildren(opponentMoves);

			// update damage;
			availableMoves->updateDamage(depth);			
			
			// if we can not go deep, revert move
			if (depth == maxTreeDepth) {
				player->revertMove(move);

				continue;
			}			

			// go deep, 
			swapPlayers(&player, &opponent);
			//availableMoves = availableMoves->current->children; // faster? use opponentMoves
			availableMoves = opponentMoves;
			depth++;
		}	

		treeBuildTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - t1).count();
		//std::cout << executedMoveCount << " moves executed in " << timeDiff << " milliseconds" << std::endl;

		return moveTree;
	}

	void Engine::swapPlayers(Player** player1, Player** player2) {
		Player* temp = *player1;
		*player1 = *player2;
		*player2 = temp;
	}

	int Engine::watchMoveScores(Tree* legalMoves) {
		std::vector<std::string> movesScoreList;
		for (TreeNode* p0 = legalMoves->tree->right;p0; p0 = p0->right) {
			std::stringstream ss;
			ss << p0->move->toSAN() << " (" << (int)p0->minCumulativeDamage << ", " << (int)p0->maxCumulativeDamage << ")";
			movesScoreList.push_back(ss.str());
		}
		return 0;
	}

	int Engine::thinkingOutput(Tree* legalMoves) {
		int ply = maxTreeDepth;
		double score = legalMoves->tree->right->minCumulativeDamage * 100.0;
		long long time = treeBuildTime;
		long long nodes = executedMoveCount;
		std::string pv;
		//std::cout << ply << " " << score << " " << time << " " << nodes << " " << "New Line" << std::endl;
		for (TreeNode* p0 = legalMoves->tree->right;p0; p0 = p0->right) {
			std::stringstream ss;
			ss << p0->move->toSAN() << " (" << (int)p0->minCumulativeDamage << ", " << (int)p0->maxCumulativeDamage << ")";
			pv = ((colorOnMove == White) ? "" : "... ") + ss.str();
			std::cout << ply << " " << score << " " << time << " " << nodes << " " << pv << std::endl;
		}
		return 0;
	}
}