cmake_minimum_required(VERSION 3.10)
project(DoublyLinkedList)

set(CMAKE_CXX_STANDARD 14)

add_executable(DoublyLinkedList main.cpp perftest.cpp DoublyLinkedList.h SinglyLinkedList.h LinkedList.h FixedArrayList.h VariableArrayList.h List.h)