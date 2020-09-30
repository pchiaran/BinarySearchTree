#ifndef __bst__
#define __bst__

#include "node.hpp"
#include "iterator.hpp"
#include <functional> 
#include <vector>

namespace BST{
	
//Binary search tree class with templated nodes (here as std::pair<K,V>) and comparison method (here std::less<K>)

template <typename K, typename V, typename cmp=std::less<K> >
class bst{
	
	//setting names for clarity
	using pair_type = typename std::pair<const K,V>;
	using node_type = typename NODE::node<pair_type>;
	using iterator  = typename ITER::BST_iterator<NODE::node<pair_type>,pair_type>; 
	using const_iterator = typename ITER::BST_iterator<NODE::node<pair_type>,const pair_type>;
		
  	
public:

	/******* CONSTRUCTOR, COPY AND MOVE SEMANTIC ********/

	bst() noexcept : op{}, head{nullptr} { std::cout << "BST default constructor" << std::endl; }		//default bst constructor. Comparison set to std::less and head to nullptr

	explicit bst(bst&&) noexcept = default;		//default move constructor

	bst& operator=(bst&&) noexcept = default;	//default move assignment

	explicit bst(const bst&);			//copy constructor with deep copy	

	bst& operator=(const bst& tree){		//copy assignment
		(*this).clear();
		bst tree_new{tree}; 
		*this = std::move(tree_new);
		return *this; }

	void __copy(const bst& t, std::unique_ptr<node_type>&);		//copy helper function

	
	/******* FUNCTIONS IMPLEMENTED HERE ********/

	
	//emplace function to insert a node with the syntax emplace(K,V). It uses the function insert
        std::pair<iterator,bool> emplace(const K& a, V& b) { return insert(pair_type{a,b}); }		//accepts lvalues
	std::pair<iterator,bool> emplace(K&& a, V&& b) { return insert(pair_type{a,b}); }		//accepts rvalues

	//use the private _begin() function to define three different public functions that returns an iterator or a const iterator to the leftmost node
	iterator begin() noexcept { return iterator{__begin()};}
	const_iterator begin() const noexcept{ return const_iterator{__begin()};}
	const_iterator cbegin() const noexcept{ return const_iterator{__begin()};} 			
	
	//use the private _end() function to define three different public functions that returns an iterator or a const iterator to the rightmost node
	iterator end() noexcept	{ return iterator{__end()};}
	const_iterator end() const noexcept { return const_iterator{__end()};}
	const_iterator cend() const noexcept { return const_iterator{__end()};}

	//function to clear the tree resetting head to nullptr
	void clear(){ this->head.reset(); }

	//subscripting operator to return the value of a node with a given key if present or inserting it and returning the default value. It uses the function insert to do the job
	V& operator[](K& x){ return insert(pair_type{x, V()}).first->second; }				//accepts lvalues
        V& operator[](K&& x){ return insert(pair_type{x, V()}).first->second; }				//accepts rvalues

        //stream operator to print the tree ordered using the comparison method
        friend std::ostream& operator<<(std::ostream& os, const bst& x){
                if(x.head.get() == nullptr) std::cout<<"The tree is empty"<<std::endl;
                for ( auto v : x ) std::cout << "Key = " << v.first << "\tValue = " << v.second  << std::endl; 
                return os; }


	/******* FUNCTIONS IMPLEMENTED IN bst.cpp ********/


        //function to insert a node passed as a pair_type if the key is not already present. In this case it returns an iterator pointing to the inserted node and a bool=true, otherwise it returns a pointer to the already present node and a bool=false
        std::pair<iterator, bool> insert(pair_type& x);  		//accept lvalues
	std::pair<iterator, bool> insert(pair_type&& x);		//accept rvalues


	//function to find a node with a given key. If the node is present it returns a pointer to the node, otherwise a pointer to end()
        iterator find(const K& x);
        const_iterator find(const K& x) const;          //const iterator version

    	//function to balance the tree by iteratively findingn the median of nested subtrees. It usese the function sortedArrayToBST
	void balance();

    	//helper function for balance. It map the tree to a sorted array using keys
	void sortedArrayToBST(std::vector<pair_type> data,int start, int end,bst &balanced_tree);

	//function to erase a node with a given key and to rejoin the tree structure. It uses the private functions erase_head() and erease_generic()
        void erase(const K& x);


private:

        /**** DATA MEMBERS ****/

        cmp op;                                 //less comparison method op(x,y) from <functional>. Returns true if x<y
        std::unique_ptr<node_type> head;        //pointer to the head of the tree

        /******* FUNCTIONS IMPLEMENTED HERE ********/

        //function to find the leftmost node in the tree
        node_type* __begin() const noexcept{
                if (!head) return nullptr;              //if the tree is empty return nullptr
                node_type* t = head.get();              //otherwise travel to the left untile you reach the leftmost node
                while(t->left) t=t->left.get();
                return t; }
        //function to find the rightmost node in the tree
        node_type* __end() const noexcept {
                node_type* t = head.get();
                if(t == nullptr) return t;              //if the tree is empty return nullptr
                else{                                   //otherwise travel to the left untile you reach the rightmost node
                        while(t) t=t->right.get();
                        return t; }
                }

        /******* FUNCTIONS IMPLEMENTED IN bst.cpp ********/


        //helper functions to erase nodes
        void erase_head();
        void erase_generic(iterator it_erase);


};

}
#endif
#include "../src/bst.cpp"
