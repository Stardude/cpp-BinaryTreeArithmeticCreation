#include "BinaryTree.h"

#include<iostream>
#include<string>
using namespace std;
class ArithmeticTree: public BinaryTree
{
public:
	ArithmeticTree();
	ArithmeticTree(string);
	void printTree() const;
	void printTree(BinaryTree*, short) const;

	string expression;
	BinaryTree *root;
private:
	
	bool isOperation(char) const;
	short priority(char) const;
	string eraseBrackets(string, short*) const;
	short findMinPriorityIndex(string) const;

	BinaryTree *addElement(BinaryTree*, char);
	BinaryTree *formTree(BinaryTree*, string);
};

