#include <iostream>
using namespace std;
template <class T>
class maxPriorityQueue
{
public:
	virtual ~maxPriorityQueue() {};
	virtual bool empty()const = 0;
	virtual int size()const = 0;
	virtual const T& top() const = 0;
	virtual void pop() = 0;
	virtual void push(x) = 0;
};
template<class T>
class maxHeap
{
private:
	T* Heap;
	int arrayLength, heapSize;
public:
	const T& top();
	bool empty() const { return heapSize == 0; }

};