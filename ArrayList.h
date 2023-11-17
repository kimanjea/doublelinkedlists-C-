//
// Interface Definition for the ArrayList Base Class
// Author: Max Benson
// Date: 08/06/2021
//

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
using std::ostream;

#include "List.h"

template <typename ItemType>
class ArrayList : public List<ItemType> {
public:
    ~ArrayList() override;

    // Iteration
    typedef const ItemType* iterator;
    iterator begin() const { return &_array[0]; };
    iterator end() const { return &_array[this->_size]; };

    // Other methods
    bool Get(size_t position, ItemType& item) const override;
    int Find(const ItemType& item, size_t start = 0) const override;
    bool Insert(size_t position, const ItemType& item) override;
    bool Replace(size_t position, const ItemType& item) override;
    bool Swap(size_t position1, size_t position2) override;
    bool Remove(size_t position, ItemType& item) override;
    void Clear() override;

    bool CheckConsistency() const override;

protected:
    // Stream output
    void ToOstream(ostream& os) const override;

    // Resizeabilty
    virtual bool GrowCapacity() = 0;
    virtual void ShrinkCapacity() = 0;

    ItemType* _array;
    size_t _capacity;
};

/**
 * Destructor
 * Frees the dynamic memory allocated for the list
 */
template <typename ItemType>
ArrayList<ItemType>::~ArrayList() {
    delete[] _array;
}

/**
 * Get  the item at a specified position
 * This method runs in O(1) time.
 * @param position the position of the element to retrieve.
 * @param item the item found at position
 * @return true if valid position given, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::Get(size_t position, ItemType& item) const {
    if (position < this->_size) {
        item = _array[position];
        return true;
    }
    return false;
}

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
template <typename ItemType>
int ArrayList<ItemType>::Find(const ItemType& item, size_t start)  const {
    for (size_t i = start; i < this->_size; i++) {
        if (_array[i] == item) {
            return i;
        }
    }
    return -1;
}

/**
 * Inserts an element into a given position so long as the position is valid
 * and the list is not filled to capacity.
 * THe running time of inserting at the start is O(N), it's O(1) if you are
 * inserting at the end.
 * @param item what the client wants to insert into the list
 * @param position the position where the element is to be inserted
 * @return true if it was possible to insert, false otherwise.
 */
template <typename ItemType>
bool ArrayList<ItemType>::Insert(size_t position, const ItemType& item) {
    if (position > this->_size) {
        return false;
    }
    else
    {
        if (this->_size == _capacity && !GrowCapacity()) {
            return false;
        }

        // Shift out elements to make room for insertion
        for (size_t i = this->_size; i > position; i --) {
            _array[i] = _array[i-1];
        }
        // Insert the element
        _array[position] = item;
        this->_size ++;
        return true;
    }
}

/**
 * Replace  the item at a specified position
 * This method runs in O(1) time.
 * @param position the position of the element to retrieve.
 * @param item the new item to insert in the old one's place
 * @return true if valid position given, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::Replace(size_t position, const ItemType& item) {
    if (position < this->_size) {
        _array[position] = item;
        return true;
    }
    return false;
}

/**
 * Swap elements in specified positions
 * This method runs in O(1) time.
 * @param position1 the position of the first element
 * @param position2 the position of the second element
 * @return true if valid positions were given, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::Swap(size_t position1, size_t position2) {
    if (position1 < this->_size && position2 < this->_size) {
        ItemType tmp;

        tmp = _array[position1];
        _array[position1] = _array[position2];
        _array[position2] = tmp;
        return true;
    }
    return false;
}

/**
 * Removes the item at position, so long as the position is valid. The item previously
 * stored in the list is returned in the supplied parameter.
 * THe running time of removing the first element is  O(N), it's O(1) if you are
 * removing the last element.
 * @param position the position of the element to be removed.
 * @param item the item previously stored in the list
 * @return true if node could be deleted, false if position at end of list or invalid,
 */
template <typename ItemType>
bool ArrayList<ItemType>::Remove(size_t position, ItemType& item) {
    if (position >= this->_size) {
        return false;
    }
    else {
        item = _array[position];

        // Close up the gap
        for (size_t i = position; i < this->_size-1; i ++) {
            _array[i] = _array[i+1];
        }
        this->_size--;

        ShrinkCapacity();

        return true;
    }
}

/**
 * Clear the list
 * and then resetting _head to nullptr.
 * This method runs in O(1) time
 * There is no need to free the string values
 * that will occur when the class destructs
 */
template <typename ItemType>
void ArrayList<ItemType>::Clear() {
    this->_size = 0;
}

/**
 * Checks if list data structure appears to be consistent
 * @return true if list consistent, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::CheckConsistency() const {
    return this->_size <= _capacity;
}


/**
 * Output list to an ostream
 */
template <typename ItemType>
void ArrayList<ItemType>::ToOstream(ostream& os) const {
    os << "[";
    for (iterator iter = begin(); iter != end(); iter++) {
        if (iter != begin()) {
            os << ", ";
        }
        os << *iter;
    }
    os << "]";
}


#endif //ARRAYLIST_H
