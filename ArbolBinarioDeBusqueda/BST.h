//
//  BST.h
//  ABB_Clase
//
// 

#ifndef BST_h
#define BST_h

#include "Node.h"
#include<stack>
#include <queue>
using namespace std;

template <class T>
class BST {
public:
	BST();
	BST(const BST<T> &bst);
	~BST();
	bool isEmpty();
	bool add(T d);
	bool find(T d);
	bool del(T d);
	void print(int n);
	void clear();
	int height();
	void ancestors(T d);
	int getLevelForValue(T d);
	bool operator == (BST<T> bst);
	void printLeaves();
	int count();
	void recorridoCount(Node<T>* r, int &count);
	int nearstRelative(T d1, T d2);
	int maxWidth();
	bool isBalanced();
	int nodosXNivel(int level);
	void hijosDelHijo(T d);


private:
	Node<T>* root;
	void heightCounter(Node<T>* r, int & count);
	void recorridoComprativo(Node<T>* r, queue<T>&queue);
	void preorder(Node<T>* r);
	void inorder(Node<T>* r);
	void postorder(Node<T>* r);
	void deleteAll(Node<T>* r);
	T predecessor(Node<T>* r);
	T successor(Node<T>* r);
	int getChildCount(Node<T>* r);
	void printLevels(Node<T>* r);
	int heightNum; 
	void recorridoHojas(Node<T>* r);
	void recorridoMaxWidth(Node<T>* aux, Node<T>* aux2);
	void heightCounter2(Node<T>* r, int & count, int (&arr)[100], int &size);
	void segundoRecorridoBalanced(Node<T>* r, int &countL, int &countR, Node<T> *auxRoot, int &heightR, int &heightL);
	void recorridoBalanced(Node<T>* r, bool &balanced);
	void recorridoNivel(Node<T>* r, int level, int & nodosNum, int & count);
	void recorridoHijos(Node<T>* r, Node<T>* aux);
	
};

template <typename T>
BST<T>::BST()
{
	root = nullptr;
	heightNum = 0;
}

template <typename T>
BST<T>::~BST()
{
	deleteAll(root);
}

template<typename T>
BST<T>::BST(const BST<T> &bst) {
	root = nullptr;
	queue<T> queue;
	Node<T>* father = nullptr;
	Node<T>* aux = root;
	recorridoComprativo(bst.root, queue);


	while (!queue.empty())
	{
		add(queue.front());
		queue.pop();
	}

/*

	int length = queue.size();
	cout << length << endl;
	for (int i = 0; i < length; i++) {

		while (aux != nullptr)
		{
			father = aux;
			aux = (queue.front() > aux->getData()) ? aux->getRight() : aux->getLeft();
		}

		if (father == nullptr)
		{
			root = new Node<T>(queue.front());
			queue.pop();
		}
		else
		{
			if (queue.front() > father->getData())
			{
				father->setRight(new Node<T>(queue.front()));
				queue.pop();
			}
			else
			{
				father->setLeft(new Node<T>(queue.front()));
				queue.pop();
			}
		}
	}
*/
}

template <typename T>
void BST<T>::deleteAll(Node<T>* r)
{
	if (r != nullptr)
	{
		deleteAll(r->getLeft());
		deleteAll(r->getRight());
		delete r;
	}
}

template <typename T>
void BST<T>::clear()
{
	deleteAll(root);
}

template <typename T>
bool BST<T>::find(T d)
{
	Node<T>* aux = root;
	while (aux != nullptr)
	{
		if (aux->getData() == d)
		{
			return true;
		}
		aux = (aux->getData() > d) ? aux->getLeft() : aux->getRight();
	}
	return false;
}

template <typename T>
bool BST<T>::add(T d)
{
	Node<T>* father = nullptr;
	Node<T>* aux = root;
	// Buscar la posicion
	while (aux != nullptr)
	{
		if (aux->getData() == d)
		{
			return false;
		}
		father = aux;
		aux = (aux->getData() > d) ? aux->getLeft() : aux->getRight();
	}

	// Crear el Nodo
	if (father == nullptr)
	{
		root = new Node<T>(d);
	}
	else
	{
		if (father->getData() > d)
		{
			father->setLeft(new Node<T>(d));
		}
		else
		{
			father->setRight(new Node<T>(d));
		}
	}
	return true;
}

