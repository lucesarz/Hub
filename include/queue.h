//queue.h
#ifndef QUEUE_H_
#define QUEUE_H_
#include"hubDefs.h"
#include <cstddef>
#include <cstdio>
template <typename T>
class Queue
{
private:
	struct Node { T item; struct Node * next;};
	const static int Q_SIZE = 10;
	Node * front;												// pointer to front of Queue
	Node * rear;												// pointer to rear of Queue
	int count;													// current number of items in Queue

	// preemptive definitions to prevent public copying
//	Queue & operator=(const Queue & q) {return *this;};

public:
	Queue();										// create queue with a qs limit
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const T &);									// add item to end
	bool dequeue(T &);											// remove item from front
};

template<typename T>
Queue<T>::Queue()
{   
    count = 0;
    front = NULL; 
    rear = NULL;
}
template <typename T>
Queue<T>::~Queue()
{
    Node * temp;    
    while(front != (void *) 0)  
    {   
        temp = front;
        front = front->next;
        delete temp;    
    }   
}

template <typename T>
bool Queue<T>::isempty() const
{
    return count == 0;
}

template <typename T>
bool Queue<T>::isfull() const
{
    return count == Q_SIZE;
}

template <typename T>
int Queue<T>::queuecount() const
{
    return count;
}

template <typename T>
bool Queue<T>::enqueue(const T &data)   
{
    if(isfull())    
        return false;

    Node * add = new Node;    
    add->item = data;    
    add->next = NULL;
    count++;
    if (front == NULL)
        front = add;    
    else
       rear->next = add;   
    rear = add;    
    return true;
}

template <typename T>
bool Queue<T>::dequeue(T &data)    
{
    if(front == NULL)    
        return false;

    data = front->item;    
    count--;    
    Node * temp = front;
    front = front->next;
    delete temp;    

    if (count == 0)
        rear = NULL;

    return true;
}
#endif /* QUEUE_H_ */
