#pragma once
#include "Move.h"

namespace chess {
	
    struct Tree;
    class Move;
    class Square;

    struct TreeNode {

        Move* move;

        TreeNode* left;
        TreeNode* right;

        Tree* thisTree;
        Tree* children;
        char cumulativeDamage;
        char maxCumulativeDamage;
        char minCumulativeDamage;

        TreeNode();
        TreeNode(Move* move);
        void setChildren(Tree* _children);
        ~TreeNode();
    };

    struct Tree {

        TreeNode* tree;
        TreeNode* last;
        TreeNode* parent;
        TreeNode* rootParent;
        unsigned length;
        char maxScore;

        TreeNode* current;

        static const char LeastScore = -104;

        Tree();
        void add(Move* move);
        TreeNode* remove(TreeNode* p);
        TreeNode* getAt(int i);
        void updateDamage(unsigned level);
        ~Tree();
    };    	
}

