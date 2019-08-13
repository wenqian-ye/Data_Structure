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
    // your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot) const{
    if(subRoot == NULL)
        return;
    mirror(subRoot->left);
    mirror(subRoot->right);

    Node* temp;

    temp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = temp;
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
//     your code here
    return isOrderedRecursive(root);


}
template <typename T>
bool BinaryTree<T>::isOrderedIterative(Node* root) const {
    InorderTraversal<T> iot(root);
    bool isOrderedIterative = true;
    T temp = (*iot.begin())->elem;
    for(typename TreeTraversal<T>::Iterator it = iot.begin(); it != iot.end(); ++it) {
        if (temp > (*it)->elem) {
            isOrderedIterative = false;
            break;
        }
        temp = (*it)->elem;
    }
    return isOrderedIterative;

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

    // your code here
    return isOrderedRecursive(root);

}
template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* subRoot) const
{

    // your code here
    bool isOrdered = true;
    if(subRoot == NULL){
        return true;
    }
    if (subRoot->left != NULL){
        if (subRoot->elem < maxElementOnLeft(subRoot->left)){
            isOrdered = false;
        }
    }
    if(subRoot->right != NULL){
        if (subRoot->elem > minElementOnRight(subRoot->right)){
            isOrdered = false;
        }
    }

    if (isOrdered && isOrderedRecursive(subRoot->left) && isOrderedRecursive(subRoot->right)) {
        return true;
    }

    return false;


}


template <typename T>
T BinaryTree<T>::maxElementOnLeft(Node *subRoot) const{
    if (subRoot->left == NULL && subRoot->right == NULL){
        return subRoot->elem;
    }else if (subRoot->left == NULL){
        return(max(subRoot->elem,maxElementOnLeft(subRoot->right)));
    }else if (subRoot->right == NULL) {
        return (max(subRoot->elem,maxElementOnLeft(subRoot->left)));

    } else {
        return max(max(subRoot->elem,maxElementOnLeft(subRoot->left)),
                   maxElementOnLeft(subRoot->right));
    }
}


template <typename T>
T BinaryTree<T>::minElementOnRight(Node *subRoot) const{
    if (subRoot->left == NULL && subRoot->right == NULL){
        return subRoot->elem;
    }else if (subRoot->left == NULL){
        return(max(subRoot->elem,minElementOnRight(subRoot->right)));
    }else if (subRoot->right == NULL) {
        return (max(subRoot->elem,minElementOnRight(subRoot->left)));

    } else {
        return max(max(subRoot->elem, minElementOnRight(subRoot->left)),
                   minElementOnRight(subRoot->right));
    }
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
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    std::vector <const BinaryTree<T>::Node *> treeVec;
    printPaths(treeVec, root);
}


template <typename T>
void BinaryTree<T>::printPaths(vector <const BinaryTree<T>::Node *> &treeVec,
                               const Node* subRoot) const
{
    // your code here
    treeVec.push_back(subRoot);
    if(subRoot->left == NULL&&subRoot->right == NULL)
        printVector(treeVec);
    if(subRoot->left != NULL)
        printPaths(treeVec, subRoot->left);
    if(subRoot->right != NULL)
        printPaths(treeVec, subRoot->right);
    treeVec.pop_back();
    return;
}

template <typename T>
void BinaryTree<T>::printVector(vector <const BinaryTree<T>::Node *> treeVec) const
{
    std::cout<<"Path:";
    for (typename vector<const BinaryTree<T>::Node *>::iterator it = treeVec.begin(); it != treeVec.end(); ++it)
        std::cout << ' ' << (*it)->elem;
    std::cout<<endl;

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
    int sum = 0;
    return sumDistances(-1, root, sum);


}

template <typename T>
int & BinaryTree<T>::sumDistances(int distanceHave, const Node* subRoot, int &sum) const
{
    distanceHave++;
    sum += distanceHave;
    if(subRoot->left != NULL)
        sum = sumDistances(distanceHave, subRoot->left, sum);
    if(subRoot->right != NULL)
        sum = sumDistances(distanceHave, subRoot->right, sum);
    return sum;

}