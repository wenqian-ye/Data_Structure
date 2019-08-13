//
// /**
//  * @file heap.cpp
//  * Implementation of a heap class.
//  */
//
// template <class T, class Compare>
// size_t heap<T, Compare>::root() const
// {
//     // @TODO Update to return the index you are choosing to be your root.
//     return 1;
// }
//
// template <class T, class Compare>
// size_t heap<T, Compare>::leftChild(size_t currentIdx) const
// {
//     // @TODO Update to return the index of the left child.
//     int left = currentIdx*2;
//     return left;
// }
//
// template <class T, class Compare>
// size_t heap<T, Compare>::rightChild(size_t currentIdx) const
// {
//     // @TODO Update to return the index of the right child.
//     int right = currentIdx*2 + 1;
//     return right;
// }
//
// template <class T, class Compare>
// size_t heap<T, Compare>::parent(size_t currentIdx) const
// {
//     // @TODO Update to return the index of the parent.
//
//     return currentIdx/2;
// }
//
// template <class T, class Compare>
// bool heap<T, Compare>::hasAChild(size_t currentIdx) const
// {
//     // @TODO Update to return whether the given node has a child
//
//     return currentIdx <= _elems.size()/2;
// }
//
// template <class T, class Compare>
// size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
// {
//     // @TODO Update to return the index of the child with highest priority
//     ///   as defined by higherPriority()
//
//     return _elems[currentIdx/2] < _elems[currentIdx/2 + 1] ? currentIdx/2 : currentIdx/2 + 1;
// }
//
// template <class T, class Compare>
// void heap<T, Compare>::heapifyDown(size_t currentIdx)
// {
//     // @TODO Implement the heapifyDown algorithm.
//     size_t length = _elems.size();
//     size_t leftChild = currentIdx * 2;
//     size_t rightChild = currentIdx * 2 + 1;
//
//     if(leftChild >= length)
//         return;
//     size_t min = currentIdx;
//
//     if(higherPriority(_elems[leftChild], _elems[currentIdx]))
//         min = leftChild;
//     if(rightChild < length && higherPriority(_elems[rightChild], _elems[min]))
//         min = rightChild;
//     if(min != currentIdx){
//
//         std::swap(_elems[currentIdx], _elems[min]);
//         heapifyDown(min);
// }
//
// }
//
// template <class T, class Compare>
// void heap<T, Compare>::heapifyUp(size_t currentIdx)
// {
//     if (currentIdx == root())
//         return;
//     size_t parentIdx = parent(currentIdx);
//     if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
//         std::swap(_elems[currentIdx], _elems[parentIdx]);
//         heapifyUp(parentIdx);
//     }
// }
//
// template <class T, class Compare>
// heap<T, Compare>::heap()
// {
//     // @TODO Depending on your implementation, this function may or may
//     ///   not need modifying
//
//     // for (unsigned i = parent(_elems.size()); i > 0 ; i--) {
//     //   heapifyDown(i);
//     // }
//     T inf = std::numeric_limits<T>::min();
//     _elems.push_back(inf);
//
// }
//
// template <class T, class Compare>
// heap<T, Compare>::heap(const std::vector<T>& elems)
// {
//     // @TODO Construct a heap using the buildHeap algorithm
// }
//
// template <class T, class Compare>
// T heap<T, Compare>::pop()
// {
//     // @TODO Remove, and return, the element with highest priority
//
//     T temp = _elems[1];
//
//     std::swap(_elems[1], _elems[_elems.size()-1]);
//     _elems.pop_back();
//     heapifyDown(1);
//
//     return temp;
// }
//
// template <class T, class Compare>
// T heap<T, Compare>::peek() const
// {
//     // @TODO Return, but do not remove, the element with highest priority
//      return _elems[1];
// }
//
// template <class T, class Compare>
// void heap<T, Compare>::push(const T& elem)
// {
//     // @TODO Add elem to the heap
//     _elems.push_back(elem);
//     heapifyUp(_elems.size()-1);
// }
//
// template <class T, class Compare>
// bool heap<T, Compare>::empty() const
// {
//     // @TODO Determine if the heap is empty
//     if(_elems.size() > 1)
//         return false;
//     return true;
// }
//
// template <class T, class Compare>
// void heap<T, Compare>::getElems(std::vector<T> & heaped) const
// {
//     for (size_t i = root(); i < _elems.size(); i++) {
//         heaped.push_back(_elems[i]);
//     }
// }


/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
    if(currentIdx*2 >= _elems.size())
        return false;
    return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()

    if(hasAChild(currentIdx))
        return 0;
    size_t ret = currentIdx * 2;
    if(ret+1 >= _elems.size())
        return ret;
    if(higherPriority(_elems[ret], _elems[ret+1]))
        return ret;
    else
        return ret+1;
    //return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.

    size_t length = _elems.size();
    size_t leftChild = currentIdx * 2;
    size_t rightChild = currentIdx * 2 + 1;

    if(leftChild >= length)
        return;
    size_t min = currentIdx;

    if(higherPriority(_elems[leftChild], _elems[currentIdx]))
        min = leftChild;
    if(rightChild < length && higherPriority(_elems[rightChild], _elems[min]))
        min = rightChild;
    if(min != currentIdx){
        /*
        T temp = _elems[currentIdx];
        _elems[currentIdx] = _elems[min];
        _elems[min] = temp;
        */
        std::swap(_elems[currentIdx], _elems[min]);
        heapifyDown(min);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying

    T inf = std::numeric_limits<T>::min();
    _elems.push_back(inf);

}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm

    T inf = std::numeric_limits<T>::min();
    _elems.push_back(inf);
    _elems.insert(_elems.end(), elems.begin(), elems.end());
    for(size_t i = parent(_elems.size()-1); i>0; i--){
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority

    T temp = _elems[1];

    std::swap(_elems[1], _elems[_elems.size()-1]);
    _elems.pop_back();
    heapifyDown(1);

    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    if(_elems.size() > 1)
        return false;
    return true;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
