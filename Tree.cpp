#include "Tree.h"

namespace chess {

    TreeNode::TreeNode() {
        move = nullptr;
        left = nullptr;
        right = nullptr;
        thisTree = nullptr; // will be set by TreeNode
        children = nullptr;
        cumulativeDamage = 0;
        maxCumulativeDamage = -128;
        minCumulativeDamage = 127;
    }
    TreeNode::TreeNode(Move* _move) : TreeNode() {
        move = _move;
    }

    void TreeNode::setChildren(Tree* _children) {
        children = _children;
        children->parent = this;
        if (this->thisTree->rootParent == nullptr) {
            children->rootParent = this;
        }
        else {
            children->rootParent = this->thisTree->rootParent;
        }        
    }

    TreeNode::~TreeNode() {
        if (move) {
            delete move;
            move = nullptr;
        }
        if (children) {
            delete children;
            children = nullptr;
        }
    }


    /////////////////////////////

    Tree::Tree() {
        tree = new TreeNode();
        last = tree;
        parent = nullptr;
        rootParent = nullptr;
        length = 0;
        maxScore = Tree::LeastScore;
        current = tree;
    }

    Tree::~Tree() {
        while (last->left) {
            last = last->left;

            delete last->right;
            last->right = nullptr;
        }

        delete tree;
        tree = nullptr;
        //parent = nullptr;
        //last = nullptr;
        //length = 0;
    }

    void Tree::add(Move* move) {
        TreeNode* treeNode = new TreeNode(move);
        treeNode->thisTree = this;
        treeNode->left = last;
        last->right = treeNode;
        last = treeNode;// move last after setting last right
        ++length;
        if (move->score > maxScore) {
            maxScore = move->score;
        }
    }

    TreeNode* Tree::remove(TreeNode* p) {
        if (p == tree) {
            // do not remove the first node [oh! WTH]
            return p;
        }
        TreeNode* pprev = p->left;
        p->left->right = p->right;
        if (p->right) {
            p->right->left = p->left;
        }
        else {
            // this is last node
            last = last->left;
        }
        delete p;
        p = nullptr;
        --length;


        // update maxScore
        if (length == 0) {
            maxScore = Tree::LeastScore;
        }
        else {
            TreeNode* p = tree->right;
            char score;
            while (p) {
                score = p->move->score;
                if (score > maxScore) {
                    maxScore = score;
                }
                p = p->right;
            }
        }

        return pprev;
    }

    TreeNode* Tree::getAt(int i) {
        // i is 0 based index
        TreeNode* p = tree->right;
        while (i--) {
            p = p->right;
        }
        return p;
    }

    void Tree::updateDamage(unsigned level) {        
        char cumulativeDamage = (parent ? parent->cumulativeDamage : 0) + current->move->score * ((level % 2) ? 1 : -1);
        current->cumulativeDamage = cumulativeDamage;
        TreeNode* _rootParent = rootParent ? rootParent : current;
        if (cumulativeDamage > _rootParent->maxCumulativeDamage) {
            _rootParent->maxCumulativeDamage = cumulativeDamage;
        }
        if (cumulativeDamage < _rootParent->minCumulativeDamage) {
            _rootParent->minCumulativeDamage = cumulativeDamage;
        }
    }
}
