#include "RBTree.h"
#include <iostream>

using namespace std;

int main() {
    RBTree tree;
    tree.insert(60);
    tree.insert(17);
    tree.insert(12);
    tree.insert(23);
    tree.insert(9);
    tree.insert(14);
    tree.insert(19);
    tree.insert(72);
    tree.insert(54);
    tree.insert(76);
    tree.insert(67);


    tree.postOrder();
    cout << endl;
    tree.inOrder();
    cout << endl;
    tree.deleteNode(23);
    tree.postOrder();
    cout << endl;
    tree.inOrder();
    cout << endl;
}
