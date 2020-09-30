#include "bst.hpp"

int main() {

	//CHECK DEFAULT CONSTRUCTOR
	std::cout << "Checking default constructor" << std::endl;
	BST::bst<int,int> tree{};

        //CHECK ostream FUNCTION
        std::cout << "Printing empty BST" << std::endl;
        std::cout << tree << std::endl;

	//CHECK INSERT lvalue FUNCTION
	std::vector<int> key{1,2,3,5,8};
	std::cout << "Filling the tree with the vector (1,2,3,5,8)" << std::endl;
	for (std::size_t i{0};i<key.size();i++) tree.insert(std::pair<int,int>(key[i],0)); 

	//CHECK ostream FUNCTION
	std::cout << "Printing BST" << std::endl;
	std::cout << tree << std::endl;
	
	//CHECK SUBSCRIPTING OPERATOR
	std::cout << "Key = 1, value = " << tree[1] << std::endl;
	std::cout << "Subscripting key=1 with the value 5, BST[1]=5" << std::endl;
	tree[1]=5;
	std::cout << "Key = 1, new value = " << tree[1] << std::endl << std::endl;

        //CHECK EMPLACE FUNCTION
        std::cout << "Call emplace(6,1)" << std::endl;
        tree.emplace(6,1);
        std::cout << "Printing BST after emplace" << std::endl;
        std::cout << tree << std::endl;

	//CHECK ERASE FUNCTION
	std::cout << "Call erase at key = 1" << std::endl;
	tree.erase(1);
	std::cout << "Printing BST after erase" << std::endl;
	std::cout << tree << std::endl;

        std::cout << "Call erase at key = 6" << std::endl;
        tree.erase(6);
        std::cout << "Printing BST after erase" << std::endl;
	std::cout << tree << std::endl;
	
	//CHECK BALANCE
	std::cout << "Balancing the tree" << std::endl << std::endl;
	tree.balance();

	//CHECK COPY CONSTRUCTOR
	std::cout << "Copying the tree and modifying the copy with emplace(4,2)" << std::endl;
	BST::bst<int,int> tree_copy{tree};
	tree_copy.emplace(4,2);
	std::cout << "Printing the original tree and the modified copy. No modification in the original tree thanks to the deep copy" << std::endl;
	std::cout << "Original tree" << std::endl;
	std::cout << tree << std::endl;
	std::cout << "Copied tree" << std::endl;
	std::cout << tree_copy << std::endl;

	//CHECK COPY ASSIGNMENT
	BST::bst<int,int> new_tree{};
	new_tree = tree;
	std::cout << "Printing new tree constructed with copy assignment from the original tree" << std::endl;
	std::cout << new_tree << std::endl;
	
	//CHECKING MOVE CONSTRUCTOR
	std::cout << "Moving BST to new tree" << std::endl;
	BST::bst<int,int> tree_move{std::move(tree)};
	std::cout << "Printing the new tree" << std::endl;
	std::cout << tree_move << std::endl;
	std::cout << "Printing the old tree" << std::endl;
	std::cout << tree << std::endl;

	//CHECKING CLEAR FUNCTION
	std::cout << "Clearing the new tree" << std::endl;
	tree_move.clear();
	std::cout << "Printing the cleared new tree" << std::endl;
	std::cout << tree_move << std::endl;

	//CHECKING WITH DOUBLE
	std::cout << "Checking with double keys and values" << std::endl;
	BST::bst<double,double> tree_d{};
	std::cout << "emplace(1.5,3.14), emplace(10,2.71) and emplace(1,1) in an empty tree" << std::endl;
	tree_d.emplace(1.5,3.14);
	tree_d.emplace(10,2.71);
	tree_d.emplace(1,1);

	std::cout << "Printing the tree" << std::endl;
	std::cout << tree_d << std::endl;

	std::cout << "Balancing the tree" << std::endl;

	std::cout << "Copy, move and erase node (1,1) from the copied tree" << std::endl;
	BST::bst<double,double> copy_tree_d{tree_d};
	BST::bst<double,double> move_tree_d{std::move(tree_d)};
	copy_tree_d.erase(1);	
	std::cout << "Printing original (empty) tree, moved tree and copied tree" << std::endl;
	std::cout << "Original tree" << std::endl;
	std::cout << tree_d << std::endl;
        std::cout << "Moved tree" << std::endl;
        std::cout << move_tree_d << std::endl;
        std::cout << "Copied tree" << std::endl;
        std::cout << copy_tree_d << std::endl;


	return 0; }
