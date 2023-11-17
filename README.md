# lab2-doubly-linked-list-f21

In this lab assignment, there will be two distinct stages of your work.  

The first stage will be to create an abstract `LinkedList` class that is derived from `List`, and then to modify the `SinglyLinkedList` class so it is a subclass of `LinkedList`.  

The second stage will be to implement a new `DoublyLinkedList` class which is derived from `LinkedList`.

# Stage 1: 

Here are the instructions you should follow:

## LinkedList.h

### Declare a new template class called `LinkedList` which is derived from `List<ItemType>`

#### In the public section

1. Declare the following methods to override the same methods declared in the `List` class
- `Get`
- `Find`
- `Replace`
- `Swap`
- `Clear`

#### In the protected section 

1. Declare the following abstract `Node` class
  
```
  class Node {
  public:
      ItemType item;
      virtual Node* Next() const = 0; 
  };
```

2. Declare the following method to override the same method in the `List` class:

  `ToOstream`

3. Declare two virtual methods which are not implemented in this class:

```
  Node* GetPtrToNodeAtPosition(size_t position) const
  Node* Head() const
```
### Implement the following methods

1. Move the implementations of `Get`, `Find`, `Replace`, `Swap`, `Clear`, and `ToOstream` from `SinglyLinkedList.h` and place them into `LinkedList.h`
2. Since they are now going to be methods of the `LinkedList` class make these changes (please try to understand why you are making these changes).

- `SinglyLinkedList` => `LinkedList`
- `SLLNode` => `Node`
- `GetPtrToSLLNodeAtPosition` => `GetPtrToNodeAtPosition`
- `_head` => `Head()`
- `ptr->next` => `ptr->Next()`

## SinglyLinkedList.h

### In the declaration of the `SinglyLinkedList` class:

#### Public section

1. Change `SinglyLinkedList` to be derived from `LinkedList<ItemType>` instead of `List<ItemType>`
2. Remove declarations of the six methods whose implementations you moved to the `LinkedList` class.

#### Private section

1. Change the declaration of the existing `SLLNode` class to this:

```
// Node class for Singly linked lists
class SLLNode : public LinkedList<ItemType>::Node {
public:
    typename LinkedList<ItemType>::Node* Next() const { return next; }
    SLLNode* next;
};
```
2.  Declare that you are overriding the two new virtual methods you added to the `LinkedList` class.  Here's the syntax you should use:

```
typename LinkedList<ItemType>::Node* Head() const override { return _head; }
typename LinkedList<ItemType>::Node* GetPtrToNodeAtPosition(size_t position) const override;
```
### Add the following method implementation

```
template <typename ItemType>
typename LinkedList<ItemType>::Node* SinglyLinkedList<ItemType>::GetPtrToNodeAtPosition(size_t position) const {
    return GetPtrToSLLNodeAtPosition(position);
}
```

##  Make sure it works

Make sure your program and passes the validation tests

# Stage 2: 

You are going to implement a doubly linked list that is circularly linked.  See the comment at the top of the file `DoublyLinkedList.h`:

```
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
```

Here are the steps you can follow:

## DoublyLinkedList.h

### Declare a new template class called `DoublyLinkedList` which is derived from `LinkedList<ItemType>`

The layout of the declaration section should be very similar to what you now have for the `SinglyLinkedList` class.

#### Public section

1. Declare the following standard methods:

= default constructor
- destructor (should be declared `override`)
- copy constructor
- copy assignment operator


2. Declare the following overrides of methods of `List`

- `Insert`
- `Remove`
- `CheckConsistency`

#### Private section

1. Declare the node class

```
class DLLNode : public LinkedList<ItemType>::Node {
    public:
        typename LinkedList<ItemType>::Node* Next() const { return next; }
        DLLNode* next;
        DLLNode* prev;
    };
```
2.  Declare that you are overriding the two new virtual methods you added to the `LinkedList` class.  Here's the syntax you should use:

```
typename LinkedList<ItemType>::Node* Head() const override { return _head; }
typename LinkedList<ItemType>::Node* GetPtrToNodeAtPosition(size_t position) const override;
```

3.  Declare a node positioning method

```
DLLNode* GetPtrToDLLNodeAtPosition(size_t position) const;
```

4.  Declare the head of the list

```
DLLNode* _head;
```

### Method implementation

1.  The `CheckConsistency` method has already been implemented for you.  You should not modify this method, but you should remove line 32 which reads
`#if defined(DOUBLY_LINKED_IMPLEMENTED)`
and line 65 which reads
`#endif`

2.  You need to implement

- Default constructor
- Destructor
- Copy constructor
- Copy assignment operator
- Insert
- Remove
- GetPtrToNodeAtPosition
- GetPtrToDLLNodeAtPosition

You can adapt many of the corresponding implementations in `SinglyLinkeList` class with little or no modification, but you will have to pay special attention to the following:

- Copy constructor: make sure it runs in O(N) time
- Insert: make sure that insert at position 0 and position Size() run in O(1) time
- Remove: make sure that remove at position 0 and position Size()-1 run in O(1) time
- GetPtrToDLLNodeAtPosition:  this method should be able to position to nodes at position 0, Size()-2, and Size()-1 in O(1) time

In order for your main program to exercise the `DoublyLinkedList` class, you will need to change line 23 of `main.cpp`, which is currently blank, to `#define DOUBLY_LINKED_IMPLEMENTED`, and you will also need to change line 11 of `perftest.cpp` to `#define DOUBLY_LINKED_IMPLEMENTED`.

##  Make sure it works

Make sure your code compiles and runs, passing the validation tests.
Then run it on the command line with the appropriate -perf arguemtns to check that you are inserting at start, inserting at end, removing the first item, removing the last item, getting the first time, and getting the last item in O(1).

Finally, run it with `valgrind --leak-check=full` to make sure it does not report any memory problems.




`
