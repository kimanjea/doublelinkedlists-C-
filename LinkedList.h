//
// Created by Azhar Kimanje on 21/9/2021.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "List.h"

template <typename ItemType>
class LinkedList:public List<ItemType> {
public:

    virtual bool Get(size_t position, ItemType& item) const;
    virtual int Find(const ItemType& item, size_t start = 0) const;
    virtual bool Replace(size_t position, const ItemType& item);
    virtual bool Swap(size_t position1, size_t position2);
    virtual void Clear();


protected:
    class Node {
    public:
        ItemType item;
        virtual Node* Next() const = 0;
    };

     void ToOstream(ostream& os) const override;

    virtual Node* GetPtrToNodeAtPosition(size_t position) const;

    virtual Node* Head() const;

};
template <typename ItemType>
bool LinkedList<ItemType>::Get(size_t position, ItemType& item) const {
    if (position < this->_size) {
        Node* ptr = GetPtrToNodeAtPosition(position);

        item = ptr->item;
        return true;
    }
    return false;
}
template <typename ItemType>
int LinkedList<ItemType>::Find(const ItemType& item, size_t start)  const {
    if (start < this->_size) {
        Node *ptr;

        // First navigate to start position
        ptr = GetPtrToNodeAtPosition(start);

        // Now search for the item, returning its position if found
        for (int curPosition = start; curPosition < this->_size; ptr = ptr->Next(), curPosition++) {
            if (ptr->item == item) {
                return curPosition;
            }
        }
    }
    return -1;
}
template <typename ItemType>
bool LinkedList<ItemType>::Replace(size_t position, const ItemType& item) {
    if (position < this->_size) {
        Node* ptr = GetPtrToNodeAtPosition(position);

        ptr->item = item;
        return true;
    }
    return false;
}
template <typename ItemType>
bool LinkedList<ItemType>::Swap(size_t position1, size_t position2) {
    if (position1 < this->_size && position2 < this->_size) {
        Node* ptr1 = GetPtrToNodeAtPosition(position1);
        Node* ptr2 = GetPtrToNodeAtPosition(position2);
        ItemType tmp;

        tmp = ptr1->item;
        ptr1->item = ptr2->item;
        ptr2->item = tmp;
        return true;
    }
    return false;
}
template <typename ItemType>
void LinkedList<ItemType>::Clear() {
    size_t numberToRemove = this->_size;

    for (size_t i = 0; i < numberToRemove; i ++) {
        ItemType item;

        this->Remove(0, item);
    }
}

template<typename ItemType>
typename LinkedList<ItemType>::Node *LinkedList<ItemType>::GetPtrToNodeAtPosition(size_t position) const {
    return nullptr;
}

template<typename ItemType>
typename LinkedList<ItemType>::Node *LinkedList<ItemType>::Head() const {
    return nullptr;
}

template<typename ItemType>
void LinkedList<ItemType>::ToOstream(ostream &os) const {
    Node* ptr;
    size_t curPosition;

    os << "[";
    for(curPosition=0,ptr = Head(); curPosition<this->_size ;curPosition++, ptr=ptr->Next()){
        if(curPosition!=0){
        os << ", ";
        }
        os <<ptr->item;
    }
    os << "]";

}

#endif //LINKEDLIST_H
