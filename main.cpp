#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <random>
using std::string;
using std::endl;
using std::cout;
using std::vector;

int main(){
	
	cout << "Test: " << endl;
	RedBlackTree<int> tree;
	int nTwo = 1000;

    for (int i = 0; i < nTwo; i++)
    {
        tree.insert(rand() % nTwo);
    }

    // print before remove
 

    std::cout << ("------INSERTION COMPLETE------") << std::endl;

    for (int i = 0; i < nTwo; i++)
    {
        tree.remove(i);
    }

    //print after




	
	statistics("note.txt");

	/*
	RedBlackTree<int> tree;
	tree.insert(41);
	
	tree.insert(32);
	tree.insert(23);
	tree.insert(61);
	tree.insert(25);
	tree.insert(87);
	tree.insert(65);
	tree.insert(45);
	tree.insert(43);
	tree.insert(23);
	tree.insert(56);
	tree.insert(44);
	tree.insert(40);
	tree.insert(90);
	tree.insert(78);
	tree.insert(98);
	tree.insert(53);
	tree.insert(25);
	tree.insert(15);
	tree.insert(17);
	tree.insert(13);
	tree.insert(18);
	tree.insert(26);
	tree.insert(69);
	tree.insert(72);
	tree.insert(61);
	tree.insert(51);
	tree.insert(21);
	tree.insert(11);
	
	tree.print();
	
	tree.remove(41);
	
	tree.remove(32);
	tree.remove(23);
	tree.remove(61);
	tree.remove(25);
	tree.remove(87);
	tree.remove(65);
	tree.remove(45);
	tree.remove(43);
	tree.remove(23);
	tree.remove(56);
	tree.remove(44);
	tree.remove(40);
	tree.remove(90);
	tree.remove(78);
	tree.remove(98);
	tree.remove(53);
	tree.remove(25);
	tree.remove(15);
	tree.remove(17);
	tree.remove(13);
	tree.remove(18);
	tree.remove(26);
	tree.remove(69);
	tree.remove(72);
	tree.remove(61);
	tree.remove(51);
	tree.remove(21);
	tree.remove(11);
	
	tree.print();
	
    // Int Tree Tests	
	RedBlackTree<int> rb1;
	if (rb1.insert(42)) cout << "inserted 42" << endl;
	rb1.insert(71);
	rb1.insert(13);
	rb1.insert(44);
	rb1.insert(33);
	RedBlackTree<int> rb2(rb1);
    
    rb1.print();
	if (rb1.remove(13)) cout << "removed 13" << endl;
	if (rb1.search(42)) cout << "found 42" << endl;
	//RedBlackTree rb2(rb1);
	rb1.print();

	//rb1.print();
    rb2.print();
	RedBlackTree<int> rb3 = rb1;
	rb3.print();
   
	vector<int> v1 = rb1.search(50, 100); //should contain 71
	for (int i=0; i<v1.size(); i++){
		cout << v1.at(i) << endl;
	}


	vector<int> v2 = rb1.values(); //should contain {42,71}
	for (int i=0; i<v2.size(); i++){
		cout << v2.at(i) << endl;
	}
	
	
	cout << "closestLess(50) = " << rb1.closestLess(50) << endl;
	cout << "closestGreater(33) = " << rb1.closestGreater(33) << endl;
    

	cout << "size = " << rb1.size() << endl; //should be 2



	cout << endl << endl << "Real Test: " << endl;
	// Real test
	RedBlackTree<int> tree1;
	tree1.insert(75);
	tree1.insert(15);
	tree1.insert(100);
	tree1.insert(150);
	tree1.insert(88);
	tree1.insert(55);
	tree1.insert(10);

	// EXTRA nodes

	// 2 extra on the left side

	tree1.insert(60);
	tree1.insert(65);

	// 3 extra in the middle section of the tree

	tree1.insert(60);
	tree1.insert(80);
	tree1.insert(77);
	
	tree1.print();
	*/
}