/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

 #include <iostream>
 using namespace std;

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1 (modified)
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1 (modified)
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
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1 (modified);
  ListNode* next_;

  while(head_){
    next_ = head_->next;
    delete head_;
    head_= next_;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1 (modified)
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  head_ = newNode;
  if (tail_ == NULL) {
    tail_ = newNode;
  }

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
  /// @todo Graded in MP3.1 (modified)
  ListNode * newNode = new ListNode(ndata);

  if(tail_){
    tail_->next = newNode;
  }
  else{
    head_ = newNode;
  }
  newNode->prev = tail_;
  tail_ = newNode;

  length_++;
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
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  if(splitPoint == 0){
    return curr;
  }

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
    curr->prev->next = NULL;
    curr->prev = NULL;
    return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode** start = &head_;
  ListNode* first;
  ListNode* second;
  ListNode* third;

  while(*start){
    first = *start;
    if(!first){return;}
    second = (*start)->next;
    if(!second){return;}
    third = (*start)->next->next;
    if(!third){return;}

    second->prev = (*start)->prev;
    *start = second;

    first->prev = third;
    first->next = third->next;

    third->next = first;

    start = &(first->next);
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}


template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.
  if(startPoint == endPoint || !startPoint){
    return;
  }
  ListNode* temp = startPoint;
  ListNode* startPrev = startPoint->prev;
  ListNode* start = startPoint;
  ListNode* prev;
  ListNode* curr = startPoint;
  ListNode* lastNext = endPoint->next;

  while(curr != lastNext){
    temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    prev = curr;
    curr = temp;
  }

  startPoint->next = curr;
  prev->prev = startPrev;

  if(!startPrev){
    head_ = prev;
  }
  else{
    startPrev->next = prev;
  }

  if(!lastNext){
    tail_ = start;
  }
  else{
    lastNext->prev = start;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  int i = n;
  ListNode* curr = head_;
  ListNode* nextNode = head_;
  ListNode* temp;

  while(i <= length_){
    nextNode = curr;
    for(int x=0; x<n-1; x++){
      nextNode = nextNode->next;
    }
    temp = nextNode->next;
    reverse(curr, nextNode);
    curr = temp;
    i += n;

  }
  reverse(curr, tail_);
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
  /// @todo Graded in MP3.2
  ListNode* curr1 = first;
  ListNode* curr2 = second;
  ListNode* tempHead = first;

  if(first && second){
    if(curr1->data < curr2->data){
      tempHead = curr1;
      curr1 = curr1->next;
    }
    else{
      tempHead = curr2;
      curr2 = curr2->next;
    }
  }
  else{
    if(curr1){return curr1;}
    else if(curr2){return curr2;}
    else{return NULL;}

  }
  ListNode* curr = tempHead;

  while(curr1 && curr2){
    if(curr1->data < curr2->data){
      curr->next = curr1;
      curr1 = curr1->next;
    }
    else{
      curr->next = curr2;
      curr2 = curr2->next;
    }
    curr = curr->next;
  }

  while(curr1){
    curr->next = curr1;
    curr1 = curr1->next;
    curr = curr->next;
  }
  while(curr2){
    curr->next = curr2;
    curr2 = curr2->next;
    curr = curr->next;
  }

  first = tempHead;
  return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  if(chainLength == 1){
    return start;
  }
  ListNode *temp = start;
  for(int i=0; i<chainLength/2; i++){
    temp = temp->next;
  }
  int n1 = 0;
  int n2 = 0;

  ListNode* first = mergesort(start, chainLength/2);
  ListNode* second = mergesort(temp, chainLength-chainLength/2);

  ListNode* tempHead = first;

  if(first->data < second->data){
      tempHead = first;
      first = first->next;
      n1++;
    }
  else{
      tempHead = second;
      second = second->next;
      n2++;
  }

  ListNode* curr = tempHead;

  while(n1 < chainLength/2 && n2 < chainLength-chainLength/2){
    if(first->data < second->data){
      curr->next = first;
      first = first->next;
      n1++;
    }
    else{
      curr->next = second;
      second = second->next;
      n2++;
    }
    curr = curr->next;
  }

  while(n1 < chainLength/2){
    curr->next = first;
    first = first->next;
    curr = curr->next;
    n1++;
  }
  while(n2 < chainLength-chainLength/2){
    curr->next = second;
    second = second->next;
    curr = curr->next;
    n2++;
  }

  curr->next = NULL;
  return tempHead;
}
  /// @todo Graded in MP3.2
