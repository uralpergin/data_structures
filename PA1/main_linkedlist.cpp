#include <iostream>

#include "LinkedList.h"

int main() {
    
    LinkedList<int> llist;
    //LinkedList<int> nod;
    Node<int> *tmp = new Node<int>(12);
    Node<int> *tmpn = new Node<int>(12);
    Node<int> *tmpp = new Node<int>(12);
    tmp -> next = tmpn;
    tmp -> prev = tmpp;
    llist.print();

    llist.insertAtTheEnd(3);
    llist.insertAtTheFront(2);
    llist.insertAfterNode(1, llist.getNode(2));
    llist.insertAtTheEnd(5);
    llist.insertAtTheFront(4);
    llist.insertAfterNode(7, llist.getNode(1));
    //llist.insertAsEveryKthNode(8,3);
    //llist.removeAllNodes();
    
    llist.print();
    /*
    std::cout << "size  = " << llist.getSize() << std::endl;
    
    //std::cout << "second =" << llist.getNode(5)->data << std::endl;

    //std::cout << "first =" << llist.getFirstNode() -> data << std::endl;

    //std::cout << "last  = " << llist.getLastNode() -> data<< std::endl;

    //std::cout << "node at index 0  = " << llist.getNodeAtIndex(0) -> data<< std::endl;

    //std::cout << "node at index 2  = " << llist.getNodeAtIndex(2) -> data<< std::endl;

    if(llist.contains(tmp) == 1) std::cout << " true" << std::endl;
    else std::cout << "false " << std::endl;

    //llist.removeAllNodes();
    //llist.removeNode(llist.getNode(4));
    //llist.removeNode(llist.getNode(2));
    //llist.removeNode(llist.getNode(1));
    //llist.removeNode(llist.getNode(7));
    //llist.removeNode(llist.getNode(3));
    //llist.removeNode(llist.getNode(5));
    //llist.removeNode(llist.getNode(4));
    //llist.swap(llist.getNode(4),llist.getNode(2));
    //llist.removeEveryKthNode(2);
    //llist.shuffle(8);
    //std::cout << "node at index 0  = " << llist.getNode(5) -> data<< std::endl;
    std::cout << " " << std::endl;
    //std::cout << llist.getFirstNode() -> next << std::endl;
    //std::cout << llist.getFirstNode() -> prev << std::endl;
    //std::cout << llist.getFirstNode() << std::endl;
    
    //nod = llist;

    
    //nod.print();
    */
    std::cout << " " << std::endl;
    llist.swap(llist.getNode(4),llist.getNode(2));
    llist.print();
    return 0;
}