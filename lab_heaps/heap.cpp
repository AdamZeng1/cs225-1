
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

#include <iostream>
using namespace std;

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const {
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const {
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const {
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const {
    return currentIdx * 2 < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const {
    size_t left = currentIdx * 2;
    size_t right = currentIdx * 2 + 1;
    if (right >= _elems.size()) return left;
    if (higherPriority(_elems[left], _elems[right])) return left;
    return right;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx) {
    if (currentIdx * 2 >= _elems.size()) return;
    size_t childIdx = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[childIdx], _elems[currentIdx])) {
    	std::swap(_elems[childIdx], _elems[currentIdx]);
    	heapifyDown(childIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx) {
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) {
    _elems = {T()};

    for (auto elem: elems) 
    	_elems.push_back(elem);

    for (size_t idx = _elems.size() - 1; idx > 0; idx--)
    	heapifyDown(idx);
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    if (_elems.size() == 1) return T();
    T temp = _elems[1];
    std::swap(_elems[1], _elems.back());
    _elems.pop_back();
    heapifyDown(1);
    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem) {
	_elems.push_back(elem);
	heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem) {
	size_t converted_idx = idx + root();
    _elems[converted_idx] = elem;
    if (higherPriority(elem, _elems[parent(converted_idx)]))
    	heapifyUp(converted_idx);
    else heapifyDown(converted_idx);
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    return _elems.size() == 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
