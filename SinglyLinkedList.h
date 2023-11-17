//
// Interface Definition for the SinglyLinkedList Class
// Author: Azhar Amir Kimanje
// Date: 21/09/2021;
//

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
using std::ostream;

#include "LinkedList.h"

//Declaration of the SinglyLinkedList class
template <typename ItemType>
class SinglyLinkedList : public LinkedList<ItemType>  {
public:
    //Default constructor
    SinglyLinkedList();
    // Rule of Three
    ~SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList&);
    const SinglyLinkedList& operator=(const SinglyLinkedList&);

    // List methods implemented at this level in class hierarchy
    bool Insert(size_t position, const ItemType& item) override;
    bool Remove(size_t position, ItemType& item) override;
    bool CheckConsistency() const override;



private:
    // Node class for Singly linked lists
    class SLLNode : public LinkedList<ItemType>::Node {
    public:
        typename LinkedList<ItemType>::Node* Next() const {
            return next;
        }
        SLLNode* next;
    };
    // List method implemented at this level of class hierarchy
    typename LinkedList<ItemType>::Node* Head() const override {
        return _head;
    }

    typename LinkedList<ItemType>::Node* GetPtrToNodeAtPosition(size_t position) const override;

    // Method only used in this class
    SLLNode* GetPtrToSLLNodeAtPosition(size_t position) const;

    // Start of list
    SLLNode* _head;
};

template <typename ItemType>
typename LinkedList<ItemType>::Node* SinglyLinkedList<ItemType>::GetPtrToNodeAtPosition(size_t position) const {
    return GetPtrToSLLNodeAtPosition(position);
}


/**
 * Default constructor
 * Creates an empty list.
 */
template <typename ItemType>
SinglyLinkedList<ItemType>::SinglyLinkedList() {
    _head = nullptr;
    this->_size = 0;
}

/**
 * Destructor
 * Frees the dynamic memory allocated for the list
 */
template <typename ItemType>
SinglyLinkedList<ItemType>::~SinglyLinkedList() {
    this->Clear();
}

/**
 * Copy Constructor
 * Creates a deep copy of the list as it traverses through
 * the other list.  Because we keep a pointer to the link field
 * of the last node of the new list as we go, we can create
 * a new node and append it to the end of the list in O(1) time.
 * The running time of the whole method is O(N) time where N is the
 * length of the list
 * @param other the list to be copied
 */
template <typename ItemType>
SinglyLinkedList<ItemType>::SinglyLinkedList(const SinglyLinkedList& other) {
	SLLNode* prev = nullptr;

	_head = nullptr;
    for (SLLNode* nodePtr = other._head; nodePtr != nullptr; nodePtr = nodePtr->next ) {
		SLLNode* newNode;

		newNode = new SLLNode;
        newNode->item = nodePtr->item;
        newNode->next = nullptr;

		if (prev == nullptr) {
			_head = newNode;
		}
		else {
			prev->next = newNode;

		}
        prev = newNode;
	}
    this->_size = other._size;
}

/**
 * Copy assignment operator
 * Enables deep copy assignment using the operator = overload.
 * Uses the copy constructor to copy the rhs.  Then swaps internals of
 * the copy with this.  By doing it this way, the old contents
 * of this will be automatically freed when the method finishes.
 * The running time of this method is the same as the copy
 * constructor , i.e. O(N)
 * @param rhs the object to be copied into this
 * @return this to enable cascade assignments
 */
template <typename ItemType>
const SinglyLinkedList<ItemType>& SinglyLinkedList<ItemType>::operator=(const SinglyLinkedList& rhs) {
    if (this != &rhs) {
        SinglyLinkedList copy(rhs);
        SLLNode *swapHead;
        size_t swapSize;

        swapHead = _head;
        swapSize = this->_size;
        _head = copy._head;
        this->_size = copy._size;
        copy._head = swapHead;
        copy._size = swapSize;
    }
    return *this;
}

