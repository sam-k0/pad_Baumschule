#include <iostream>
#include "binarysearchtree.h"
#include "mathedealer.h" // Hole den mathe-mann ins programm😁

using namespace std;
void fillRandom(int countNodes, int minVal, int maxVal, BinarySearchTree<int>* tree)
{
    int rand;
    Node<int>* n;


    for(int i = 0; i<countNodes;i++)
    {

        rand = Num_random(minVal,maxVal);
        n = new Node<int>;
        n->setData(rand);
        tree->insert(n);
    }

}

void showInterface()
{
    cout << "1: Insert (Value)\n 2: Delete (Key)\n 3: Rotate left (Key)\n 4: Rotate right (Key)\n 5: Fill random\n"<<
            "6: Exit\n 7: Init from File\n 8: Dump to file \n 9: print"<<endl;
}


int main()
{
    cout << "Hello World!" << endl;
    bool continuecond = true; // QUit program
    BinarySearchTree<int>* tree = new BinarySearchTree<int>;
    int index = 0;
    int param = 0;
    Node<int>* node;

    while(continuecond)
    {
        try {
            showInterface();

            // Get the input
            cin >> index;
            switch(index) // react to input
            {
                case 1: // Insert (Value)
                cout << "data? (int): ";
                cin >> param;

                node = new Node<int>;
                node->setData(param);
                tree->insert(node);
                cout << "Inserted."<<endl;
                break;

                case 2: // Delete (Key)
                cout << "Delete what key?: ";
                cin >> param;

                tree->del(param);
                cout << "Deleted."<<endl;
                break;

                case 3:
                cout << "Rotate (left) what key?: ";
                cin >> param;

                tree->rotateLeft(param);
                cout << "Rotated."<<endl;
                break;

                case 4:
                cout << "Rotate (right) what key?: ";
                cin >> param;

                tree->rotateRight(param);
                cout << "Rotated."<<endl;
                break;

                case 5:
                if(tree->rootEmpty())
                {
                    cout << "Filling tree with 10 nodes with values from 1-100"<<endl;
                    fillRandom(10,1,100,tree);
                }
                else
                {
                    cout << "Tree already exists."<<endl;
                }
                break;

                case 6:
                delete tree;
                continuecond = false;
                break;

                case 7:
                if(tree->rootEmpty())
                {
                    cout << "Loading from file"<<endl;
                    tree->initTree();
                }else
                {
                    cout << "Couldnt load: Tree exists already"<<endl;
                }
                break;

                case 8:
                cout << "Dumping tree to file"<<endl;
                tree->dump();
                cout <<"Done."<<endl;
                break;

                case 9:
                if(!tree->rootEmpty())
                {
                    cout<<"How would you like to print? (1 PRE /2 IN /3 POST /4 DEFAULT):"<<endl;
                    cin >> param;
                    cout << "ROOT<-------------------->DEPTH"<<endl;
                    switch (param)
                    {
                        case 1:
                        tree->getRoot()->printPreOrder(" ");
                        break;

                        case 2:
                        tree->getRoot()->printInOrder(" ");
                        break;

                        case 3:
                        tree->getRoot()->printPostOrder(" ");
                        break;

                        case 4:
                        tree->print();
                        break;
                    }
                }
                else
                {
                    cout << "Cannot print empty tree."<<endl;
                }
                break;



                default:
                cout << "couldn't process your input."<<endl;
            }



        }  catch (...) {
            cout << "Exception catched in main loop."<<endl;
        }
    }









    tree->initTree();
    tree->print();
    tree->dump();
/* Tilos baum
    Node<int>* n = new Node<int>;
    n->setData(4);
    tree->insert(n);

    n = new Node<int>;
    n->setData(2);
    tree->insert(n);

    n = new Node<int>;
    n->setData(6);
    tree->insert(n);


    n = new Node<int>;
    n->setData(1);
    tree->insert(n);


    n = new Node<int>;
    n->setData(3);
   tree->insert(n);

    n = new Node<int>;
    n->setData(5);
    tree->insert(n);

    n = new Node<int>;
    n->setData(7);
    tree->insert(n);

    tree->dump();


//*/
/*
    Node<int>* n = new Node<int>;
    n->setData(4);
    tree->insert(n);

    n = new Node<int>;
    n->setData(2);
    tree->insert(n);

    n = new Node<int>;
    n->setData(6);
    tree->insert(n);


    n = new Node<int>;
    n->setData(7);
    tree->insert(n);


    n = new Node<int>;
    n->setData(8);
   tree->insert(n);

    n = new Node<int>;
    n->setData(9);
    tree->insert(n);

    n = new Node<int>;
    n->setData(22);
    tree->insert(n);

    tree->print();

    tree->balance(tree->getRoot());


    //cout<<"left: "<<tree->getDepthRight(tree->getRoot());
*/

    // Loeschen test
    /*fillRandom(6,1,100,tree);


    tree->print();

    cout << "Entferne:"<<endl;

    tree->del(9);

    tree->print();
    //*/

    // Depth test
    /*
    int rs=fillRandom(6,1,100,tree); // 6 elemente mit werten 1-100



    tree->getRoot()->levelOrderTraverse(tree->getRoot());

    tree->print();*/

    // get
    /*
    fillRandom(10,1,100,tree); // 6 elemente mit werten 1-100

    tree->print();
*/



    cout << "Ende"<<endl;
    return 0;
}
