cmake_minimum_required(VERSION 3.6)
project(AddressBook)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AffiliateClass.h AVLNode.h AVLNode.cpp AVLTree.h AVLTree.cpp Functions.h)
add_executable(AddressBook ${SOURCE_FILES})