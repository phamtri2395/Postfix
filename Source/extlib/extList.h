/** extList.h

    A set of Data Structures based on Doubly Linked List

	@docdate 10/11/2015
    @author phamtri2395@gmail.com
*/

#ifndef _EXTLIST_
#define _EXTLIST_

/* Define */
#define NULL 0

/* Node class using template */
template <class T>
class Node {
public:
	/* Variables */
	T value;
	Node<T>* prev;
	Node<T>* next;

	/* Constructors & Destructors */
	Node(const T&, Node<T>*, Node<T>*);
};

/* Implementations */

template <class T>
inline Node<T>::Node(const T& _value, Node* _prev = NULL, Node* _next = NULL) {
	value = _value;
	prev = _prev;
	next = _next;
}




/* LinkedList class using template */
template <class T>
class linkedList {
protected:
	/* Variables */
	Node<T>* head;
	Node<T>* tail;
public:
	/* Constructors & Destructors */
	linkedList();
	~linkedList();

	/* Function prototypes */
	bool is_empty();
	void pushHead(const T&);
	T popHead();
	void pushTail(const T&);
	T popTail();
};

/* Implementations */

template <class T>
linkedList<T>::linkedList() {
	head = tail = NULL;
}
template <class T>
linkedList<T>::~linkedList() {
	while (head != tail) {
		head = head->next;
		delete head->prev;
	}

	if (head != NULL) delete head;
}

template <class T>
bool linkedList<T>::is_empty() {
	return (head == NULL);
}
template <class T>
void linkedList<T>::pushHead(const T& value) {
	if (head != NULL) {
		head = new Node<T>(value, NULL, head);
		head->next->prev = head;
	}
	else head = tail = new Node<T>(value, NULL, NULL);
}
template <class T>
T linkedList<T>::popHead() {
	T temp = head->value;
	if (head == tail) {
		delete head;
		head = tail = NULL;
	} else {
		head = head->next;
		delete (head->prev);
		head->prev = NULL;
	}

	return temp;
}
template <class T>
void linkedList<T>::pushTail(const T& value) {
	if (head != NULL) {
		tail = new Node<T>(value, tail, NULL);
		tail->prev->next = tail;
	}
	else head = tail = new Node<T>(value, NULL, NULL);
}
template <class T>
T linkedList<T>::popTail() {
	T temp = tail->value;
	if(head == tail) {
		delete tail;
		head = tail = NULL;
	} else {
		tail = tail->prev;
		delete tail->next;
		tail->next = NULL;
	}

	return temp;
}




/* Stack class inherits from LinkedList class */
template <class T>
class Stack: private linkedList<T> {
public:
	/* Function prototypes */
	bool isEmpty();
	T peek();
	void push(const T&);
	T pop();
};

/* Implementations */

template <class T>
bool Stack<T>::isEmpty() {
	return is_empty();
}
template <class T>
T Stack<T>::peek() {
	return tail->value;
}
template <class T>
void Stack<T>::push(const T& value) {
	pushTail(value);
}
template <class T>
T Stack<T>::pop() {
	return popTail();
}




/* Queue class inherits from LinkedList class */
template <class T>
class Queue: private linkedList<T> {
public:
	/* Function prototypes */
	bool isEmpty();
	T peek();
	void enqueue(const T&);
	T dequeue();
};

/* Implementations */

template <class T>
bool Queue<T>::isEmpty() {
	return is_empty();
}
template <class T>
T Queue<T>::peek() {
	return head->value;
}
template <class T>
void Queue<T>::enqueue(const T& value) {
	pushTail(value);
}
template <class T>
T Queue<T>::dequeue() {
	return popHead();
}
#endif