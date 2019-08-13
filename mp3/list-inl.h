/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
#include <iostream>
using namespace std;
template <class T>
List<T>::~List() {
    /// @todo Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
    /// @todo Graded in MP3.1
    ListNode* curr = head_;
    ListNode* prev = NULL;
    while(curr != NULL){
        prev = curr;
        curr = curr->next;
        delete prev;
    }
    tail_ = NULL;
    length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
    /// @todo Graded in MP3.1

    ListNode* nnode = new ListNode(ndata);
    nnode->next = NULL;
    nnode->prev = NULL;
    if(head_ == NULL){
        head_ = nnode;
        tail_ = head_;
        length_++;
    }
    else{
        nnode->next = head_;
        head_->prev = nnode;
        head_ = nnode;
        length_ = length_ + 1;
    }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
    /// @todo Graded in MP3.1

    ListNode* nnode = new ListNode(ndata);
    nnode->next = NULL;
    nnode->prev = NULL;
    if(tail_ == NULL){
        tail_ = nnode;
        head_ = tail_;
        length_++;
    }
    else{
        tail_->next = nnode;
        nnode->prev = tail_;
        tail_ = nnode;
        length_++;
    }
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
    reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1


    if(startPoint == endPoint || startPoint == NULL || endPoint == NULL){
        return;
    }
    int count = getLength(startPoint, endPoint);
    ListNode* s_curr = startPoint;
    ListNode* s_curr_next = s_curr->next;
    ListNode* s_curr_prev = s_curr->prev;
    for(int i = 0; i < count; i++){
        s_curr->prev = s_curr_next;
        s_curr->next = s_curr_prev;
        s_curr_prev = s_curr;
        s_curr = s_curr_next;
        if(s_curr_next != NULL){
            s_curr_next = s_curr_next->next;
        }
    }
    if(startPoint->next != NULL){
        ListNode* temp = startPoint->next;
        temp->next = endPoint;
    }
    startPoint->next = endPoint->prev;
    ListNode* temp1 = startPoint->next;
    if(endPoint->prev != NULL){
        ListNode* temp = endPoint->prev;
        temp->prev = startPoint;
    }
    endPoint->prev = temp1;

    ListNode* temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;


}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
    /// @todo Graded in MP3.1

    if(length_ <= 1 || n == 1){
        return;
    }
    if(n == length_){
        reverse();
    }

    ListNode* temp = head_;
    ListNode* newh = head_;
    ListNode* newt = NULL;
    int count = n;
    while(temp != NULL){
        if(count == 0){
            if(newh == head_){
                head_ = newt;
            }
            reverse(newh, newt);
            count = n;
            newh = temp;
            newt = temp;
        }
        if(temp->next == NULL){
            reverse(newh, temp);
        }
        newt = temp;
        temp = temp->next;
        count--;
    }

}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
    /// @todo Graded in MP3.1
    if(length_ == 0){
        return;
    }
    ListNode* curr = head_;
    ListNode* t_prev = curr;
    ListNode* t_next = curr->next->next;
    while(curr->next != tail_ && curr->next != NULL){
        curr = curr->next;
        tail_->next = curr;
        curr->prev = tail_;
        curr->next = NULL;
        tail_ = curr;
        t_prev->next = t_next;
        t_next->prev = t_prev;
        curr = t_next;
        t_next = t_next->next->next;
        t_prev = t_prev->next;

    }






}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    if(start == NULL){
        return NULL;
    }
    tail_ = start;
    for(int i = 0; i < splitPoint && tail_->next != NULL; i++){
        tail_= tail_->next;
    }
    tail_->prev->next = NULL;
    return tail_;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
    /// @todo Graded in MP3.2
    if(first == NULL && second == NULL){
        return NULL;
    }
    if(first == second){
        return first;
    }
    ListNode* curr_first = first;
    ListNode* curr_second = second;
    ListNode* prev_second;
    if(curr_first->data < curr_second->data){
        ListNode* next_first = curr_first->next;
        curr_second->prev = curr_first;
        curr_first->next = curr_second;
        curr_first->prev = NULL;
        //curr_second = curr_second->next;
        curr_first = next_first;
        prev_second = curr_second->prev;
    }
    else{
        prev_second = curr_second;
        curr_second = curr_second->next;
    }
    while(curr_first != NULL && curr_second != NULL){
        if(curr_first->data < curr_second->data){
            ListNode* next_first = curr_first->next;
            curr_first->next = curr_second;
            curr_first->prev = prev_second;
            curr_second->prev = curr_first;
            prev_second->next = curr_first;
            curr_first = next_first;
            prev_second = curr_second->prev;
        }
        else{
            prev_second = curr_second;
            curr_second = curr_second->next;
        }
    }
    if(curr_second == NULL){
        if(curr_first != NULL){
            //curr_second = curr_second->prev;
            prev_second->next = curr_first;
            curr_first->prev = prev_second;
        }
    }
    while(second->prev != NULL){
        second = second->prev;
    }
    return second;

}
/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}
/**return the length between given startpoint and endpoint.
 *
 * @tparam T template
 * @param startPoint sp
 * @param endPoint ep
 * @return length
 */
template<class T>
int List<T>::getLength(ListNode* startPoint, ListNode* endPoint){
    ListNode* curr = startPoint;
    int length = 1;
    if(startPoint == NULL || endPoint == NULL){
        return -10;
    }
    while(curr != endPoint){
        if(curr == NULL){
            return -10;
        }
        length++;
        curr = curr->next;
    }
    return length;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2


    ListNode * hMergesort = start;
    if (chainLength == 1){
        start->next = start->prev = NULL;
        return start;
    }
    else{
        ListNode * secondStart = start;
        for(int i = 0; i < chainLength/2; i++){
            secondStart = secondStart->next;
        }
        secondStart->prev->next = NULL;
        secondStart->prev = NULL;
        start = mergesort(start, chainLength/2);
        secondStart = mergesort(secondStart, chainLength-chainLength/2);
        hMergesort = merge(start, secondStart);
    }
    return hMergesort;

}