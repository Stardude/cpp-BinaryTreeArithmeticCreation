#include "ArithmeticTree.h"

ArithmeticTree::ArithmeticTree()
{
	cout << "Enter expression: ";
	cin >> expression;
	root = NULL;
	root = formTree(root, expression);
}

ArithmeticTree::ArithmeticTree(string _expression)
{
	expression = _expression;
	root = NULL;
	root = formTree(root, expression);
}

void ArithmeticTree::printTree() const
{
	printTree(root, 0);
}

void ArithmeticTree::printTree(BinaryTree *root, short level) const
{
	if (root)
	{
		printTree(root->left, level + 1);
		printTree(root->right, level + 1);
		for (int i = 0; i < level; i++) cout << ">";
		cout << root->data << "\n";
	}
}

bool ArithmeticTree::isOperation(char el) const
{
	return (el == '+' || el == '-' || el == '*' || el == '/' || el == '^') ? true : false;
}

short ArithmeticTree::priority(char operation) const
{
	switch (operation)
	{
	case '+': return 3;
		break;
	case '-': return 3;
		break;
	case '*': return 2;
		break;
	case '/': return 2;
		break;
	case '^': return 1;
		break;
	}
}

string ArithmeticTree::eraseBrackets(string exp, short *ptr) const
{
	while (exp[0] == '(' && exp[exp.size() - 1] == ')')
	{
		exp.erase(0, 1);
		exp.erase(exp.size() - 1, 1);
		*ptr = *ptr + 1;
	}
	return exp;
}

short ArithmeticTree::findMinPriorityIndex(string exp) const
{
	short tmp, priority_max = 0;
	string i_max;
	bool p = true;
	int q = 0;
	short corect = 0, *ptr;
	ptr = &corect;
	exp = eraseBrackets(exp, ptr);
	if ((exp.find('(') != string::npos && exp.find(')') == string::npos) ||
		(exp.find(')') != string::npos && exp.find('(') == string::npos)) p = true;
	else if (exp.find('(') != string::npos && exp.find(')') != string::npos) p = false;
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == '(') q++;
		if (exp[i] == ')') q--;
		if (isOperation(exp[i]))
		{
			if (p) tmp = priority(exp[i]);
			else
			{
				if (q > 0) tmp = -1;
				else tmp = priority(exp[i]);
			}
			if (tmp >= priority_max)
			{
				priority_max = tmp;
				i_max += i;
			}
		}
	}
	return (short)i_max[i_max.size() / 2] + corect;
}

BinaryTree * ArithmeticTree::addElement(BinaryTree *root, char data)
{
	if (!root)
	{
		root = new BinaryTree;
		root->data = data;
		root->left = root->right = NULL;
		return root;
	}
}

BinaryTree *ArithmeticTree::formTree(BinaryTree *root, string expression)
{
	short i = findMinPriorityIndex(expression);
	if (i)
	{
		root = addElement(root, expression[i]);
		string leftTree = expression.substr(0, i);
		string rightTree = expression.substr(i + 1, expression.size());
		//cout << leftTree << " <> " << rightTree << "\n";
		root->left = formTree(root->left, leftTree);
		root->right = formTree(root->right, rightTree);
	}
	else
	{
		if (expression[0] == '(')
			root = addElement(root, expression.back());
		else
			root = addElement(root, expression[0]);
	}
	return root;
}