template <typename T>
bool BST<T>::isEmpty()
{
	return (root == nullptr);
}

template <typename T>
void BST<T>::preorder(Node<T>* r)
{
	if (r != nullptr)
	{
		cout << r->getData() << " ";
		preorder(r->getLeft());
		preorder(r->getRight());
	}
}

template <typename T>
void BST<T>::inorder(Node<T>* r)
{
	if (r != nullptr)
	{
		inorder(r->getLeft());
		cout << r->getData() << " ";
		inorder(r->getRight());
	}
}

template <typename T>
void BST<T>::postorder(Node<T>* r)
{
	if (r != nullptr)
	{
		postorder(r->getLeft());
		postorder(r->getRight());
		cout << r->getData() << " ";
	}
}

template <typename T>
void BST<T>::print(int n)
{
	switch (n) {
	case 1:
		preorder(root);
		break;
	case 2:
		inorder(root);
		break;
	case 3:
		postorder(root);
		break;

	case 5:
		printLevels(root);
		break;
	default:
		cout << "ERROR" << endl;
		break;
	}
}

template <typename T>
T BST<T>::predecessor(Node<T>* r)
{
	Node<T>* aux = r->getLeft();
	while (aux != nullptr && aux->getRight() != nullptr)
	{
		aux = aux->getRight();
	}
	return aux->getData();
}

template <typename T>
T BST<T>::successor(Node<T>* r)
{
	Node<T>* aux = r->getRight();
	while (aux != nullptr && aux->getLeft() != nullptr)
	{
		aux = aux->getLeft();
	}
	return aux->getData();
}

template <typename T>
int BST<T>::getChildCount(Node<T>* r)
{
	return (r->getLeft() != nullptr ? 1 : 0) + (r->getRight() != nullptr? 1 : 0);
}

template <typename T>
bool BST<T>::del(T d)
{
	Node<T>* father = nullptr;
	Node<T>* aux = root;
	while (aux != nullptr && aux->getData() != d)
	{
		father = aux;
		aux = (aux->getData() > d) ? aux->getLeft() : aux->getRight();
	}
	if (aux == nullptr)
	{
		return false;
	}
	int count = getChildCount(aux);
	if (count == 0)
	{
		// Nodo hoja
		if (father == nullptr)
		{
			// Solo hay un nodo en el arbol, el arbol queda vacio despues de eliminarlo
			root = nullptr;
		}
		else
		{
			// Liberar el lado correcto del padre, dependiendo de como son los datos
			if (father->getData() > d)
			{
				father->setLeft(nullptr);
			}
			else
			{
				father->setRight(nullptr);
			}
		}
		delete aux;
	}
	else if (count == 1)
	{
		// Nodo con un hijo
		if (father == nullptr)
		{
			root = (aux->getLeft() != nullptr) ? aux->getLeft() : aux->getRight();
		}
		else
		{
			if (father->getData() > d)
			{
				if (aux->getLeft() != nullptr)
				{
					// El hijo esta del lado izq del aux
					father->setLeft(aux->getLeft());
				}
				else
				{
					// El hijo esta del lado der del aux
					father->setLeft(aux->getRight());
				}
			}
			else
			{
				if (aux->getLeft() != nullptr)
				{
					father->setRight(aux->getLeft());
				}
				else
				{
					father->setRight(aux->getRight());
				}
			}
		}
		delete aux;
	}
	else
	{
		// Nodo con dos hijos
		T pred = predecessor(aux);
		del(pred);
		aux->setData(pred);
	}
	return true;
}

template<typename T>
void BST<T>::heightCounter(Node<T>* r, int &count) {

	if (r != nullptr)
	{
		count++;
		if (count > heightNum )
		{
			heightNum = count;
		}
		heightCounter(r->getLeft(), count);
		heightCounter(r->getRight(), count);
		count --;
	}
}

