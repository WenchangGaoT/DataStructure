#define LOCA
#include<iostream>
using namespace std;
class binaryTree;
class binaryTreeNode
{
	friend binaryTree;
	friend void visit(binaryTreeNode*);
	char element;
	binaryTreeNode* leftChild, *rightChild;
public:
	binaryTreeNode() {};
	binaryTreeNode(char theElement)
	{
		element = theElement;
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(char theElement, binaryTreeNode* left, binaryTreeNode* right)
	{
		element = theElement;
		leftChild = left;
		rightChild = right;
	}
};
class binaryTree
{
public:
	binaryTreeNode* node;
public:
	binaryTree(binaryTreeNode* theNode)
	{
		node = new binaryTreeNode(theNode->element);
	}
	binaryTree() { node = new binaryTreeNode; };
	void inOrderVisit(binaryTreeNode* t)
	{
		if (t != NULL)
		{
			inOrderVisit(t->leftChild);
			visit(t);
			inOrderVisit(t->rightChild);
		}
	}
	void preOrderBuild(binaryTreeNode*& t, char* ch, int& num, int len)
	{
		if (num < len) 
		{
			if (ch[num] == '#')  num++;
			else
			{
				t = new binaryTreeNode(ch[num]);
				num++;
				preOrderBuild(t->leftChild, ch, num,len);
				preOrderBuild(t->rightChild, ch, num,len);
			}
		}
	}
};
void visit(binaryTreeNode* t)
{
	cout << t->element << " ";
}
int main()
{
	char t[101];
	cin >> t;
	binaryTree tree;
	int num = 0;
	int len = strlen(t);
	tree.preOrderBuild(tree.node, t, num, len);
	tree.inOrderVisit(tree.node);
#ifdef LOCA
	system("pause");
#endif
}