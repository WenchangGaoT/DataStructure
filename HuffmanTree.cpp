#define LOCA
#include<iostream>
using namespace std;
class huffmanTree;
class huffmanTreeNode
{
	friend huffmanTree;
	char element;
	bool ele;
	int weight;
	int height;
	int* code;
	huffmanTreeNode* leftChild, * rightChild, * father;
public:
	huffmanTreeNode(huffmanTreeNode& t) {
		ele = t.ele;
		element = t.element;
		weight = t.weight;
		height = t.height;
		leftChild = t.leftChild;
		rightChild = t.rightChild;
		father = t.father;
	};
	huffmanTreeNode(huffmanTreeNode& l, huffmanTreeNode& r)
	{
		ele = 0;
		weight = l.weight + r.weight;
		height = 1;
		leftChild = &l;
		rightChild = &r;
		l.father = this;
		r.father = this;
	}
	huffmanTreeNode(bool el=0, int we=0, char e = 0)
	{
		element = e;
		weight = we;
		ele = el;
		height = 1;
		leftChild = rightChild = father = NULL;
		code = NULL;
#ifdef LOCA
		cout << "building" << endl;
#endif
	}
	friend huffmanTree* buildTree(huffmanTreeNode* nodes, int num);
	friend void visit(huffmanTreeNode*);
};
void visit(huffmanTreeNode* t)
{
	if (t->ele == 1)
	{
		cout << t->element << ":";
		for (int i = 0; i < t->height; i++)
		{
			cout << t->code[i];
		}
	}
}
class huffmanTree
{
public:
	huffmanTreeNode* root;
	int size;
public:
	huffmanTree(int x, huffmanTreeNode& t) { size = x; root = &t; root->code = new int; *root->code = 0; root->height = 1; }
	void DFS(huffmanTreeNode* t,int type)
	{
		if (t != NULL)
		{
			if (t!=root) 
			{
				t->height = t->father->height + 1;
				t->code = new int[t->height];
				for (int i = 0; i < t->father->height; i++)
					t->code[i] = t->father->code[i];
				t->code[t->height - 1] = type;
			}
			DFS(t->leftChild, 0);
			visit(t);
			DFS(t->rightChild, 1);
		}
	}
	huffmanTree(huffmanTree& t)
	{
		root = t.root;
		size = t.size;
	}
}; 
huffmanTree* buildTree(huffmanTreeNode* nodes, int num)
{
	int* added = new int[num];
	for (int i = 0; i < num; i++)
		added[i] = 0;
	int in;
	while (1)
	{
		int minindex1 = 0, minweight1 = 100000000, minindex2 = 0, minweight2 = 100000000;
		for (int i = 0; i < num; i++)
		{
			if (added[i] == 0 && nodes[i].weight < minweight1)
			{
				minindex1 = i;
				minweight1 = nodes[i].weight;
			}
			else if (added[i] == 0 && nodes[i].weight < minweight2)
			{
				minindex2 = i;
				minweight2 = nodes[i].weight;
			}
		}
		huffmanTreeNode* changed = nodes + minindex1;
		huffmanTreeNode min = nodes[minindex1];
		changed = new huffmanTreeNode(min, nodes[minindex2]);
		added[minindex2] = 1;
		int n = 0;
		for (int i = 0; i < num; i++)
			if (added[i]) n++;
		if (n==1) { in = minindex1; break; }
	}
	static huffmanTree tree(num, nodes[in]);
	return &tree;
}
int main()
{
	int num;
	cin >> num;
	int i = 0;
	huffmanTreeNode* node = new huffmanTreeNode[num];
	while (i++ < num)
	{
		char c;
		int in;
		cin >> c >> in;
		node[i] = new huffmanTreeNode(true, in, c);
	}
	huffmanTree *tree = buildTree(node, num);
	tree->DFS(tree->root,0);
}