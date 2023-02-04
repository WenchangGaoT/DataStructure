#define LOCA
#include <iostream>
using namespace std;
class queue;
class AVLtree
{
	friend queue;
	int size;
	int element, b, height;
	AVLtree* lefttree, * righttree;
	bool complete = 1;
public:
	bool iscomplete()
	{
		return complete;
	}
	void setSize(int s)
	{
		size = s;
	}
	AVLtree(int x = 0)
	{
		element = x;
		height = b = 0;
		lefttree = righttree = NULL;
	}
	AVLtree(AVLtree& t)
	{
		element = t.element;
		size = t.size;
		height = t.height;
		b = t.b;
		if (t.lefttree != NULL)
			lefttree = new AVLtree(*t.lefttree);
		else lefttree = NULL;
		if (t.righttree != NULL)
			righttree = new AVLtree(*t.righttree);
		else lefttree = NULL;
	}
	int getHeight(AVLtree* t)
	{
		if (t == NULL)
			return 0;
		int hl = getHeight(t->lefttree);
		int hr = getHeight(t->righttree);
		if (hl > hr) t->height = hl + 1;
		else t->height = hr + 1;
		if(t->lefttree!=NULL&&t->righttree!=NULL)t->b = t->lefttree->height - t->righttree->height;
		else
		{
			if (t->lefttree != NULL && t->righttree == NULL) t->b = t->lefttree->height;
			if (t->righttree != NULL && t->lefttree == NULL) t->b = t->righttree->height * -1;
			if (t->righttree == NULL && t->lefttree == NULL) t->b = 0;
		}
		if (t->b > 1)
		{
			if (t->lefttree->b == 1)
			{
				int e = t->element;
				AVLtree* BL = t->lefttree->lefttree, * BR = t->lefttree->righttree;
				AVLtree* AR = t->righttree;
				t->righttree = new AVLtree(e);
				t->righttree->height = t->height - 1;
				t->righttree->lefttree = BR;
				t->righttree->righttree = AR;
				t->element = t->lefttree->element;
				t->lefttree = BL;
			}
			if (t->lefttree->b == -1)
			{
				AVLtree* AR,* BL;
				if (t->righttree != NULL) { AR = t->righttree; BL = t->righttree->lefttree; }
				else { AR = NULL; BL = NULL; }
				AVLtree * CL = t->lefttree->righttree->lefttree, * CR = t->lefttree->righttree->righttree;
				int ea = t->element;
				int ec = t->lefttree->righttree->element;
				t->righttree = new AVLtree(ea);
				t->righttree->lefttree = CR;
				if (AR != NULL)t->righttree->righttree = AR;
				else t->righttree->righttree = NULL;
				t->element = ec;
				t->lefttree->lefttree = BL;
				t->lefttree->righttree = CL;
			}
		}
		if (t->b < -1)
		{
			if (t->righttree->b == -1)
			{
				int e = t->element;
				AVLtree* AL = t->lefttree, * BL = t->righttree->lefttree, * BR = t->righttree->righttree;
				t->element = t->righttree->element;
				t->lefttree = new AVLtree(e);
				t->lefttree->lefttree = AL;
				t->lefttree->righttree = BL;
				t->lefttree->element = e;
				t->righttree = BR;
			}
			if (t->righttree->b == 1)
			{
				AVLtree* AL = t->lefttree, * CL = t->righttree->lefttree->lefttree, * CR = t->righttree->lefttree->righttree, * BR = t->righttree->righttree;
				int ea = t->element;
				int ec = t->righttree->lefttree->element;
				t->element = ec;
				t->lefttree = new AVLtree(ea);
				t->lefttree->lefttree = AL;
				t->lefttree->righttree = CL;
				t->righttree->lefttree = CR;
				t->righttree->righttree = BR;
			}
		}
		return t->height;
	}
	void insert(int x)
	{
		AVLtree* ptr1 = this, * ptr2 = ptr1;
		int type;
		while (ptr1 != NULL)
		{
			ptr2 = ptr1;
			if (x <= ptr1->element) { ptr1 = ptr1->lefttree; type = 0; }
			else { ptr1 = ptr1->righttree; type = 1; }
		}
		AVLtree* ptr = new AVLtree(x);
		if (type) ptr2->righttree = ptr;
		else ptr2->lefttree = ptr;
		getHeight(this);
	}
	void levelOrder();
};
class queue
{
	AVLtree q[30];
	int length, currentsize, ptr;
public:
	queue(int s)
	{
		length = s;
		currentsize = 0;
		ptr = 0;
	}
	void push(AVLtree& t)
	{
		q[currentsize++] = t;
	}
	AVLtree& front()
	{
		return q[ptr];
	}
	void pop()
	{
		ptr++;
	}
};
void AVLtree::levelOrder()
{
	AVLtree* t = this;
	int first = 1,leftshut = 0, rightshut = 0;
	queue q(size);
	q.push(*t);
	while (first<=size)
	{
		if (t->lefttree != NULL)
			q.push(*t->lefttree);
		else leftshut = 1;
		if (t->righttree != NULL)
			q.push(*t->righttree);
		else rightshut = 1;
		if (leftshut && t->lefttree != NULL) complete = 0;
		if (rightshut && t->righttree != NULL) complete = 0;
		if (first == 1)
			cout << q.front().element;
		else
			cout << ' ' << q.front().element;
		q.pop();
		t = &q.front();
		first++;
	}
	cout << endl;
}
int main()
{
	int n,a1;
	cin >> n >> a1;
	AVLtree tree(a1);
	n--;
	tree.setSize(n + 1);
	while (n-- > 0)
	{
		int a;
		cin >> a;
		tree.insert(a);
	}
	tree.levelOrder();
	if (tree.iscomplete())cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}