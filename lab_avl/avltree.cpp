///**
// * @file avltree.cpp
// * Definitions of the binary tree functions you'll be writing for this lab.
// * You'll need to modify this file.
// */
//
//template <class K, class V>
//V AVLTree<K, V>::find(const K& key) const
//{
//    return find(root, key);
//}
//
//template <class K, class V>
//V AVLTree<K, V>::find(Node* subtree, const K& key) const
//{
//    if (subtree == NULL)
//        return V();
//    else if (key == subtree->key)
//        return subtree->value;
//    else {
//        if (key < subtree->key)
//            return find(subtree->left, key);
//        else
//            return find(subtree->right, key);
//    }
//}
//
//template <class K, class V>
//void AVLTree<K, V>::rotateLeft(Node*& root)
//{
//    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
//    // your code here
//    Node* child = root->right;
//    root->right = child->left;
//    child->left = root;
//    root = child;
//
//
//}
//
//template <class K, class V>
//void AVLTree<K, V>::rotateLeftRight(Node*& t)
//{
//    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
//    // Implemented for you:
//    rotateLeft(t->left);
//    rotateRight(t);
//}
//
//template <class K, class V>
//void AVLTree<K, V>::rotateRight(Node*& root)
//{
//    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
//    // your code here
//    Node* child = root->left;
//    root->left = child->right;
//    child->right = root;
//    root = child;
//}
//
//template <class K, class V>
//void AVLTree<K, V>::rotateRightLeft(Node*& t)
//{
//    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
//    // your code here
//    rotateRight(t->right);
//    rotateLeft(t);
//}
//
//template <class K, class V>
//int AVLTree<K, V>::getHeight(Node* root){
//    if(root == NULL){
//        //root->height = -1;
//        return -1;
//    }
//    return 1 + max(getHeight(root->left), getHeight(root->right));
//}
//
//template <class K, class V>
//void AVLTree<K, V>::setBF(Node* root){
//    if(root == NULL)
//        return;
//    //if(root != NULL)
//    root->balanceFactor = getHeight(root->right) - getHeight(root->left);
//}
//
//template <class K, class V>
//int AVLTree<K, V>::getBF(Node* root){
//    if(root == NULL)
//        return 0;
//    return root->balanceFactor;
//}
//
//
//template <class K, class V>
//void AVLTree<K, V>::rebalance(Node*& subtree)
//{
//    // your code here
//    if(subtree == NULL)
//        return;
//    setBF(subtree);
//    setBF(subtree->left);
//    setBF(subtree->right);
//    int leftB = getBF(subtree->left);
//    int rightB = getBF(subtree->right);
//
//    if(subtree->balanceFactor > 1){
//        if(rightB == 1)
//            rotateLeft(subtree);
//        else
//            rotateRightLeft(subtree);
//    }
//    else if(subtree->balanceFactor < -1){
//        if(leftB == -1)
//            rotateRight(subtree);
//        else{
//            rotateLeftRight(subtree);
//        }
//    }
//    setHeight(subtree);
//    setBF(subtree);
//    setBF(subtree->left);
//    setBF(subtree->right);
//
//}
//
//template <class K, class V>
//void AVLTree<K, V>::insert(const K & key, const V & value)
//{
//    insert(root, key, value);
//}
//
//template <class K, class V>
//void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
//{
//    // your code here
//    if(subtree == NULL){
//        subtree = new Node(key, value);
//        rebalance(subtree);
//    }
//    else if(key < subtree->key){
//        insert(subtree->left, key, value);
//        rebalance(subtree);
//    }
//    else if(key > subtree->key){
//        insert(subtree->right, key, value);
//        rebalance(subtree);
//    }
//
//}
//
//template <class K, class V>
//void AVLTree<K, V>::remove(const K& key)
//{
//    remove(root, key);
//}
//
//template <class K, class V>
//void AVLTree<K, V>::remove(Node*& subtree, const K& key)
//{
//    if (subtree == NULL)
//        return;
//
//    if (key < subtree->key) {
//        // your code here
//    } else if (key > subtree->key) {
//        // your code here
//    } else {
//        if (subtree->left == NULL && subtree->right == NULL) {
//            /* no-child remove */
//            // your code here
//        } else if (subtree->left != NULL && subtree->right != NULL) {
//            /* two-child remove */
//            // your code here
//        } else {
//            /* one-child remove */
//            // your code here
//        }
//        // your code here
//    }
//}
#include <iostream>
using namespace std;
/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

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
    // your code here
    Node* n1 = t;
    Node* n2 = n1->right;
    Node* n3 = n2->right;
    t = n2;
    n1->right = n2->left;
    n2->left = n1;
    n1->height = 1+max(heightOrNeg1(n1->left),heightOrNeg1(n1->right));
    n2->height = 1+max(heightOrNeg1(n2->left),heightOrNeg1(n2->right));
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
    Node* n1 = t;
    Node* n2 = n1->left;
    Node* n3 = n2->left;
    t = n2;
    n1->left = n2->right;
    n2->right = n1;
    n1->height = 1+max(heightOrNeg1(n1->left),heightOrNeg1(n1->right));
    n2->height = 1+max(heightOrNeg1(n2->left),heightOrNeg1(n2->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree){
    // your code here
    if (subtree == NULL){
        return;
    }
    if (subtree->left == NULL && subtree->right == NULL){
        return;
    }
    Node* l = subtree->left;
    Node* r = subtree->right;
    int b = heightOrNeg1(r) - heightOrNeg1(l);
    // cout << subtree->value << endl;
    // cout << b << endl;

    if (b <= -2){//left longer
        int bb = heightOrNeg1(l->right) - heightOrNeg1(l->left);
        if (bb == 1){//leg, lr
            rotateLeftRight(subtree);
        }
        if (bb == -1){//stick, r
            rotateRight(subtree);
        }
    }
    if (b >= 2){//right longer
        int bb = heightOrNeg1(r->right) - heightOrNeg1(r->left);
        if (bb == 1){//stick, l
            rotateLeft(subtree);
        }
        if (bb == -1){//leg, rl
            rotateRightLeft(subtree);
        }
    }
    subtree->height = 1+max(heightOrNeg1(subtree->right),heightOrNeg1(subtree->left));
    return;
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
    // Node*& tar = _find(subtree, key);
    // tar = new Node(key, value);
    if (subtree == NULL){
        subtree = new Node(key, value);
        subtree->height = 0;
        return;
    }
    // if (subtree->key == key){
    //     return;
    // }
    if (subtree->key < key){//insert right
        insert(subtree->right, key, value);
    }else{//insert left
        insert(subtree->left, key, value);
    }
    rebalance(subtree);

    return;

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}


template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            Node* cur = subtree->left;
            while (cur->right != NULL){
                cur = cur->right;
            }
            swap(subtree, cur);
            Node* cur2 = subtree->left;
            if (cur2 == cur) {
                cur2 = NULL;
            }else {
                while (cur2->right != cur) {
                    cur2 = cur2->right;
                }
                cur2->right = NULL;
            }
        } else {
            if (subtree->left != NULL){
                Node* temp = subtree;
                subtree = subtree->left;
            }
            if (subtree->right != NULL){
                Node* temp = subtree;
                subtree = subtree->right;
            }
        }
    }
    rebalance(subtree);
}