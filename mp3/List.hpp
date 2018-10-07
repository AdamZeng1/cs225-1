/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != NULL) {
    ListNode * headnext = head_->next;
    delete head_;
    head_ = headnext;
  }
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
	ListNode * newFront = new ListNode(ndata);
	if (length_ == 0) {
    tail_ = newFront;
    head_ = newFront;
    length_ = 1;
    return;
  }
  head_->prev = newFront;
  newFront->next = head_;
	newFront->prev = NULL;
  head_ = newFront;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newBack = new ListNode(ndata);
  newBack->next = NULL;
  if (length_ == 0) {
    head_ = newBack;
    tail_ = newBack;
    length_ = 1;
    return;
  } 
  tail_->next = newBack;
  newBack->prev = tail_;
  tail_ = newBack;
  length_++;
}

/**
 * Reverses the current List.
 */
template <typename T>
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
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  ListNode * curstart = startPoint;

  ListNode * veryStart = curstart->prev;
  ListNode * temp = curstart->next;
  curstart->next = endPoint->next;
  curstart->prev = temp;
  curstart = temp;

  while (curstart != endPoint) {
    temp = curstart->next;
    curstart->next = curstart->prev;
    curstart->prev = temp;
    curstart = temp;
  }

  endPoint->next = endPoint->prev;
  endPoint->prev = veryStart;
  if (head_ != startPoint) {veryStart->next = curstart;}
  if (tail_ != endPoint) {startPoint->next->prev = startPoint;}

  if (head_ == startPoint) {head_ = endPoint;}
  if (tail_ == endPoint) {tail_ = startPoint;}
}
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  ListNode * curstart = head_;
  ListNode * curend = curstart;

  while (curstart != NULL) {
    int count = 1;
    while (count < n) {
      if (curend != tail_) {
        curend = curend->next;
      }
      count++;
    }
    reverse(curstart, curend);
    curstart = curstart->next;
    curend = curstart;
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
template <typename T>
void List<T>::waterfall() {
  ListNode * curnode = head_;
  ListNode * temp;
  int count = 0;
  while (curnode != tail_) {
    temp = curnode->next;
    if (count % 2 == 1) {
      curnode->prev->next = curnode->next;
      curnode->next->prev = curnode->prev;

      tail_->next = curnode;
      curnode->prev = tail_;
      curnode->next = NULL;
      tail_ = curnode;
    }
    count++;
    curnode = temp;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
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
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  ListNode * curnode = start;
  int count = 0;
  while (count < splitPoint) {
    curnode = curnode->next;
    count++;
  }

  curnode->prev->next = NULL;
  curnode->prev = NULL;
  return curnode;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
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
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  
  if (first->next == NULL && second->next == NULL) {
    if (first->data < second->data) {
      second->next = first;
      first->prev = second;
      return second;
    }
    else {
      first->next = second;
      second->prev = first;
      return first;
    }
  }

  ListNode * temp;
  ListNode * ret = first;
  if (second->data < first->data) {
    ret = second;
    second->next = first;
    second->prev = NULL;

  }

  while (second != NULL) {
    if (first->next == NULL && first->data < second->data) {
      first->next = second;
      second->prev = first;
      break;
    }
    else if (second->data < first->data || second->data == first->data) {
      temp = second->next;
      temp->prev = NULL;

      second->next = first;
      second->prev = first->prev;
      if (first->prev != NULL) {first->prev->next = second;}
      first->prev = second;

      second = temp;
    }
    else {
      first = first->next;
    }
  }

  return ret;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
        cout << 2 << endl;
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
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  cout << chainLength << endl;
  if (start->next == NULL) {return start;}
  ListNode * second = split(start, chainLength / 2);
  return merge(mergesort(start, chainLength / 2), mergesort(second, chainLength / 2));
}