/**
 * Get  the item at a specified position
 * This method runs in O(1) when position = 0 or _size
 * otherwise its running time is O(position)
 * @param position the position of the element to retrieve.
 * @param item the item found at position
 * @return a pointer to the item if the position is valid, nullptr otherwise
 */


/**
 * Searches for the position of the first matching item in the list starting
 * at position "start".  The method performs a linear search for the item.
 * If the element is found it returns the position, if it is not found it
 * returns -1.
 * The running time of this method depends on where the search starts
 * and where the item is found (if it is found)
 * @param item the object that the client is searching for.
 * @param start position at which to start the search
 * @return the position of the element if found, -1 otherwise.
 */



/**
 * Inserts an element into a given position so long as the position is valid.
 * This method runs in O(position) time.
 * @param item what the client wants to insert into the list
 * @param position the position where the element is to be inserted
 * @return true if it was possible to insert, false otherwise.
 */



/**
 * Removes the item at position, so long as the position is valid. The item previously
 * stored in the list is returned in the supplied parameter.
 * This method runs in O(position) time.
 * @param position the position of the element to be removed.
 * @param item the item previously stored in the list
 * @return true if node could be deleted, false if position at end of list or invalid,
 */
/**
 * Replace  the item at a specified position
 * @param position the position of the element to retrieve.
 * @param item the new item to insert in the old one's place
 * @return true if valid position given, false otherwise
 */


/**
 * Swap elements in specified positions
 * @param position1 the position of the first element
 * @param position2 the position of the second element
 * @return true if valid positions were given, false otherwise
 */


/**
 * Checks if list has correct number of nodes and is linked properly
 * This method runs in O(N) time where N is the number of items in list
 * @return true if list consistent, false otherwise
 */
template <typename ItemType>
bool SinglyLinkedList<ItemType>::CheckConsistency() const {
    size_t position;
    SLLNode* ptr;

    for (position = 0, ptr = _head; position < this->_size && ptr != nullptr; position ++, ptr = ptr->next) {
    }
    return position == this->_size && ptr == nullptr;
};

/**
 * Output list to an ostream
 */

/**
 * Does the actual work of GetPtrToNodeAtPosition returning a SLLNode pointer
 * This method is used for Insert, Remove, and GetPtrToNodeAtPosition
 * @param position index in list between 0 and number of items-1
 * @return pointer to node corresponding to that position
 */
template <typename ItemType>
typename SinglyLinkedList<ItemType>::SLLNode* SinglyLinkedList<ItemType>::GetPtrToSLLNodeAtPosition(size_t position) const {
    SLLNode* ptr;
    size_t curPosition;

    assert(position  < this->_size);
    for (curPosition = 0, ptr = _head ; curPosition < position; curPosition ++, ptr = ptr->next ) {
    }
    return ptr;
}

template<typename ItemType>
bool SinglyLinkedList<ItemType>::Insert(size_t position, const ItemType &item) {
    if(position >this->_size){
        return false;
    } else {
        SLLNode* newNode;
        newNode= new SLLNode;
        newNode->item=item;
        if(0==position) {
            newNode->next=_head;
            _head=newNode;

        } else{
            SLLNode* prevNode;
            prevNode= GetPtrToSLLNodeAtPosition(position-1);
            newNode->next=prevNode->next;
            prevNode->next=newNode;

        }
        this->_size++;
        return true;

    }
}

template<typename ItemType>
bool SinglyLinkedList<ItemType>::Remove(size_t position, ItemType &item) {
    if(position >=this->_size){
        return false;
    } else {
        SLLNode* nodeToZap;

        if(0==position) {
            nodeToZap=_head;
            _head=_head->next;

        } else{
            SLLNode* prevNode;
            prevNode= GetPtrToSLLNodeAtPosition(position-1);
            nodeToZap =prevNode->next;
            prevNode->next=nodeToZap->next;

        }
        item=nodeToZap->item;
        delete nodeToZap;
        this->_size--;
        return true;

    }
}


#endif //SINGLYLINKEDLIST_H
