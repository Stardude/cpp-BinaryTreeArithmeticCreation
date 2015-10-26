#include<iostream>
#include<string>
using namespace std;

struct Tree
{
	char data;
	Tree *left;
	Tree *right;
};

bool isOperation(char el)
{
	return (el == '+' || el == '-' || el == '*' || el == '/' || el == '^') ? true : false;
}
int priority(char operation)
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
string eraseBrackets(string exp, int *ptr)
{
	while (exp[0] == '(' && exp[exp.size() - 1] == ')')
	{
		exp.erase(0, 1);
		exp.erase(exp.size() - 1, 1);
		*ptr = *ptr + 1;
	}
	return exp;
}
int findMaxPriorityIndex(string exp)
{
	int tmp, priority_max = 0;
	string i_max;
	bool p = true;
	int q = 0;
	int corect = 0, *ptr;
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
	return (int)i_max[i_max.size() / 2] + corect;
}
Tree *addElement(Tree *root, char data)
{
	if (!root)
	{
		root = new Tree;
		root->data = data;
		root->left = root->right = NULL;
		return root;
	}
}
void printTree(Tree *root, int level)
{
	if (root)
	{
		printTree(root->left, level + 1);
		printTree(root->right, level + 1);
		for (int i = 0; i < level; i++) cout << ">";
		cout << root->data << "\n";

	}
}
Tree *formTree(Tree *root, string exp)
{
	int i = findMaxPriorityIndex(exp);
	if (i)
	{
		root = addElement(root, exp[i]);
		string leftTree = exp.substr(0, i);
		string rightTree = exp.substr(i + 1, exp.size());
		cout << leftTree << " <> " << rightTree << "\n";
		root->left = formTree(root->left, leftTree);
		root->right = formTree(root->right, rightTree);
	}
	else
	{
		if (exp[0] == '(')
		{
			root = addElement(root, exp.back());
		}
		else
			root = addElement(root, exp[0]);
	}
	return root;

}
void createTree(string exp)
{
	Tree *root = NULL;
	root = formTree(root, exp);
	cout << "\n";
	printTree(root, 0);
}
int main()
{
	string expression;
	cout << "Enter expression: ";
	cin >> expression;
	createTree(expression);
	cout << "\n";
	system("pause");
	return 0;
}