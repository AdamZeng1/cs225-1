/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

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
    return 1 + max(height(subRoot->left), height(subRoot->right));
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
    cout << endl;
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
    cout << subRoot->elem << ' ';

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
    mirror(root);
}


template <typename T>
void BinaryTree<T>::mirror(Node * subRoot)
{
    if (subRoot == NULL) {return;}
    mirror(subRoot->left);
    mirror(subRoot->right);
    Node * temp = subRoot->right;
    subRoot->right = subRoot->left;
    subRoot->left = temp;
    return;
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
    InorderTraversal<int> travis(root);
    int previous;
    for (TreeTraversal<int>::Iterator iter = travis.begin(); iter != travis.end(); ++iter) {
        if ((*iter)->elem == (*travis.begin())->elem) {
            previous = (*iter)->elem;
            continue;
        }
        if((*iter)->elem > previous) {
            previous = (*iter)->elem;
            continue;
        }
        else {return false;}
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
    return isOrderedRecursive(root);
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::mostLeft(typename BinaryTree<T>::Node *subRoot) const{
    if (subRoot == NULL){
        return NULL;
    }
    if (subRoot->left == NULL){
        return subRoot;
    }
    return mostLeft(subRoot->left);
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::mostRight(typename BinaryTree<T>::Node *subRoot) const{
    if (subRoot == NULL){
        return NULL;
    }
    if (subRoot->right == NULL){
        return subRoot;
    }
    return mostRight(subRoot->right);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(const Node *subRoot) const{
    if (subRoot == NULL)
        return true;
    if (subRoot->left != NULL){
        if (mostLeft(subRoot->left)->elem > subRoot->elem){
            return false;
        }
    }
    if (subRoot->right != NULL){
        if (mostRight(subRoot->right)->elem < subRoot->elem){
            return false;
        }
    }
    if (!isOrderedRecursive(subRoot->left) || !isOrderedRecursive(subRoot->right)){
        return false;
    }
    return true;
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(vector<vector<T> > &paths) const
{
    paths.resize(1);
    getPaths(paths, root);
    paths.pop_back();
}
template <typename T>
void BinaryTree<T>::getPaths(vector<vector<T>> &paths, Node* current) const {
    if (current->left == NULL && current->right == NULL) {
        paths.back().push_back(current->elem);
        vector<T> next = paths.back();
        next.pop_back();
        paths.push_back(next);
    }
    else {
        paths.back().push_back(current->elem);
        if (current->left != NULL) {getPaths(paths, current->left);}
        if (current->right != NULL) {getPaths(paths, current->right);}
        paths.back().pop_back();
    }
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return -1;
}

