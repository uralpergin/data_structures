#include <iostream>

#include "BST.h"

int main() {
    BST<int> tree;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    if(tree.contains(tree.search(6))) std::cout << "true" << std::endl;
    else std::cout << "false" << std::endl;

    //tree.remove(4);
    //tree.removeAllNodes();
    tree.print(inorder);

    std::cout<< tree.getSuccessor(tree.search(6),inorder)->data<<std::endl;
    return 0;
}
