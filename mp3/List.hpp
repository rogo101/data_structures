#include <iostream>

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
  return List<T>::ListIterator(tail_ -> next);
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
  while (head_ != nullptr && head_ -> next != nullptr) {
    tail_ = head_ -> next;
    delete head_;
    head_ = tail_;
  }
  while (head_ != nullptr && head_ -> next== nullptr) {
    delete head_;
    head_ = nullptr;
  }
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function *SHOULD* create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * toInsert = new ListNode(ndata);
  if (head_ == nullptr) {
    head_ = toInsert;
    length_++;
    tail_ = head_;
    return;
  }
  toInsert -> next = head_;
  head_ -> prev = toInsert;
  head_ = toInsert;
  length_++;
  tail_ = head_;
  while (tail_ -> next != NULL) {
    tail_ = tail_ -> next;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function *SHOULD* create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * toInsert = new ListNode(ndata);
  if (tail_ == nullptr) {
    head_ = toInsert;
    length_++;
    tail_ = head_;
    return;
  }
  tail_ -> next = toInsert;
  toInsert -> prev = tail_;
  tail_ = tail_ -> next;
  length_++;
  toInsert = NULL;

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
  /// @todo Graded in MP3.1
  bool checkCases = startPoint == endPoint || startPoint == NULL || endPoint == NULL;
  if (checkCases) {
    return;
  }

  ListNode * curr = startPoint;
  ListNode * temp1 = startPoint;
  ListNode * temp2;

  while (temp1) {
    temp2 = temp1 -> prev;
    temp1 -> prev = temp1 -> next;
    temp1 -> next = temp2;
    temp1 = temp1 -> prev;
  }
  if (temp2) {
    startPoint = temp2 -> prev;
  }
  endPoint = curr;

}



/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  ListNode * currL = head_;
  ListNode * currR = head_;
  bool test = true;
  while (test) {
    //cout << "Line 166" << endl;
    for (int a = 0; a < n; a++) {
      if (currR -> next != NULL) {
        currR = currR -> next;
        //cout << "Line 170" << endl;
      }
      else {
        reverse(currL, currR);
        //cout << "Line 174" << endl;
        test = false;
        break;
      }
    }
    if (test == false) {
      break;
    }
    reverse(currL, currR);
    if (currR -> next != NULL) {
      //cout << "Line 183" << endl;
      currL = currR -> next;
      currR = currR -> next;
    }
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may *NOT* allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

  ListNode * curr = head_;
  for (int i = 0; i < length_; i++) {
    if (curr -> next != NULL) {
      if (i % 2 == 1 || i == 1) {
        //cout << i << endl;
        insertBack(curr -> data);
        curr -> prev -> next = curr -> next;
        curr -> next -> prev = curr -> prev;
      }
      curr = curr -> next;
    }
  }
  ListNode * temp = head_;
  while (temp -> next != NULL) {
    temp = temp -> next;
  }
  tail_ = temp;
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
 * splitPoint steps *after* start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function *SHOULD NOT* create *ANY* new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode * curr = head_;
  int test = true;
  for (int i = 0; i < splitPoint; i++) {
    if (curr -> next != NULL && splitPoint != 0) {
      curr = curr -> next;
      //cout << "Line 286" << endl;
    }
    else {
      test = false;
      return start;
    }
  }
  if (test == true){
    curr -> prev -> next = NULL;
    curr -> prev = NULL;
    //cout << "Line 296" << endl;
    return curr;
  }
  return start;
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
 * Helper function to merge two *sorted* and *independent* sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function *SHOULD NOT* create *ANY* new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  if (!first || !second) {
    return NULL;
  }
	ListNode * one = first;
	ListNode * two = second;

  if (first == second) {
    return second;
  }

  ListNode * finalList = first;

  bool test = one -> data < two -> data;
	if (!test) {
    finalList = second;
		two = second -> next;
    //cout << "Line 357" << endl;
	}
	else {
		one = first -> next;
	}

	ListNode * curr = finalList;

	while (one && two) {
		if (one -> data < two -> data || !two) {
      //cout << "Line 367" << endl;
      one -> prev = curr;
      curr -> next = one;
			curr = one;
			one = one -> next;
		}
		else {
      //cout << "Line 374" << endl;
      two -> prev = curr;
			curr -> next = two;
			curr = two;
			two = two -> next;
		}
	}

	if(!one) {
    //cout << "Line 383" << endl;
    two -> prev = curr;
		curr -> next = two;
	}
	else {
    //cout << "Line 388" << endl;
    one -> prev = curr;
		curr -> next = one;
	}
	second = NULL;
	return finalList;
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
  /// @todo Graded in MP3.2
  if (chainLength == 1) {
    return start;
  }
  ListNode * two = split(start, chainLength/2);
  return merge(mergesort(start, chainLength/2), mergesort(two, chainLength/2));
}
