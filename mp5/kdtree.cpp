/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(curDim < Dim && curDim >= 0){
        if(first[curDim]!=second[curDim])
            return first[curDim] < second[curDim];
        return first < second;
    }

    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */


    double curr = getDistance(target, currentBest);
    double poten = getDistance(target, potential);
    if(curr != poten)
        return poten < curr;
    return potential < currentBest;
}


template <int Dim>
double KDTree<Dim>::getDistance(const Point<Dim>& target1,
                             const Point<Dim>& target2) const{
    double ret = 0.0;
    for (int i = 0; i < Dim; i++){
        ret += ((double)target1[i]-(double)target2[i])*((double)target1[i]-(double)target2[i]);
    }
    return ret;

}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(int left, int right, int dimension, int midIndex){
    if (left == right){
        return points[left];
    }
    int pivotIndex = (right + left) / 2;
    pivotIndex = partition(left, right, dimension, pivotIndex);
    if (pivotIndex == midIndex){
        return points[pivotIndex];
    }
    else if (midIndex < pivotIndex){
        return quickSelect(left, pivotIndex-1, dimension, midIndex);
    }
    else{
        return quickSelect(pivotIndex+1, right, dimension, midIndex);
    }

}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int dimension, int pivotIndex){
    Point<Dim> pivotValue = points[pivotIndex];
    swap(points[pivotIndex], points[right]);
    int a = left;
    for (int i = left; i < right; i++){
        //cout << points[i] << endl;
        if (smallerDimVal(points[i], pivotValue, dimension)){
            //cout << "Swap " << points[i] << endl;
            swap(points[a], points[i]);
            a++;
        }
    }
    swap(points[a], points[right]);
    return a;

}

template <int Dim>
void KDTree<Dim>::buildTree(int left, int right, int dimension){
    if (right < 0) {
        root = NULL;
        return;
    }
    int median = (left + right)/2;
    root = new KDTreeNode(quickSelect(left, right, dimension, median));

    if (left <= median-1){
        buildTreeHelper(left, median - 1, (dimension + 1) % Dim, root->left);

    }

    if (right >= median+1){
        buildTreeHelper(median + 1, right, (dimension + 1) % Dim, root->right);

    }
}

template <int Dim>
void KDTree<Dim>::buildTreeHelper(int left, int right, int dimension, KDTreeNode *&node){
    int median = (left + right) / 2;
    node = new KDTreeNode(quickSelect(left, right, dimension, median));
    if (left <= median-1){
        buildTreeHelper(left, median - 1, (dimension + 1) % Dim, node->left);

    }

    if (right >= median+1){
        buildTreeHelper(median + 1, right, (dimension + 1) % Dim, node->right);

    }

}



template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    points = newPoints;
    buildTree(0, points.size()-1, 0);


}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
    _copy(other);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */

    if (this == &rhs){
        return *this;
    }
    _destroy();
    _copy(rhs);
    return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
    _destroy();
}

/**
 * helper function for copy the KDTree
 * @tparam Dim data
 * @param other is other KDTree to copy
 */
template <int Dim>
void KDTree<Dim>::_copy(const KDTree &other){
    size = other.size;
    points.resize(size);
    for (unsigned i = 0; i < size; i++){
        points[i] = other.points[i];

    }

}
/**
 * helper function for destrcution
 * @tparam Dim data
 */
template <int Dim>
void KDTree<Dim>::_destroy(){
    points.erase (points.begin(),points.end());
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if (points.empty()){
        return NULL;
    }
    return helperNN(query, 0, this->points.size()-1, 0);
}

/**
*   helperNN is the helper funtion for findNearestNeighbor
*   input:
*   target point, bound of search in vector, current dimension
*   function: as described in MP5 webpage,
*   go all the way down then back trace and check if should go to right branch according to median value
*   output:
*   the point that is closest to the target point
**/
template <int Dim>
Point<Dim> KDTree<Dim>::helperNN(const Point<Dim>& query, int start, int end, int dimension) const
{
    /**
     * @todo Implement this function!
     */
    // Base case: touch down
    int mid = (start+end)/2;
    if (start >= end){
        return this->points[mid];
    }

    int nextDim = (dimension+1)%Dim;
    Point<Dim> curBest;
    if (smallerDimVal(this->points[mid],query,dimension)){
        // go right
        curBest = helperNN(query, mid+1, end, nextDim);
    }else{
        // go left
        curBest = helperNN(query, start, mid-1, nextDim);
    }
    // after touch down, check if median is actually nearer

    if (shouldReplace(query, curBest, this->points[mid])){
        curBest = this->points[mid];
    }
    // update the radius of current best (square)
    double cur_best_r = 0;
    for (int i=0; i<Dim; i++){
        cur_best_r += (query[i]-curBest[i])*(query[i]-curBest[i]);
    }
    double mid_r = (query[dimension]-points[mid][dimension])*(query[dimension]-points[mid][dimension]);
    // should go right branch
    if(mid_r <= cur_best_r){
        Point<Dim> potBest;
        if (smallerDimVal(this->points[mid],query,dimension)){
            // go left
            potBest = helperNN(query, start, mid-1, nextDim);
        }else{
            // go right
            potBest = helperNN(query, mid+1, end, nextDim);
        }
        if (shouldReplace(query, curBest, potBest)){
            curBest = potBest;
        }
    }

    return curBest;
}
