#include<iostream>
#include<queue>
using namespace std;
template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild, * rightChild;
	binaryTreeNode() { leftChild = rightChile = NULL; }
	binaryTreeNode(const T& theElement)
	{
		element = theElement;
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode* theLeftChild, binaryTreeNode* theRightChild)
	{
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};
template<class T>
class binaryTree
{
public:
	virtual ~binaryTree() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual void preOrder(void (*) (T*)) const = 0;
	virtual void inOrder(void (*)(T*)) const = 0;
	virtual void postOrder(void (*)(T*))const = 0;
	virtual void levelOrder(void(*)(T*))const = 0;
};
template<class E>
class linkedBinaryTree:public binaryTree<binaryTreeNode<E>>
{
private:
	binaryTreeNode* root;
	int treeSize;
	static void (*visit)(binaryTreeNode<E>*);
	static void preOrder(binaryTreeNode<E>*);
	static void inOrder(binaryTreeNode<E>*);
	static void postOrder(binaryTreeNode<E>*);
	static void dispose(binaryTreeNode<E>*);
public:
	linkedBinaryTree() {root = NULL; treeSize = 0;}
	~linkedBinaryTree() { erase(); }
	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }
	void preOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit;
		preOrder(root);
	}
	void inOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit;
		inOrder(root);
	}
	void postOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit;
		inOrder(root);
	}
	void levelOrder(void(*)(binaryTreeNode<E>*));
	void erase()
	{
		postOrder(dispose);
		root = NULL;
		treeSize = 0;
	}
};