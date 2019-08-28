#ifndef Node_h
#define Node_h

template <class T>
class Node {
public:
	Node();
	Node(T d);
	void setData(T d);
	void setLeft(Node<T>* l);
	void setRight(Node<T>* r);
	T getData();
	Node<T>* getLeft();
	Node<T>* getRight();
private:
	T data;
	Node<T>* left;
	Node<T>* right;
};

template <typename T>
Node<T>::Node()
{
	left = NULL;
	right = NULL;
}

template <typename T>
Node<T>::Node(T d)
{
	left = NULL;
	right = NULL;
	data = d;
}

template <typename T>
void Node<T>::setData(T d)
{
	data = d;
}

template <typename T>
void Node<T>::setLeft(Node<T>* l)
{
	left = l;
}

template <typename T>
void Node<T>::setRight(Node<T>* r)
{
	right = r;
}

template <typename T>
T Node<T>::getData()
{
	return data;
}

template <typename T>
Node<T>* Node<T>::getLeft()
{
	return left;
}

template <typename T>
Node<T>* Node<T>::getRight()
{
	return right;
}

#endif
