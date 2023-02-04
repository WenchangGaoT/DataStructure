#define LOCA
#include <iostream>
using namespace std;
class huffmanTree;
class huffmanTreeNode
{
	friend huffmanTree& buildTree(huffmanTree* t, int num);
	friend huffmanTree;
	char element;
	int weight, height;
	int* code;
	bool ele;
	huffmanTreeNode* leftChild, * rightChild, * father;
public:
	huffmanTreeNode(int theWeight,bool e=0, char theElement=0 )
	{
		element = theElement;
		weight = theWeight;
		ele = e;
		height = 1;
		leftChild = rightChild = NULL;
		father = NULL;
	}
	huffmanTreeNode(huffmanTreeNode& t)
	{
		element = t.element;
		weight = t.weight;
		height = t.height;
		ele = t.ele;
		if (t.leftChild != NULL) {
			leftChild = new huffmanTreeNode(*t.leftChild);
			leftChild->father = this;
		}
		if (t.rightChild != NULL) {
			rightChild = new huffmanTreeNode(*t.rightChild);
			rightChild->father = this;
		}
	}
	friend void visit(huffmanTreeNode*);
};
void visit(huffmanTreeNode* t)
{
	if (t->ele)
	{
		cout << t->element << ":";
		for (int i = 0; i < t->height - 1; i++)
			cout << t->code[i];
		cout << endl;
	}
}
class huffmanTree
{
public:
	huffmanTreeNode* root;
public:
	huffmanTree() {}
	huffmanTree(int theWeight,bool e=0,char theElement=0) {
		root = new huffmanTreeNode(theWeight, e, theElement);
	}
	huffmanTree(huffmanTree& t)
	{
		root = new huffmanTreeNode(*t.root);
		root->code = NULL;
	}
	void combine(huffmanTree& r)
	{
		this->root->father = new huffmanTreeNode(root->weight + r.root->weight, 0);
		this->root->father->rightChild = root;
		this->root->father->leftChild = r.root;
		r.root->father = root->father;
		this->root = this->root->father;
		this->root->father = NULL;
#ifdef LOCA
		cout << "combining" << root->weight << "  " << root->leftChild->weight << "  " << root->rightChild->weight << endl;
#endif
	}
	void DFS(huffmanTreeNode* t,int type)
	{
		if (t != NULL)
		{
			if (t != root)
			{
				t->height = t->father->height + 1;
				t->code = new int[t->height - 1];
				for (int i = 0; i < t->height-2; i++)
					t->code[i] = t->father->code[i];
				t->code[t->height - 2] = type;
			}
			DFS(t->leftChild,0);
			visit(t);
			DFS(t->rightChild,1);
		}
	}
	friend huffmanTree& buildTree(huffmanTree*,int);
};
template<class T>
void sswap(T& a1, T& a2)
{
	T t = a1;
	a1 = a2;
	a2 = t;
}
huffmanTree& buildTree(huffmanTree* t, int num)
{
	int index = 0;
	while (index < num - 1)
	{
		int minweight1 = t[index].root->weight;
		int minweight2 = t[index + 1].root->weight;
		for (int i = index; i < num; i++)
			if (t[i].root->weight < minweight1)
			{
				sswap(t[i], t[index]);
				minweight1 = t[index].root->weight;
				minweight2 = t[index + 1].root->weight;
			}
		for(int i=index+1;i<num;i++)
			if (t[i].root->weight < minweight2)
			{
				sswap(t[i], t[index + 1]);
				minweight2 = t[index + 1].root->weight;
			}
		t[index + 1].combine(t[index]);
		index++;
	}
	return t[num - 1];
}
int main()
{
	int num;
	cin >> num;
	huffmanTree* forest = new huffmanTree[num];
	for (int i = 0; i < num; i++)
	{
		char c;
		int in;
		cin >> c >> in;
		huffmanTree t(in, 1, c);
		forest[i] = t;
	}
	huffmanTree tree = buildTree(forest, num);
	tree.DFS(tree.root,0);
#ifdef LOCA
	system("pause");
#endif
}