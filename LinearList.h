#include <iostream>
using namespace std;
template<class T>
class linearList
{
public:
	virtual ~linearList() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int theIndex) const = 0;
	virtual int indexOf(const T& theElement)const = 0;
	virtual void erase(int theIndex) = 0;
	virtual void insert(int theIndex, const T& theElement) = 0;
	virtual void output(ostream& out) const = 0;
};
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("new length must be >= 0");
	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(a, a + number, temp);
	delete[]a;
	a = temp;
}//O(oldLength)
template<class T>
class arrayList :public linearList<T>
{
public:
	arrayList(int initialCapacity = 10)
	{
		if (initialCapacity < 1)
		{
			ostringstream s;
			s << "Initial capcity = " << initialCapacity << " Must be > 0";
			throw illegalParameterValue(s.str());
		}
		arrayLength = initialCapacity;
		listSize = 0;
	}//��T�ǻ�������ʱ��O(1);��T���Զ���������ʱ��O(initialCapacity)
	arrayList(const linearList<T>& t)
	{
		element = new T[t.arrayLength];
		copy(t.element, t.element + t.arrayLength, element);
		arrayLength = t.arrayLength;
		listSize = t.listSize;
	}//O(t.arrayLength)
	~arrayList()
	{
		delete[] element;
	}

