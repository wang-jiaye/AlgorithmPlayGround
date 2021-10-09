#include<iostream>

#include "RBTree.h"

RBTree::RBTree() {
    TNULL = new RBNode;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

void RBTree::insert(int key) {
    NodePtr node = new RBNode;
    node->parent = nullptr;
    node->val = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
    NodePtr x = this->root;
    
    while (x != TNULL) {
        y = x;
        if (node->val < x->val) x = x->left;
        else x = x->right;
    }

    node->parent = y;
    if (!y) root = node;
    else if (node->val < y->val) y->left = node;
    else y->right = node;

    if (!node->parent) {
        node->color = 0;
        return;
    }
    
    if (!node->parent->parent)
        return;
    insertFix(node);
}

void RBTree::deleteNode(int key) {
    NodePtr z = root, x, y;
    while (z != TNULL) {
        if (z->val == key) break;
        if (z->val <= key) z = z->right;
        else z = z->left;
    }
    if (z == TNULL) {
        std::cout << "Key not found in the tree\n";
        return;
    }
    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = treeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) 
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (!y_original_color) 
        deleteFix(x);
}

void RBTree::postOrder() {
    postOrderHelper(this->root);
}

void RBTree::inOrder() {
    inOrderHelper(this->root);
}

void RBTree::preOrder() {
    preOrderHelper(this->root);
}

void RBTree::leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) 
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) 
        this->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else 
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        this->root = y;
    else if (x == x->parent->right) 
        x->parent->right = y;
    else 
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RBTree::insertFix(NodePtr k) {
    NodePtr u;
    while (k->parent->color) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;
            if (u->color) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent; 
                    leftRotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) break;
    }
    root->color = 0;
}

void RBTree::deleteFix(NodePtr x) {
    NodePtr w;
    while (x != root && !x->color) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color) {
                w->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (!w->left->color && !w->right->color) {
                w->color = 1;
                x = x->parent;
            } else {
                if (!w->right->color) {
                    w->left->color = 0;
                    w->color = 1;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->right->color = 0;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            w = x->parent->left;
            if (w->color) {
                w->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                w = x->parent->left;
            } 
            if (!w->right->color) {
                w->color = 1;
                x = x->parent;
            } else {
                if (!w->left->color) {
                    w->right->color = 0;
                    w->color = 1;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->left->color = 0;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 0;
}

void RBTree::transplant(NodePtr u, NodePtr v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

NodePtr RBTree::treeMinimum(NodePtr node) {
    while (node->left != TNULL) 
        node = node->left;
    return node;
}


void RBTree::postOrderHelper(NodePtr node) {
    if (!node) return;
    postOrderHelper(node->left);
    postOrderHelper(node->right);
    std::cout << node->val << " ";
}

void RBTree::inOrderHelper(NodePtr node) {
    if (!node) return;
    inOrderHelper(node->left);
    std::cout << node->val << " ";
    inOrderHelper(node->right);
}

void RBTree::preOrderHelper(NodePtr node) {
    if (!node) return;
    std::cout << node->val << " ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
}
