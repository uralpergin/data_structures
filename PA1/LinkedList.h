#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    this -> head = NULL;
    this -> size = 0;
    /* TODO */
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    
    head = NULL;
    if(obj.isEmpty())  removeAllNodes();
    else (*this) = obj;
}

template<class T>
LinkedList<T>::~LinkedList() {
    removeAllNodes();
    head = NULL;
    size = 0;
}

template<class T>
int LinkedList<T>::getSize() const {
    return size;
    /* TODO */
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    if(head == NULL) return 1;
    else return 0;
    /* TODO */
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    Node<T> *curr = head;
    if(head == NULL) return 0;
    else{
        while(curr -> next != head){
            if(curr -> next == node -> next || curr -> prev == node -> prev ||  curr -> data == node -> data) return 1;
            else curr = curr -> next;
        }
        if(curr -> next == node -> next || curr -> prev == node -> prev || curr -> data == node -> data ) return 1;
        else return 0;
    }
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    if(head == NULL) return NULL;
    else return head;
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    Node<T> *curr = head;
    if(head == NULL) return NULL;
    else{
        while(curr -> next != head) curr = curr -> next;
        return curr;
    }
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    Node<T> *curr = head;
    
    if(head == NULL) return NULL;
    else{
        while(curr -> next != head){
            if(curr -> data == data){
                return curr;
            }    
            else curr = curr -> next;
        }
        if(curr -> data == data) return curr;
        else return NULL;
    }
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    Node<T> *curr = head;
    int i = 0;
    for(i=0 ; curr -> next != head; i++){
        if(i == index) return curr;
        else curr = curr -> next;
    }
    if(i == index) return curr;
    else return NULL;
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    Node<T> *newNode = new Node<T>(data);
    Node<T> *curr = head;

    if(head == NULL){
        head = newNode;
        newNode -> next = head;
        newNode -> prev = head;
    }
    else{
        newNode -> data = data;
        newNode -> next = curr;
        newNode -> prev = head -> prev;

        head -> prev -> next = newNode;
        head = newNode;
        newNode -> next -> prev = newNode;    
    }
    /* TODO */
    size+=1;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    Node<T> *newNode = new Node<T>(data);

    if(head == NULL){
        head = newNode;
        newNode -> next = head;
        newNode -> prev = head;
    }
    else{
        newNode -> data = data;
        newNode -> next = head;
        newNode -> prev = head -> prev;

        head -> prev -> next = newNode;
        head -> prev = newNode;   
    }
    /* TODO */
    size+=1;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    Node<T> *newNode = new Node<T>(data);
    Node<T> *curr = head;
    int done =0;
    newNode -> data = data;
    
     
    if(head -> next == node -> next || head -> prev == node -> prev ||  head -> data == node -> data){
        size+=1;
        done =1;
        newNode -> next = head -> next;
        newNode -> prev = head;

        head -> next = newNode;
        newNode -> next -> prev = newNode;
    }
    else{
        while(curr -> next != head){
            if(curr -> next == node -> next || curr -> prev == node -> prev ||  curr -> data == node -> data){
                size++;
                done =1;
                newNode -> next = curr -> next;
                newNode -> prev = curr;

                curr -> next = newNode;
                newNode -> next -> prev = newNode;
                curr = curr -> next;
            }
            else curr = curr -> next;
        }
        if(curr -> next == node -> next || curr -> prev == node -> prev ||  node -> data == curr -> data){
            size++;
            done = 1;
            newNode -> next = curr -> next;
            newNode -> prev = curr;

            curr -> next = newNode;
            newNode -> next -> prev = newNode;
            head = newNode -> next;
        }
        else ;
    }
    if(done == 0) delete newNode;
    else ;
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    Node<T> *curr = head;
    int i = 2;

    if(k >= 2 || k <= size){
        while(curr -> next != head){
            if(i % k == 0){
                insertAfterNode(data,curr);
                curr = curr -> next;
                i = 1;
            }
            else{
                curr = curr -> next;
                i++;
            }
        }
        if(i % k == 0){
            insertAfterNode(data,curr);
        }
        else ;
    }
    
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    Node<T> *curr = head;
    if(head == NULL) ;
    else{
        if(head == node){
            if(head -> next == head){
                this -> head = NULL;
                delete node;
                size = 0;
            }
            else{
                head -> next -> prev = head -> prev;
                head -> prev -> next = head -> next;
                head = head -> next;
        
                delete node;
                size--;
            }
        }
        else{
            curr = curr -> next;
            while(curr != head){
                if(curr -> next == node -> next || curr -> prev == node -> prev ||  curr -> data == node -> data){
                    curr -> next -> prev = curr -> prev;
                    curr -> prev -> next = curr -> next;

                    delete node;
                    size--;
                    break;
                }
                else{
                    curr = curr -> next;
                }
            }    
        }
    }
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    Node<T> *curr = head;
    if(head == NULL) ;
    else{
        if(head -> data == data){
            if(head -> next == head){
                delete head;
                this -> head = NULL;
                size = 0;
            }
            else{
                head -> next -> prev = head -> prev;
                head -> prev -> next = head -> next;
                head = head -> next;
                delete curr;
                size--;
            }
        }
        else{
            curr = curr -> next;
            Node<T> *tmp;
            while(curr != head){
                tmp = curr;
                if(curr -> data == data){
                    curr -> next -> prev = curr -> prev;
                    curr -> prev -> next = curr -> next;
            
                    curr = curr -> next;
                    delete tmp;
                    size--;
            
                }
                else{
                    curr = curr -> next;
                }
            }
        }
    }    
    /* TODO */
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    if(head == NULL) ;
    else{
        while(head){
            removeNode(head);
        }
        head = NULL;
        size = 0;
    }
    /* TODO */
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    Node<T> *curr = head;
    Node<T> *tmp;
    int i = 2;
    curr = curr -> next;
    if(k < 2 && k > size) ;
    else{
        while(curr != head){
            if( i == k ){
                tmp = curr -> next;
                removeNode(curr);
                curr = tmp;
                i = 1;
            }
            else{
                curr = curr -> next;
                i++;
            }
        }
    }
    /* TODO */
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    Node<T> *curr = head;
    Node<T> *tmp1;
    Node<T> *tmp2;
    Node<T> *tmp_nxt;
    Node<T> *tmp_prv;
    if(node1 -> next == node2){
        node1 -> prev -> next = node2;
        node2 -> next -> prev = node1;
        
        tmp_nxt = node2 -> next;
        tmp_prv = node1 -> prev;
        node1 -> next = tmp_nxt;
        node1 -> prev = node2;
        node2 -> next = node1;
        node2 -> prev = tmp_prv;

        if(head == node1) head = head -> prev;
        else if(head == node2) head = head -> next;
        else;   
    }
    else if(node2 -> next == node1){
        node2 -> prev -> next = node1;
        node1 -> next -> prev = node2;
        
        tmp_nxt = node1 -> next;
        tmp_prv = node2 -> prev;
        node2 -> next = tmp_nxt;
        node2 -> prev = node1;
        node1 -> next = node2;
        node1 -> prev = tmp_prv;

        if(head == node2) head = head ->prev;
        else if(head == node1) head = head -> next;
        else ; 
    }
    else{
        curr = curr -> next;
        while(curr != head){
            if(curr -> next == node1 -> next || curr -> prev == node1 -> prev || curr -> data == node1 -> data){
                tmp1 = curr;
                curr = curr -> next;
            }
            else if(curr -> next == node2 -> next || curr -> prev == node2 -> prev || curr -> data == node2 -> data){
                tmp2 = curr;
                curr = curr ->next;
            }
            else curr = curr -> next;
        }    
        tmp1 -> prev -> next = tmp2;
        tmp1 -> next -> prev = tmp2;
        tmp2 -> prev -> next = tmp1;
        tmp2 -> next -> prev = tmp1;

        tmp_nxt = tmp1 -> next;
        tmp_prv = tmp1 -> prev;
    
        tmp1 -> next = tmp2 -> next;
        tmp1 -> prev = tmp2 -> prev;

        tmp2 -> next = tmp_nxt;
        tmp2 -> prev = tmp_prv;
    }    
    /* TODO */
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    int i;
    Node<T> *curr1;
    Node<T> *curr2;
   
    for(i = 0; i <= size-1; i++){
        curr1 = getNodeAtIndex(i);
        curr2 = getNodeAtIndex((i*i+seed)%size);
        swap(curr1,curr2);
    }
    /* TODO */
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    removeAllNodes();
    head = NULL;
    
    if(rhs.isEmpty()){
        return (*this);
    }
    else{
        Node<T> *curr = rhs.getFirstNode();
        insertAtTheFront(curr -> data);

        curr = curr -> next;
        while(curr != rhs.getFirstNode()){
            insertAtTheEnd(curr -> data);    
            curr = curr -> next;
        }
        this -> size = rhs.getSize();
        return (*this);
    }
    /* TODO */
}

#endif //LINKEDLIST_H
