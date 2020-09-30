#ifndef __BST_CPP__
#define __BST_CPP__

#include "bst.hpp"

//IMPLEMENTATION OF FUNCTIONS IN bst.hpp


/********** COPY CONSTRUCTOR **********/
//perform a deep copy of a given tree using the helper function __copy
template <typename K, typename V, typename cmp>
BST::bst<K,V,cmp>::bst(const BST::bst<K,V,cmp>& tree) : op{tree.op}, head{ std::unique_ptr<NODE::node<std::pair<const K,V>>>( new NODE::node<std::pair<const K,V>>(tree.head.get()->value, nullptr) ) } {
  if (tree.head.get()->left) __copy(tree, tree.head.get()->left);
  if (tree.head.get()->right) __copy(tree, tree.head.get()->right); }


/********** COPY SINGLE NODE **********/
//use emplace function to recursevely copy a given tree
template <typename K, typename V, typename cmp>
void BST::bst<K,V,cmp>::__copy(const BST::bst<K,V,cmp>& tree, std::unique_ptr<NODE::node<std::pair<const K, V>>>& a) {
	this->emplace(a.get()->value.first,a.get()->value.second);

	if (a.get()->left) __copy(tree, a.get()->left);
        if (a.get()->right) __copy(tree, a.get()->right);
            
  	return; }


/********** INSERT FUNCTION **********/
//Create a node with a given value if it is not present and returns an iterator pointing to the inserted node and a bool=true. If the key is already present returns an iterator to the present node and abool=false
template <typename K, typename V, typename cmp>
std::pair<ITER::BST_iterator<NODE::node<std::pair<const K,V>>, std::pair<const K,V> >, bool> BST::bst<K,V,cmp>::insert(pair_type& x){

	node_type* t = head.get();

  	while(t){
      		if(op(x.first,t->value.first)){
                	if(t->left) t=t->left.get();
                	else{   t->left.reset(new node_type {x,t});
                        	return std::make_pair(iterator{t->left.get()},true) ; }
                	}

      	else if(op(t->value.first,x.first)){
        	if(t->right) t=t->right.get();
                else{   t->right.reset(new node_type{x,t});
                        return std::make_pair(iterator{t->right.get()},true); }
                }

      	else return std::make_pair(iterator{t},false); }

    	head.reset(new node_type{x, nullptr});
    	return std::make_pair(iterator{head.get()},true); }


/********** INSERT FUNCTION rvalue **********/
template <typename K, typename V, typename cmp>
std::pair<ITER::BST_iterator<NODE::node<std::pair<const K,V>>, std::pair<const K,V> >, bool> BST::bst<K,V,cmp>::insert(pair_type&& x){

  	node_type* t = head.get();

  	while(t){
      		if(op(x.first,t->value.first)){
                	if(t->left) t=t->left.get();
                	else{   t->left.reset(new node_type {x,t});
                        	return std::make_pair(iterator{t->left.get()},true) ; }
                	}

      	else if(op(t->value.first,x.first)){
        	if(t->right) t=t->right.get();
                else{   t->right.reset(new node_type{x,t});
                        return std::make_pair(iterator{t->right.get()},true); }
                }

      	else return std::make_pair(iterator{t},false); }

    	head.reset(new node_type{x, nullptr});
    	return std::make_pair(iterator{head.get()},true); }


/********** FIND **********/
//move from the head using the op operator and stop if the key is found
template <typename K, typename V, typename cmp>
ITER::BST_iterator<NODE::node<std::pair<const K,V>>,std::pair<const K,V>> BST::bst<K,V,cmp>::find(const K& x) { 
	node_type* t = head.get();
  	while(t) {
    		if(op(x,t->value.first)){
      			if(t->left) t=t->left.get();
      			else return end(); }
    		
		else if(op(t->value.first, x)){
     	 		if(t->right) t=t->right.get();
      			else return end(); }
    		
		else return iterator{t}; }
  	
	return iterator{nullptr}; }