template<typename T>
int BST<T>::height() {
	int count = 0;
	this->heightCounter(root, count);
	return heightNum;
}

template <typename T>
void BST<T>::ancestors(T d) {
	Node<T>* aux = root;
	if (aux != nullptr)
	{
		Node<T>* father = nullptr;
		stack<T> stack;
		bool botton = true;

		while (aux != nullptr)
		{
			if (aux->getData() == d)
			{
			
				while (!stack.empty())
				{
					cout << stack.top() << " ";
					stack.pop();
				}
		
				return;
			}
			else
			{
				father = aux;
				stack.push(father->getData());
				aux = (aux->getData() > d) ? aux->getLeft() : aux->getRight();
			}
			
				
			
		}


		
	}
	cout << "No se encuentra dato" << endl;
	cout << endl;

}

template<typename T>
int BST<T>::getLevelForValue(T d) {
	Node<T> *aux = root;
	int level = 0;

	if (root != nullptr) {
		while (aux != nullptr)
		{
			
			if (aux->getData() == d)
			{
				return level;
			}
			else
			{
				if (d > aux->getData())
				{
					aux = aux->getRight();
					level++;
				}
				else 
				{
					aux = aux->getLeft();
					level++;
				}
			}
		}
		return -1;
	}
	return -1;
}

template<typename T>
void BST<T>::printLevels(Node<T> *r) {
	queue<Node<T>*> queue;

	if (r != nullptr)
	{
		queue.push(r);
		Node<T> *aux = nullptr;

		while (!queue.empty())
		{
			aux = queue.front();
			queue.pop();
			cout << aux->getData() << " ";
			
			if (aux->getLeft() != nullptr)
			{
				queue.push(aux->getLeft());
			}
			if (aux->getRight() != nullptr)
			{
				queue.push(aux->getRight());
			}
		}
	}
	cout << endl;
}


template<typename T>
bool BST<T>:: operator == (BST<T> bst){

	queue<T> queue, queue2;
	int size = 0;

	if (this->root != nullptr && bst.root != nullptr)
	{
		recorridoComprativo(root, queue);
		recorridoComprativo(bst.root, queue2);
		size = queue.size();

		for (int i = 0; i < size; i++)
		{
			if (queue.front() != queue2.front()) {
				return false;
			}
			queue.pop();
			queue2.pop();
		}
	}
	else
	{
		return false;
	}
	
	return true;
}

template<typename T>
void BST<T>:: recorridoComprativo(Node<T>* r, queue<T> &queue ) {
	if (r != nullptr)
	{
		queue.push(r->getData());
		recorridoComprativo(r->getLeft(),queue );
		recorridoComprativo(r->getRight(), queue);
	}
}	

template<typename T>
int BST<T>::nearstRelative(T d1, T d2) {
	Node<T>* aux = root;
	Node<T>* aux2 = root;
	stack<T> stack;

	if (root != nullptr)
	{
		while (aux != nullptr && aux2 != nullptr)
		{
			if (aux->getData() == aux2->getData())
			{
				stack.push(aux->getData());
			}
			else
			{
				return stack.top();
			}
			aux = (d1 > aux->getData()) ? aux->getRight() : aux->getLeft();
			aux2 = (d2 > aux2->getData()) ? aux2->getRight() : aux2->getLeft();
		}

	}
	else {
		cout << "ABB vacio" << endl;
	}

}

template<typename T>
int BST<T>::maxWidth() {
	int arr[100] = {};
	int max = 0, size = 0;
	int count = 0;
	heightCounter2(root, count, arr, size);
	
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	return max;
}

template<typename T>
void BST<T>::heightCounter2(Node<T>* r, int &count, int (&arr)[100], int &size) {

	if (r != nullptr)
	{
		count++;
		arr[count-1] += 1;
		if (count > size)
		{
			size = count;
		}
		heightCounter2(r->getLeft(), count, arr, size);
		heightCounter2(r->getRight(), count, arr, size);
		count--;
	}
}

template<typename T>
bool BST<T>::isBalanced() {
	bool balanced = true;
	if (root != nullptr)
	{
		recorridoBalanced(root, balanced);
		return balanced;
	}
	
}

