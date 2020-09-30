# Binary search tree implementented in c++

# Compilation and run
To compile the code just type in command line

make

This will compile the two .cpp files "main.cpp" and "src/bst.cpp" including all dependencies in the folder "include". The procedure will produce an executable called "bst". To run the code type

./bst

This will produce an output on screen with all the tests on implemented functions. The output should be self-explainatory of what is being tested and what should be the output.

To recompile the code you need to first type

make clean

and than repeat the compilation.

# Code details
The Binary Serach Tree is implemented in the following way.

There are three header files in the folder "include" and one in the folder "src"

- In /include/node.hpp you can find the definition and implementation of the class node used as building blocks for the tree. Each node stores a templated value (here implemented as an std::pair<Key,Value>) and three pointers to other nodes which are the parent node and the right and left children.

- In /include/iterator.hpp you can find the definition and implementation of the class iterator, used to navigate throghout the tree following the key order. The iterator is templated on the node and on the node value and store a pointer to a node.

- In /include/bst.hpp there is the definition and part of the implementation of the class binary search tree. The tree has two data members which are the comparison method for sorting the keys and a pointer to the head node and it is templated on the key and value types and also on the comparison method, which is here defaulted with std::less. All the members functions allow us insert, erase and access the bst nodes, as well as initializing, copying and moving a tree. Some small functions are directly implemented here while the other implementations are in src/bst.cpp

- In src/bst.cpp you can find the implementation of the bst. Each function has a short explanation on the top and for more complicated functions the implementation is explained step by step in the code.
