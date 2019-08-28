/*
	Operaciones BST Pt 2
	Ricardo López Rodríguez a01066515
	
*/
#include <iostream>
#include "BST.h"
using namespace std;

int main() {


	BST<int> bst;	
	bool b = true;

	bst.add(25);
	bst.add(13);
	bst.add(24);
	bst.add(5);
	bst.add(34);
	bst.add(2);
	bst.add(8);
	bst.add(22);
	bst.add(11);
	bst.add(4);
	bst.add(23);

	BST<int> bst2(bst);
	
	cout << "Preorder bst" << endl;
	bst.print(1);
	cout << endl;
	cout << "Preorder bst2" << endl;
	bst2.print(1);
	cout << endl;

	cout << "Max Width" << endl;
	cout << bst.maxWidth() << endl;

	cout << "Comparacion de dos ABB" << endl;
	b = (bst == bst2);
	cout << b << endl;

	cout << "nearstRelative" << endl;
	cout << bst.nearstRelative(2,22) << endl;

	cout << "IsBalanced" << endl;
	cout << bst.isBalanced() <<endl;

	cout << "Nodos en X nivel" << endl;
	cout << bst.nodosXNivel(5) << endl;
	
	cout << "Hijos del hijo" << endl;
	bst.hijosDelHijo(5);
	cin.get();
	return 0;
}
