/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include <cmath>
 #include <algorithm>
 #include <iostream>

 using namespace std;

template <class K, class V>
int AVLTree<K, V>::calculateHeight(Node* subtree)
{
    if(!subtree){
        return -1;
    }

    return max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;

    
}

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* newRoot = t->right;
    Node* newRootLeft = t;
    Node* newRootLeftRight = newRoot->left;

    t = newRoot;
    newRoot->left = newRootLeft;
    newRootLeft->right = newRootLeftRight;

    newRoot->left->height = calculateHeight(newRoot->left);
    newRoot->height = calculateHeight(newRoot);
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* newRoot = t->left;
    Node* newRootRight = t;
    Node* newRootRightLeft =  newRoot->right;

    t = newRoot;
    newRoot->right = newRootRight;
    newRootRight->left = newRootRightLeft;

    newRoot->right->height = calculateHeight(newRoot->right);
    newRoot->height = calculateHeight(newRoot);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if(!subtree) return;
    subtree->height = calculateHeight(subtree);
    //cout<<"value: "<<subtree->value<<" height: "<<subtree->height<<endl;
    // your code here
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(abs(balance) < 2){
        return;
    }

    else if(balance == -2){
      int nextB = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if(nextB == -1) {rotateRight(subtree);}
      else            {rotateLeftRight(subtree);}
    }
    else{
      int nextB = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
      if(nextB == 1) {rotateLeft(subtree);}
      else            {rotateRightLeft(subtree);}
    }


}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(!subtree){
        subtree = new Node(key, value);
        return;
    }

    else if(subtree->key > key){
        insert(subtree->left, key, value);
    }
    else{
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    Node* temp;
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            temp = subtree;
            subtree = NULL;
            delete temp;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            Node* IOP = subtree->left;
            while(IOP->right){
                IOP = IOP->right;
            }
            swap(subtree, IOP);

            remove(subtree->left, key);
            /* two-child remove */
            // your code here
        } else {
            if(subtree->left){
                temp = subtree;
                subtree = subtree->left;
                delete temp;
            }
            else{
                temp = subtree;
                subtree = subtree->right;
                delete temp;
            }
            /* one-child remove */
            // your code here
        }
        // your code here
    }
    rebalance(subtree);
}
