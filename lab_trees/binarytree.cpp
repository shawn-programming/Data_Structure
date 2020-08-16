/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <stack>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
<<<<<<< HEAD
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    //your code here
    if(!subRoot){
      return;
    }

    mirror(subRoot->left);
    mirror(subRoot->right);

    Node* temp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = temp;

=======
>>>>>>> refs/remotes/origin/master
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    // Base case
    if (subRoot == NULL)
        return;

    mirror(subRoot->left);
    mirror(subRoot->right);

    Node* tempLeft = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = tempLeft;
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{

  InorderTraversal<int> iot(root);
  int temp = INT_MIN;

  for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
      if(temp > (*it)->elem){return false;}
      temp = (*it)->elem;
  }

  return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
  if(!root) return true;
    std::stack<int> st;
  inOrderIsRecursive(root, st);
  int temp = INT_MAX;
  while(!st.empty()){
    if(temp < st.top()) return false;
    temp = st.top();
    st.pop();
  }
  return true;
}
<<<<<<< HEAD
=======

template <typename T>
void BinaryTree<T>::inOrderIsRecursive(Node* subroot, std::stack<int> &st) const
{
    if(!subroot)
      return;

    inOrderIsRecursive(subroot->left, st);
    st.push(subroot->elem);
    inOrderIsRecursive(subroot->right, st);
}
>>>>>>> refs/remotes/origin/master
