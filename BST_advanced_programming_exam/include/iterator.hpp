#ifndef __ITERATOR_BST_HPP__
#define __ITERATOR_BST_HPP__


namespace BST {
    template<typename K, typename V, typename cmp>
    class bst; }


namespace ITER{

//Iterator class to move in the tree. The iterator travels the tree by following the keys order. Incrementing the iterator will move the pointer from the current node to the node with the next key in ascending order. To do this it uses right and left children in the proper way in the operator ++

	template <typename node,typename vtype>
	class BST_iterator{
	 

	/**** DATA MEMBERS ****/

	  node* current;
	
public:
	  
	 /**** CONSTRUCTOR ***/

	  explicit BST_iterator(node* x) noexcept : current{x} {}


	  //Dereference operator to obtain the node value 
	  vtype& operator*() const noexcept { return current -> value; } 

	   // Arrow operator to obtain a pointer to the node value
	  vtype* operator->() const noexcept { return &(*(*this)); } 

	  //Preincrement operator. We need to find the smallest key in the right subtree of the current node. If there is no right subtree you must go up until either you end up in the head or you find a node for which the starting node is in the left subtree
	  BST_iterator operator++() noexcept{
		node* p;		  //temp pointer	

	//if the current node has right child, move to it because its key is greater than the current one
        if (current -> right != nullptr){
            current = current->right.get();

	    //once you have moved to the right, you have to explore the left subtree to find the smallest key
            while (current->left != nullptr) current = current->left.get(); }
        
	else{
        	p = current->upper;
        	//if there's no right child, you go up until you find a node for which your previous path is in the left subtree or the head of the entire tree
		while (p != nullptr && current == p->right.get()){
                   current = p;
                   p = p->upper; }
            current = p; }
        return *this; }

	  //define equality between iterators if they point to the same node
	  friend bool operator==(const BST_iterator& a, const BST_iterator& b) { return a.current == b.current; }
	  friend bool operator!=(const BST_iterator& a, const BST_iterator& b) { return !(a.current == b.current); }

	  // set bst class as a friend class to access iterator's members in it
	  template<typename K, typename V, typename cmp>
      	  friend class BST::bst;
};

}

#endif
