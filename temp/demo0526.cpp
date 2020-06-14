// demo0526.cpp : ??????????ио????????
//

#include <iostream>
#include <assert.h>

using namespace std;

class test
{
private:
	int *ptr;
	int size;

public:
	test(int sz) : size(sz) { ptr = new int[size]; }
	virtual ~test()
	{
		if (ptr)
			delete[] ptr;
	}
	test(const test &obj)
	{
		size = obj.size;
		ptr = new int[size];
		memcpy(ptr, obj.ptr, size * sizeof(int));
	}
	test(test &&obj)
	{
		ptr = obj.ptr;
		obj.ptr = NULL;
	}
	test &operator=(const test &obj)
	{
		if (ptr)
			delete[] ptr;
		size = obj.size;
		ptr = new int[size];
		memcpy(ptr, obj.ptr, size * sizeof(int));
		return *this;
	}
	test &operator=(test &&obj)
	{
		if (ptr)
			delete[] ptr;
		ptr = obj.ptr;
		obj.ptr = NULL;
		return *this;
	}
};

int _tmain()
{
	test tt1(10), tt2 = tt1;

	test tt3 = std::move(tt2);

	tt3 = tt1;
	tt3 = move(tt1);
	return 0;
}

#if 0
template <class T, int SIZE = 50>
class Stack 
{
private:
	T list[SIZE];
	int top;

	public:
	Stack();
	void push(const T &item);
	T pop();
//	void clear();
//	const T &peek() const{assert(!isEmpty());return list[top];}
	bool isEmpty() const;
	bool isFull() const;
	void display() const;
};

template <class T, int SIZE>
Stack<T,SIZE>::Stack()
{
	top=-1;
}

template <class T, int SIZE>
bool Stack<T,SIZE>::isEmpty() const
{
	return top==-1;
}

template <class T, int SIZE>
bool Stack<T,SIZE>::isFull() const
{
	return top==SIZE-1;
}
/*
template <class T, int SIZE>
void Stack<T,SIZE>::clear()
{
	top=-1;
}*/
template <class T, int SIZE>
void Stack<T,SIZE>::push(const T &item)
{
	assert(!isFull());
	list[++top]=item;
}
template <class T, int SIZE>
T Stack<T,SIZE>::pop()
{
	assert(!isEmpty());
	return list[top--];
}
template <class T, int SIZE>
void Stack<T,SIZE>::display() const
{
	assert(!isEmpty());
	for(int i=0; i<=top; i++)
		cout<<list[i]<<endl;
}
/*
template<class T>
class Store
{
};

template class Store<double>;*/

template <>
class Stack<bool, 32> 
{
private:
	unsigned list;
	int top;
public:
	Stack():top(-1){}
	void push(bool item);
	bool pop();
//	void clear();
//	bool peek() const;
	bool isEmpty() const;
	bool isFull() const;
};

bool Stack<bool, 32>::isFull() const
{
	return top==32-1;
}

bool Stack<bool, 32>::isEmpty() const
{
	return top==-1;
}
void Stack<bool, 32>::push(bool item) {
	assert(!isFull());
	++top;
	list = (list << 1) | (item ? 1 : 0);
}

bool Stack<bool, 32>::pop() {
	assert(!isEmpty());	
	bool result = ((list & 1) == 1);
	list >>= 1; --top; 
	return result;		
}

template <int SIZE>
class Stack<bool, SIZE>
{
private:
	enum {
		UNIT_BITS = sizeof(unsigned) * 8,
		ARRAY_SIZE = (SIZE - 1) / UNIT_BITS + 1
	};
	unsigned list[ARRAY_SIZE];
	int top;	
public:
	Stack():top(-1){}
	void push(bool item);
	bool pop();
	//void clear();
	//bool peek() const;
	bool isEmpty() const; 
	bool isFull() const;
};

template <int SIZE>
void Stack<bool, SIZE>::push(bool item) 
{
	assert(!isFull());
	int index = ++top / UNIT_BITS;
	list[index] = (list[index] << 1) | (item ? 1 : 0);
}

template <int SIZE>
bool Stack<bool, SIZE>::pop()
{
	assert(!isEmpty());
	int index = top-- / UNIT_BITS;
	bool result = ((list[index] & 1) == 1);
	list[index] >>= 1; 
	return result;
}

template <int SIZE>
bool Stack<bool, SIZE>::isFull() const
{
	return top==32-1;
}
template <int SIZE>
bool Stack<bool, SIZE>::isEmpty() const
{
	return top==-1;
}

void main()
{
	
	Stack<int,100> st;

	st.push(10);
	st.push(20);
	cout<<st.pop()<<endl;

	st.display();

	Stack<bool,32> st1;
	st1.push(1);

	Stack<bool,64> st2;
	st2.push(1);
}
#endif
