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

        TreeNode();
        TreeNode(Move* move);
        void setChildren(Tree* _children);
        ~TreeNode();
    };

    struct Tree {

        TreeNode* tree;
        TreeNode* last;
        TreeNode* parent;
        unsigned length;
        char maxScore;

        static const char LeastScore;

        Tree();
        void add(Move* move);
        TreeNode* remove(TreeNode* p);
        TreeNode* getAt(int i);
        ~Tree();
    };    	
}

