#include <iostream>
#include "BTree.h"

int main(){
    BTree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(50);
    tree.insert(60);
    tree.insert(55);

    tree.inOrderTraversal();

    return 0;
}

