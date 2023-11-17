//
// Interface Definition for a VariableArrayList Class derived from a base class
// Author: Max Benson
// Date: 08/06/2021
//

#ifndef VARIABLEARRAYLIST_H
#define VARIABLEARRAYLIST_H

#include "ArrayList.h"

template <typename ItemType>
class VariableArrayList : public ArrayList<ItemType>  {
public:
    VariableArrayList();

    VariableArrayList(const VariableArrayList&);
    const VariableArrayList& operator=(const VariableArrayList&);

private:
    bool GrowCapacity() override;
    void ShrinkCapacity() override;
};

/**
 * Default constructor
 * Creates an empty list.
 */
template <typename ItemType>
VariableArrayList<ItemType>::VariableArrayList() {
    this->_array = new ItemType[1];
    this->_size = 0;
    this->_capacity = 1;
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
const VariableArrayList<ItemType>& VariableArrayList<ItemType>::operator=(const VariableArrayList& rhs) {
    if (this != &rhs) {
        VariableArrayList copy(rhs);
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
VariableArrayList<ItemType>::VariableArrayList(const VariableArrayList& other) {
    this->_array = new ItemType[other._capacity];
    for (size_t i = 0; i < other._size; i ++) {
        this->_array[i] = other._array[i];
    }
    this->_size = other._size;
    this->_capacity = other._capacity;
}

/**
 * Doubles the size of the array allocation
 * This is meant to be called when array is full.
 * @return success
 */
template <typename ItemType>
bool VariableArrayList<ItemType>::GrowCapacity() {
    ItemType* newArray;

    assert(this->_size == this->_capacity);
    newArray = new ItemType[2*this->_capacity];
    for (size_t i = 0; i < this->_size; i ++) {
        newArray[i] = this->_array[i];
    }
    delete[] this->_array;
    this->_array = newArray;
    this->_capacity *= 2;
    return true;
}

/**
 * Check if array allocation should be reduced
 * If using less than 1/4 capacity, halves the size of allocation.
 */
template <typename ItemType>
void VariableArrayList<ItemType>::ShrinkCapacity() {
    if (this->_size > 0 && 4*this->_size <= this->_capacity) {
        ItemType* newArray;

        newArray = new ItemType[this->_capacity/2];
        for (size_t i = 0; i < this->_size; i ++) {
            newArray[i] = this->_array[i];
        }
        delete[] this->_array;
        this->_array = newArray;
        this->_capacity /= 2;
    }
}


#endif //VARIABLEARRAYLIST_H
