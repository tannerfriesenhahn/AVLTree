#include <iostream>
#include "BTree.h"

int main(){
    BTree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(50);
    tree.insert(60);
    tree.insert(55);

    tree.printTree();

    tree.remove(20);

    tree.printTree();


    return 0;
}