	bool empty() const
	{
		return listSize == 0;
	}
	int size() const
	{
		return listSize;
	}
	T& get(int theIndex) const
	{
		checkIndex(theIndex);
		return element[theIndex];
	}
	int indexOf(T& theElement) const
	{
		int theIndex = (int)(find(element, element + listSize, theElement) - element);
		if (theIndex == listSize)
			return -1;
		else return theIndex;
	}//O��listSize)
	void erase(int theIndex)
	{
		checkIndex(theIndex);
		copy(element + theIndex+1, element + listSize, element + theIndex);
		element[--size].~T();
	}//O(listSize-theIndex)
	void insert(int theIndex, const T& theElement)
	{
		if (theIndex<0 || theIndex>listSize)
		{
			ostringstream s;
			s << "index = " << theIndex << " size = " << listSize;
			throw illegalParameterValue(s.str());
		}
		if (listSize == arraylength)
		{
			changeLength1D(element, 2 * arraylength);
			arrayLength *= 2;
		}
		copy_backward(element + theIndex, element + listSize, element + theIndex + 1);
		listSize++;
	}
	void output(ostream& o);
	int capacity() const
	{
		return arrayLength;
	}
protected:
	void checkIndex(int theIndex) const
	{
		if (theIndex < 0 || theIndex >= listSize)
		{
			ostringstream s;
			o << "index = " << theIndex << " size = " << listSize;
			throw illegalParameterValue(s.str());
		}
	}
	T* element;
	int arrayLength;
	int listSize;
};
template<class T>
void arrayList<T>::output(ostream& o)
{
	copy(element, element + listSize, ostream_iterator<T>(cout," ");
}
template<class T>
ostream& operator<<(ostream& out, const arrayList<T>& x)
{
	x.output(out);
	return out;
}
template<class T>
struct chainNode
{
	T element;
	chainNode<T>* next;

	chainNode() {}
	chainNode(const T& element)
	{
		this->element = element;
	}
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};
template<class T>
class chain : public linearList<T>
{
public:
	chain(int initialCapacity = 10)
	{
		if (initialCapacity < 1)
		{
			ostringstream s;
			s << "Initial capacity = " << initialCapacity << " Must be > 0";
			throw illegalParameterValue(s.str());
 		}
		firstNode = NULL;
		listSize = initialCapacity;
	}
	chain(const chain<T>& theList)
	{
		listSize = theList.listSize;
		if (listSize == 0)
		{
			firstNode = NULL;
			return;
		}
		chainNode<T>* sourceNode = theList.firstNode;
		firstNode = new chainNode<T>(sourceNode->element);
		sourceNode = sourceNode->next;
		chainNode<T>* targetNode = firstNode;
		while (sourceNode != NULL)
		{
			targetNode->next = new chainNode<T>(sourceNode->element);
			sourceNode = sourceNode->next;
			targerNode = targetNode->next;
		}
		targetNode = NULL;
	}
	~chain()
	{
		while (firstNode != NULL)
		{
			chainNode<T>* nextNode = firstNode->next;
			delete[] firstNode;
			firstNode = nextNode;
		}
	}
	
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const
	{
		checkIndex(theIndex);
		chainNode<T>* currentNode = firstNode;
		for (int i = 0; i < theIndex; i++)
			currentNode = currentNode->next;
		return currentNode->element;
	}
	int indexOf(T& theElement) const
	{
		chainNode<T>* currentNode = firstNode;
		int index = 0;
		while (currentNode!= NULL && currentNode->element != theElement)
		{
			currentNode = currentNode->next;
			index++;
		}
		if (currentNode == NULL)
			return -1;
		else return index;
	}
	void erase(int theIndex)
	{
		checkIndex(theIndex);
		chainNode<T>* deleteNode = firstNode;
		if (theIndex == 0)
			firstNode = firstNode->next;
		else
		{
			chainNode<T>* p = firstNode;
			for (int i = 0; i < theIndex - 1; i++)
				p = p->next;
			deleteNode = p->next;
			p->next = deleteNode->next;
		}
		listSize--;
		delete[]deleteNode;
	}
	void insert(int theIndex, T& theElement)
	{
		if (theIndex<0 || theIndex>size)
		{
			ostringstream s;
			s << "index = " << theIndex << " size = " << listSize;
			throw illegalParameterValue(s.str());
		}
		if (theIndex == 0)
			firstNode = new chainNode<T>(theElement);
		else
		{
			chainNode<T>* p = firstNode;
			for (int i = 0; i < theIndex - 1; i++)
				p = p->next;
			p->next = new chainNode<T>(theElement, p->next->next);
		}
		listSize++;
	}
	void output(ostream& out) const;
protected:
	void checkIndex(int theIndex) const
	{
		if (theIndex < 0 || theIndex >= listSize)
		{
			ostringstream s;
			s << "index = " << theIndex << " size = " << listSize;
			throw illegalParameterValue(s.str());
		}
	}
	chainNode<T>* firstNode;
	int listSize;
};
template<class T>
void chain<T>::output(ostream& out) const
{
	for (chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
		out << currentNode->element << " ";
}
template<class T>
ostream& operator<<(ostream& o, chain<T> theList)
{
	theList.output(o);
	return o;
}
template<class T>
class extendedLinearList : public linearList<T>
{
public:
	virtual ~extendedLinearList() = 0;
	virtual void clear() = 0;
	virtual void push_back(const T& theElement) = 0;
};
template<class T>
class extendedChain : public chain<T>, public exetendedLinearList<T>
{
public:
	extendedChain<T>(int initialCapacity = 10): chain<T>(initialCapacity)
	{
		lastNode = firstNode;
	}
	void clear()
	{
		while (firstNode != NULL)
		{
			chainNode<T>* nextNode = firstNode->next;
			delete firstNode;
			firstNode = nextNode;
		}
		listSize = 0;
	}
	void push_back(const T& theElement)
	{
		chainNode<T>* newNode = new chainNode(theElement, NULL);
		if (listSize == 0)
			firstNode = lastNode = newNode;
		else
		{
			lastNode->next = newNode;
			lastNode = newNode;
		}
		listSize++;
	}
protected:
	chainNode<T>* lastNode;
};
template<class T>
class circularListWithHeader :public extendedChain<T>
{
	circularListWithHeader()
	{
		headerNode = new chainNode<T>();
		headerNode->next = headerNode;
		listSize = 0;
	}
	indexOf(const T& theElement) const
	{
		headerNode->element = theElement;
		chainNode<T>* currentNode = headerNode->next;
		int index = 0;
		while (currentNode->element != theElement)
		{
			currentNode = currentNode->next;
			index++
		}
		if (currentNode = headerNode)
			return -1;
		else return index;
	}
protected:
	chainNode<T>* headerNode;
};