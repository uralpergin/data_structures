#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;

    void insert(BSTNode<T> *&p, const T &val){
        if(p == NULL) p = new BSTNode<T>(val,NULL,NULL);
        else if(p -> data > val) insert(p -> left, val);
        else if(p -> data < val) insert(p -> right, val); 
    }

    bool contains(BSTNode<T> *p, BSTNode<T> *node) const {
        if(p == NULL) return false;
        else{
            if(p == node) return true;
            else if(p -> data > node -> data) return contains(p -> left, node);
            else return contains(p -> right, node);
        }
    }

    T getMin(BSTNode<T>* r) {
        if (r->left == NULL) return r->data;
        else return getMin(r->left);
    }
    
    void remove(BSTNode<T> *&p, const T &val){
        if(p == NULL) return;
        else if(p -> data > val) remove(p -> left, val);
        else if(p -> data < val) remove(p -> right, val);
        else{
            if(p -> left != NULL && p -> right != NULL){
                p -> data = getMin(p -> right);
                remove(p -> right, p -> data);    
            }
            else{
                BSTNode<T> *oldnode = p;
                p = (p -> left != NULL)? p -> left : p -> right;
                delete oldnode;
            }
        }
    }

    void removeAllNodes(BSTNode<T> *&p){
        if(p == NULL) return;
        if(p -> right != NULL) removeAllNodes(p -> right);
        if(p -> left != NULL) removeAllNodes(p -> left);
        delete p;
        p = NULL;
    }

    BSTNode<T> *search(BSTNode<T> *p, const T &val) const {
        if(p == NULL) return NULL;
        else{
            if(p -> data == val) return p;
            else if(p -> data > val) return search(p -> left, val);
            else return search(p -> right, val);
        }
    } 

    void make_copy(BSTNode<T> *& r1, BSTNode<T> *r2){
        if(r2 != NULL){
            r1 = new BSTNode<T>(r2 -> data,NULL,NULL);
            make_copy(r1 -> left, r2 -> left);
            make_copy(r1 -> right, r2 -> right);
        }
        else r1 = NULL;
    }
    
private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    root = NULL;
    /* TODO */
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    if(obj.root == NULL) root = NULL;
    else make_copy(root, obj.root);
    /* TODO */
}

template<class T>
BST<T>::~BST() {
    removeAllNodes();
    root = NULL;
    /* TODO */
}
/*
template<class T>
T getMin() {
    if (root == nullptr) return;
    return getMin(root);
}
*/

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    if(root == NULL) return NULL;
    else return root;
    /* TODO */
}

template<class T>
bool BST<T>::isEmpty() const {
    if(root == NULL) return true;
    else return false;
    /* TODO */
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    return contains(root,node);
    /* TODO */
}

template<class T>
void BST<T>::insert(const T &data) {
    insert(root,data);
    /* TODO */
}

template<class T>
void BST<T>::remove(const T &data) {
    remove(root,data);
    /* TODO */
}

template<class T>
void BST<T>::removeAllNodes() {
    if(root == NULL) ;
    else{
        removeAllNodes(root);
        root = NULL;
    }
    /* TODO */
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    if(root == NULL) return NULL;
    else return search(root,data);
    /* TODO */
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {

    if (tp == inorder) {
        /* TODO */
    } else if (tp == preorder) {
        /* TODO */
    } else if (tp == postorder) {
        /* TODO */
    }
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        if(isEmpty()){
            std::cout << "BST_preorder{}" << std::endl;
            return;    
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
        /* TODO */
    } else if (tp == postorder) {
        if(isEmpty()){
            std::cout << "BST_postorder{}" << std::endl;
            return;    
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;    
        /* TODO */
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    if(this != &rhs){
        removeAllNodes();
        make_copy(root, rhs.root);
    }
    return *this;
    /* TODO */
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);

    } else if (tp == preorder) {
        std::cout << "\t" << node->data;

        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);

        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
        /* TODO */
    } else if (tp == postorder) {
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }

        std::cout << "\t" << node->data;
        /* TODO */
    }
}
