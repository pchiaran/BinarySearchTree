#ifndef __NODE_CLASS_HPP__
#define __NODE_CLASS_HPP__

#include <memory> 
#include <iostream>
#include <utility> 

namespace BST {
    template<typename K, typename V, typename cmp>
    class bst; }

namespace ITER {
    template<typename node, typename vtype>
    class BST_iterator; }


namespace NODE{

//template to define a templated node class. Each node has a value of type T and three pointers, the 'right' and 'left' pointers to children nodes and the 'up' one to the parent node

	template<typename T>
	class node{

		T value;				//templated value of the node
		std::unique_ptr<node<T>> left;		//pointer to the left child
		std::unique_ptr<node<T>> right;		//pointer to the right child
		node<T>* upper;				//pointer to the parent. Cannot use unique_ptr here

		//user-defined default constructor. It initializes the node value to the default value depending on type T and the three node's pointers to nullptr
		node() noexcept : value{}, left{nullptr}, right{nullptr}, upper{nullptr} {} 

    		//custom constructor to initialize a node using an lvalue. This copies an exixsting node
		node(const T& v, node<T>* up) noexcept : value{v}, left{nullptr}, right{nullptr}, upper{up} {}

		//custom constructor to initialize a node using an rvalue
		node(T&& v, node<T>* up) noexcept : value{std::move(v)}, left{nullptr}, right{nullptr}, upper{up} {}

		//set bst and iterator as friend classes to access node's private members in them
		template<typename K, typename V, typename cmp>
		friend	class BST::bst;

		template<typename node, typename vtype>
		friend class ITER::BST_iterator;
};

}
#endif 