/********** FIND const VERSION **********/
template <typename K, typename V, typename cmp>
ITER::BST_iterator<NODE::node<std::pair<const K,V>>,const std::pair<const K,V>> BST::bst<K,V,cmp>::find(const K& x) const{
	node_type* t = head.get();
  	while(t) {
    		if(op(x,t->value.first)){
      			if(t->left) t=t->left.get();
      			else return cend(); }
    		
		else if(op(t->value.first,x)){
      			if(t->right) t=t->right.get();
      			else return cend(); }
    
		else return const_iterator{t}; }
  
	return const_iterator{nullptr}; }


/********** BALANCE **********/	
//Use iteratively the function sortedArrayToBst to rebuild a balanced tree. It starts with saving the tree in a sorted array
template <typename K, typename V, typename cmp>
void BST::bst<K,V,cmp>::balance(){
	std::vector<pair_type> app;
  	int tmp=0;
  	for(auto i=cbegin(); i != cend(); ++i){
    		app.push_back(*i);
    		tmp++; }

	bst balanced_tree{};
  	sortedArrayToBST(app,0,app.size()-1,balanced_tree);
  	clear(); 
  	head.reset(balanced_tree.head.release());
  	return; }


/********** SORTED ARRAY TO BST **********/
//find the median of an oredered vector and insert it as a head of the tree. Then calls iteratevely itslef to build right and left subtrees.
template <typename K, typename V, typename cmp >
void BST::bst<K,V,cmp>::sortedArrayToBST(std::vector<std::pair<const K,V>> data,int start, int end, BST::bst<K,V,cmp> &balanced_tree){  
	if (start > end) return;  
  
  	int mid = (start + end)/2;  
  	balanced_tree.insert(data[mid]);  

  	sortedArrayToBST(data, start, mid-1,balanced_tree);
  	sortedArrayToBST(data, mid + 1, end,balanced_tree);  

  	return; }  


/********** ERASE **********/
//Remove a given key if present and rejoin the tree after the removal. It uses helper functions erase_head() and erase_generic()
template <typename K, typename V, typename cmp >
void BST::bst<K,V,cmp>::erase(const K& x){
	iterator it_erase = find(x);
 	node_type* node_to_erase = it_erase.current;

  	if( it_erase == end()) {
    		std::cout<< "The key is not present."<<std::endl; 
    		return; }

  	else { 	if(node_to_erase==head.get()) erase_head();
   		else erase_generic(it_erase);
		return; }
	}


