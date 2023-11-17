//
// Interface Definition for the FixedArrayList Class as a derived class
// Author: Max Benson
// Date: 08/06/2021
//

#ifndef FIXEDARRAYLIST_H
#define FIXEDARRAYLIST_H

#include "ArrayList.h"

template <typename ItemType>
class FixedArrayList : public ArrayList<ItemType>  {
public:
    FixedArrayList (size_t capacity);

    FixedArrayList(const FixedArrayList&);
    const FixedArrayList<ItemType>& operator=(const FixedArrayList&);

private:
    bool GrowCapacity() override;
    void ShrinkCapacity() override;
};

/**
 * Default constructor
 * Creates an empty list.
 */
template <typename ItemType>
FixedArrayList<ItemType>::FixedArrayList(size_t capacity) {
    this->_array = new ItemType[capacity];
    this->_size = 0;
    this->_capacity = capacity;
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
const FixedArrayList<ItemType>& FixedArrayList<ItemType>::operator=(const FixedArrayList& rhs) {
    if (this != &rhs) {
        FixedArrayList<ItemType> copy(rhs);
        ItemType* swapArray;
        size_t swapSize;
        size_t swapCapacity;

        swapArray = this->_array;
        swapSize = this->_size;
        swapCapacity = this->_capacity;
        this->_array = copy._array;
        this->_capacity = copy._capacity;
        this->_size = copy._size;
        copy._array = swapArray;
        copy._size = swapSize;
        copy._capacity = swapCapacity;
    }
    return *this;
}

/**
 * Copy Constructor
 * Creates a deep copy of the list.
 * The running time of the whole method is O(N) time where N is the
 * length of the list
 * @param other the list to be copied
 */
template <typename ItemType>
FixedArrayList<ItemType>::FixedArrayList(const FixedArrayList& other) {
    this->_array = new ItemType[other._capacity];
    for (size_t i = 0; i < other._size; i ++) {
        this->_array[i] = other._array[i];
    }
    this->_size = other._size;
    this->_capacity = other._capacity;
}

/**
 * Grow the capacity of the array
 * Since this is a fixed array, this does nothing but return false
 * @return false
 */
template <typename ItemType>
bool FixedArrayList<ItemType>::GrowCapacity() {
    return false;
}

/**
 * Shrink the capacity of the array
 * Since this is a fixed array, this does nothing
 */
template <typename ItemType>
void FixedArrayList<ItemType>::ShrinkCapacity() {
}


#endif //FIXEDARRAYLIST_H
