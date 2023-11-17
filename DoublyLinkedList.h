//
// Interface Definition for the DoublyLinkedList Class
//
// Since the class is templated, the methods implementation must be
// included in this file.  You are to put your method implementations
// in the file DLL_Implementation.h."  No modifications are allowed to
// made to this file
//
// Author: Azhar Kimanje
// Date: 18/09/2021
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

// In this implementation the doubly linked list is CIRCULARLY linked.
// 1) When the list is empty, _head is nullptr
// 2) Otherwise
//      a) When the list has N element, the list has exactly N nodes.
//         In particular _head points to a node containing the first
//         element of the list
//      b) The list is CIRCULARLY linked, which means the prev
//         field of _head points to the node containing the last node
//         in the list, the next field of the node containing the
//         last node of the list points to _head

#include <iostream>
using std::ostream;
#include "list"
#include "LinkedList.h"
#include <string>

template <typename ItemType>

class DoublyLinkedList : public LinkedList<ItemType> {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList&);
    const DoublyLinkedList& operator=(const DoublyLinkedList&);
    bool Insert(size_t position, const ItemType& item) override;
    bool Remove(size_t position, ItemType& item) override;
    bool CheckConsistency() const override;

private:
    class DLLNode : public LinkedList<ItemType>::Node {
    public:
        typename LinkedList<ItemType>::Node* Next() const { return next; }
        DLLNode* next;
        DLLNode* prev;
    };
    typename LinkedList<ItemType>::Node* Head() const override { return _head; }
    typename LinkedList<ItemType>::Node* GetPtrToNodeAtPosition(size_t position) const override;

    DLLNode* GetPtrToDLLNodeAtPosition(size_t position) const;
    DLLNode* _head;

};


template<typename ItemType>
typename LinkedList<ItemType>::Node *DoublyLinkedList<ItemType>::GetPtrToNodeAtPosition(size_t position) const {

    return GetPtrToDLLNodeAtPosition(position);
}


template<typename ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList(const DoublyLinkedList& other) {
    DLLNode* prev = nullptr;
    _head = nullptr;
    this->_size=0;

    DLLNode* nodePtr =other._head;

    for (size_t i=0; i<other.Size(); i++) {
        DLLNode* newNode;
        newNode = new DLLNode;

        if (i == 0) {
            newNode->item = nodePtr->item;
            _head = newNode;
            _head->prev = _head;
            _head->next = _head;
        }
        else {
            DLLNode* prevNode;
            prevNode= GetPtrToDLLNodeAtPosition(i-1);
            newNode->item=nodePtr->item;
            prevNode->next = newNode;
            newNode->prev=prevNode;
            newNode->next= _head;
            _head->prev=newNode;
        }
        nodePtr=nodePtr->next;
        this->_size++;
    }
    this->_size = other._size;
}

template<typename ItemType>
const DoublyLinkedList<ItemType>& DoublyLinkedList<ItemType>::operator=(const DoublyLinkedList& rhs) {
    if (this != &rhs) {
        DoublyLinkedList copy(rhs);
        DLLNode *swapHead;
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

template<typename ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList() {
    _head=nullptr;
    this->_size = 0;


}

template<typename ItemType>
DoublyLinkedList<ItemType>::~DoublyLinkedList() {

this->Clear();
}

template<typename ItemType>
bool DoublyLinkedList<ItemType>::Insert(size_t position, const ItemType &item) {
    if (position > this->_size) {
        return false;
    } else {
        DLLNode *newNode;
        newNode = new DLLNode;
        newNode->item = item;
        if (0 == position) {
            DLLNode* prevNode;
            DLLNode* nextNode;

            if (this->_size > 0) {

                prevNode= GetPtrToDLLNodeAtPosition(this->_size-1);
                newNode->next=_head;
                _head= newNode;
                nextNode=_head->next;
                nextNode->prev=_head;
                _head->prev=prevNode;
                prevNode->next=_head;
                /*prevNode=_head->prev;
                _head->prev=newNode;
                newNode->next = _head;
                _head = newNode;
                newNode->prev=prevNode;
                prevNode->next = _head;

*/
            } else {
                _head = newNode;
                _head->next = _head;
                _head->prev = _head;
            }
        }  else {
                DLLNode *prevNode;
                DLLNode *nextNode;

                prevNode = GetPtrToDLLNodeAtPosition(position - 1);
                newNode->next=prevNode->next;
                nextNode=prevNode->next;
                nextNode->prev = newNode;
                prevNode->next = newNode;
                newNode->prev = prevNode;

            }
        this->_size++;
        return true;

    }
}

template<typename ItemType>
bool DoublyLinkedList<ItemType>::Remove(size_t position, ItemType &item) {
    if(position >=this->_size){
        return false;
    } else {
        DLLNode* nodeToZap;

        if(0==position) {
            DLLNode* prevNode;
             if(this->_size>1) {
            prevNode=_head->prev;
            nodeToZap=_head;
            _head=_head->next;
            _head->prev=prevNode;
            prevNode->next=_head;
             }
             else {
                 nodeToZap=_head;
                 _head=nullptr;
             }

        } else{
               DLLNode* prevNode;
               DLLNode* nextNode;

            prevNode= GetPtrToDLLNodeAtPosition(position-1);
            nodeToZap =prevNode->next;
            prevNode->next=nodeToZap->next;
            nextNode=nodeToZap->next;
            nextNode->prev=prevNode;

        }

        item=nodeToZap->item;
        delete nodeToZap;
        this->_size--;
        return true;

    }
}


/**
 * Checks if list has correct number of nodes and is linked properly
 * This method runs in O(N) time where N is the number of items in list
 * @return true if list consistent, false otherwise
 */
template <typename ItemType>
bool DoublyLinkedList<ItemType>::CheckConsistency() const {
    if (this->_size == 0) {
        return _head == nullptr;
    }
    else if (this->_size == 1) {
        return _head->next == _head && _head->prev == _head;
    }
    else {
        size_t position;
        DLLNode* ptr;

        //Walk forward
        for (position = 1, ptr = _head->next; position < this->_size && ptr != _head; position ++, ptr = ptr->next) {
        }
        if (position != this->_size || ptr != _head)  {
            return false;
        }
        //Walk backward
        for (position = 1, ptr = _head->prev; position < this->_size && ptr != _head; position ++, ptr = ptr->prev) {
        }
        if (position != this->_size || ptr != _head)  {
            return false;
        }
        return true;
    }
}

template<typename ItemType>
typename DoublyLinkedList<ItemType>::DLLNode *DoublyLinkedList<ItemType>::GetPtrToDLLNodeAtPosition(size_t position) const {
    DLLNode* ptr;
    size_t curPosition;

    assert(position  < this->_size);
    for (curPosition = 0, ptr = _head ; curPosition < position; curPosition ++, ptr = ptr->next ) {
    }
    return ptr;
}


#endif //DOUBLYLINKEDLIST_H