template<typename T>
void BST<T>::recorridoBalanced(Node<T> *r, bool &balanced) {

	if (r != nullptr)
	{	
		Node<T> *auxRoot = r;
		int countR = 0;
		int countL = 0;
		int balancedFactor = 0;
		int heightR = 0;
		int heightL = 0;

		segundoRecorridoBalanced(r, countL, countR, auxRoot, heightR, heightL);

		balancedFactor = heightR - heightL;
		cout << "BF: "<< balancedFactor << endl;

		if (balancedFactor > 1 || balancedFactor < -1)
		{
			balanced = false;
		}
		recorridoBalanced(r->getLeft(), balanced);
		recorridoBalanced(r->getRight(), balanced);
	}
}

template<typename T>
void BST<T>::segundoRecorridoBalanced(Node<T> *r, int &countL, int &countR, Node<T> *auxRoot, int &heightR, int &heightL) {

	if (r != nullptr)
	{
		if (r->getData() < auxRoot->getData() || r->getData() == auxRoot->getData())
		{
			countL ++;
			if (countL > heightL)
			{
				heightL = countL;

			}
		}
		if (r->getData() > auxRoot->getData() || r->getData() == auxRoot->getData())
		{
			countR ++;
			if (countR > heightR)
			{
				heightR = countR;
			}
		}

		segundoRecorridoBalanced(r->getLeft(), countL, countR, auxRoot, heightR, heightL);
		segundoRecorridoBalanced(r->getRight(), countL, countR, auxRoot, heightR, heightL);

		if (r->getData() < auxRoot->getData())
		{
			countL --;
		}
		else
		{
			countR --;
		}
	}
}

template<typename T>
int BST<T>::nodosXNivel(int level) {
	int nodosNum = 0, count = 0;
	if (root != nullptr) {
		recorridoNivel(root, level, nodosNum, count);
		return nodosNum;
	}
}

template<typename T>
void BST<T>::recorridoNivel(Node<T> *r, int level, int &nodosNum, int &count) {
	if (r != nullptr)
	{
		count++;
		if (count == level)
		{
			nodosNum ++;
		}
		recorridoNivel(r->getLeft(), level, nodosNum, count);
		recorridoNivel(r->getRight(), level,nodosNum, count);
		count--;
	}
}

template<typename T>
void BST<T>::hijosDelHijo(T d) {
	Node<T>* aux = root;
	Node<T>* aux2;
	if (root != nullptr)
	{
		while (aux != nullptr)
		{
			if (aux->getData() == d)
			{
				aux2 = aux;
				recorridoHijos(aux, aux2);
				return;
			}
			aux = (d > aux->getData()) ? aux->getRight() : aux->getLeft();
		}
	}
}

template< typename T>
void BST<T>::recorridoHijos(Node<T> *r, Node<T> *aux) {
	if (r != nullptr)
	{
		if (r->getData() != aux->getData())
		{
			cout << r->getData() << endl;
		}
		recorridoHijos(r->getLeft(), aux);
		recorridoHijos(r->getRight(), aux);

	}
}

//Ejercicios de clase...
template<typename T>
void BST<T>::printLeaves() {
	if (root != nullptr) {
		recorridoHojas(root);
	}
	else
	{
		cout << "ABB vacio" << endl;
	}
}

template<typename T>
void BST<T>::recorridoHojas(Node<T>*r) {

	if (r != nullptr)
	{
		if (r->getLeft() == nullptr && r->getRight() == nullptr)
		{
			cout << r->getData() << endl;
		}
		recorridoHojas(r->getLeft());
		recorridoHojas(r->getRight());
	}
}

template<typename T>
int BST<T>::count() {
	int count = 0;
	if (root != nullptr)
	{
		recorridoCount(root,count);
		return count;
	}
	else
	{
		cout << "ABB vacio" << endl;
	}
}

template<typename T>
void BST<T>::recorridoCount(Node<T>*r, int &count) {

	if (r != nullptr)
	{
		count ++; 
		recorridoCount(r->getLeft(), count);
		recorridoCount(r->getRight(), count);
	}
}

#endif