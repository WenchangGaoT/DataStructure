#include"Tree.h"
template<class T>
void preOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}//ǰ����� O(n)
template<class T>
void inOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		inOrder(t->leftChild);
		visit(t);
		inOrder(t->rightChild);
	}
}//������� O(n)
template<class T>
void postOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		visit(t);
	}
}//������� O(n)
template<class T>
void infix(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		cout << '(';
		infix(t->leftChild);
		cout << t->element;
		infix(t->rightChild);
		cout << ')';
	}
}//��ȫ���Ż���׺����ʽ O(n)
template<class T>
void levelOrder(binaryTreeNode<T>* t)
{
	visit(t);
	arrayQueue<binaryTreeNode<T>*> q;
	while (t != NULL)
	{
		if (t->leftChild != NULL)
			q.push(t->leftChild);
		if (t->rightChild != NULL)
			q.push(t->rightChild);
		try { t = q.front(); }
		catch (queueEmpty) { return; }
		q.pop();
	}
}//��α��� O(n)
template<class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		linkedBinaryTree<T>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}