/********** ERASE GENERIC **********/
//function called by erase which erases any node different from head. 
template <typename K, typename V, typename cmp>
void BST::bst<K,V,cmp>::erase_generic(ITER::BST_iterator<NODE::node<std::pair<const K,V>>,std::pair<const K,V>> it_erase){
	node_type* node_to_erase = it_erase.current;
  	node_type* parent = node_to_erase->upper;   
    
  	//IF NO CHILDREN
	if(node_to_erase->left == nullptr  && node_to_erase->right == nullptr){
      		node_to_erase->upper=nullptr;

      		if(op(node_to_erase->value.first,parent->value.first)) parent->left.reset();
       		else parent->right.reset(); }
  
  	//ONLY RIGHT CHILD
	else if(node_to_erase->left.get() == nullptr && node_to_erase->right.get() != nullptr){
      		(node_to_erase->right)->upper=parent;		//set new right child parent
      
      	//set new child for new parent. Check if node_to_erase was either right or left child
	if(op(node_to_erase->value.first,parent->value.first)) parent->left.reset(node_to_erase->right.release());
	else parent->right.reset(node_to_erase->right.release());

 	node_to_erase->upper=nullptr; }
        
	//ONLY LEFT CHILD
	else if(node_to_erase->left.get() != nullptr && node_to_erase->right.get() == nullptr){
      		(node_to_erase->left)->upper=parent;		//set new left child parent
      
        //set new child for new parent. Check if node_to_erase was either right or left child
		if(op(node_to_erase->value.first,parent->value.first)) parent->left.reset(node_to_erase->left.release());
     		else parent->right.reset(node_to_erase->left.release());   

      		node_to_erase->upper=nullptr; }

        //TWO CHILDREN
	else{
	//find the node_to_erase successor (incrementing iterator). Then "replace" node_to_erase with node_successor in the following way.
        //Set the parent of node_to_erase's left child as the node_successor
        //Reset successor's left child with the left child of node_to_erase. Successor has for sure no left child, otherwise it wouldn't have been the successor
	node_type* node_successor=(++it_erase).current;
   	(node_to_erase->left)->upper=node_successor;
   	node_successor->left.reset(node_to_erase->left.release());
	
	//if node_successor is the right child of node_to_erase then set node_successor parent with the former parent of node_to_erase and viceversa, checking if node_to_erase was either a left or a right child 
    	if(node_successor==node_to_erase->right.get()){
      		node_successor->upper=parent;
      		node_to_erase->upper=nullptr;

      		if(op(node_to_erase->value.first,parent->value.first)) parent->left.reset(node_to_erase->right.release());
		else parent->right.reset(node_to_erase->right.release()); }

	//if node_successor is not the right child of node_to_erase
        //if node_successor has a right child (it cannot have a left child, otherwise it wouldn't have been the successor) set the new parent of this right child with the former parent of node_successor and viceversa (node_successor was for sure a left child of its parent)
        //then "replace" node_to_erase with node_successor by setting the right child of node_successor with the former right child of node_to_erase and finally set the new parent of node_successor with the former parent of node to erase and viceversa, checking if node_to_erase was either a left or a right child
	else{
      		if (node_successor->right) { 
        		(node_successor->right)->upper = node_successor->upper;
        		(node_successor->upper)->left.reset(node_successor->right.release()); }

      		node_successor->right.reset(node_to_erase->right.release());
      		(node_successor->right)->upper=node_successor;
                
      		node_successor->upper=parent;
      		node_to_erase->upper=nullptr;

      		if(op(node_to_erase->value.first,parent->value.first)) parent->left.reset(node_to_erase->right.release());
       		else parent->right.reset(node_to_erase->right.release()); } 
  	}
return; }


/********** ERASE HEAD **********/
//erase the head of the tree
template <typename K, typename V, typename cmp>
void BST::bst<K,V,cmp>::erase_head(){
	using pair_type = typename std::pair<const K,V>;
  	using iterator  = typename ITER::BST_iterator<NODE::node<pair_type>,pair_type>; 


  	//THERE IS ONLY THE HEAD
	if(head.get()->right==nullptr && head.get()->left==nullptr) head.reset();
  
  	else{
		//ONLY LEFT CHILD just remove the head from the tree
    		if(head.get()->right==nullptr) {
      			(head.get()->left)->upper=nullptr;
      			head.reset(head.get()->left.release()); }

    		//ONLY RIGHT CHILD just remove the head from the tree
 		else if(head.get()->left==nullptr) {
                        (head.get()->right)->upper=nullptr;
                        head.reset(head.get()->right.release()); }

		//HEAD HAS TWO CHILDREN
		//substitue the head with its successor node_successor (next node following the keys). Set the parent of the head's left child to node_successor and viceversa (node_successor cannot have left child, otherwise it wouldn't have been the successor)
		else{
			iterator H{head.get()};
      			node_type* node_successor = (++H).current;
        		(head.get()->left)->upper=node_successor;
        		node_successor->left.reset(head.get()->left.release());

      			//if successor is the right child of the head set it as new head
			if(node_successor==head.get()->right.get()){
				head.reset(head.get()->right.release());
        			node_successor->upper=nullptr; }

      			//if the successor is not the right child of the head do the following: if successor has a right child set the parent of this child to the parent of node_successor and viceversa, then set the right child of the former head as the right child of node_successor. Reset the head to node_successor
      			else{
        			if (node_successor->right.get()) {
          				(node_successor->right)->upper = node_successor->upper;
          				(node_successor->upper)->left.reset(node_successor->right.release()); }

        			node_successor->right.reset(head.get()->right.release());
        			head.reset(node_successor);
        			(node_successor->right)->upper=node_successor;
        			node_successor->upper=nullptr; } 
    			}               
  		}
  	return; }


#endif
