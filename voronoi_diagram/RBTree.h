// Reference: Introduction to Algorithms (CLRS)
#ifndef RBTREE_H_
#define RBTREE_H_


struct RBNode {
    int val;
    int color;
    RBNode *parent;
    RBNode *left;
    RBNode *right;
};

typedef RBNode *NodePtr;

class RBTree {
    public:
        RBTree(); // constructor

        void insert(int key);
        void deleteNode(int key);

        void postOrder();
        void inOrder();
        void preOrder();
        
    private:
        NodePtr root;
        NodePtr TNULL;

        NodePtr treeMinimum(NodePtr node);
        void transplant(NodePtr u, NodePtr v);
        void leftRotate(NodePtr x);
        void rightRotate(NodePtr x);

        void deleteFix(NodePtr k);
        void insertFix(NodePtr k);

        void postOrderHelper(NodePtr node);
        void inOrderHelper(NodePtr node);
        void preOrderHelper(NodePtr node);
};

#endif
