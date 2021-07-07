#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "node.h"
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
template<typename T>

class BinarySearchTree
{
private:
    Node<T>* root;
    std::stringstream outstream;

public:
    BinarySearchTree()
    {
        root = nullptr;
    }

    ~BinarySearchTree()
    {
        if(!rootEmpty())
        {
            root->wipeSubtree(true);
        }
    }

    bool rootEmpty() // Checks if the root node is empty (nullptr)
    {
        if(root == nullptr)
            return true;
        else
            return false;
    }

    void print()
    {
        if(!rootEmpty())
        {
            root->print(" ");
        }
    }

    Node<T>* getByKey(int key) // Get a node by key
    {
        Node<T>* result = nullptr; // set return val
        try{
            if(!rootEmpty())           // if !empty, search recursive
            {
                result = root->searchByKey(key);

                if(result == nullptr)
                {
                    throw runtime_error("Node not found: In tree");
                }
            }
            else
            {
                throw runtime_error("Node not found: Root empty");
            }
        }
        catch(runtime_error e)
        {
            cout <<"Exception thrown at: getByKey(): " <<e.what()<<endl;
        }
        return result;              // return result
    }

    void insert(Node<T>* toAdd) // Insert by data value
    {
        string keystr = "";
        if(rootEmpty()) // root was empty
        {
            root = toAdd;
            root->setKey(1);
            return;
        }
        // insert somewhere else
        root->insert(toAdd,keystr);

    }

    void del(int searchKey) // Delete by key
    {
        Node<T>* n = nullptr;
        try{
            if(!rootEmpty())
            {
                n = getByKey(searchKey); // Check if in tree
                if(n == nullptr) // it is not in tree
                {
                    throw invalid_argument("Not in tree");
                }
                else
                {
                    root->deleteRec(root,searchKey);
                }
            }
            else
            {
                throw invalid_argument("Tree empty");
            }
        }
        catch(invalid_argument e)
        {
            cout <<"Exception thrown at: del(): " <<e.what() << endl;
        }
    }
    // Get set
    Node<T>* getRoot()          // Get the root
    {
        return root;
    }

    bool setRoot(Node<T>* value) // Set the root
    {
        if(root == nullptr)
        {
            root = value;
            return true;
        }

        return false;
    }

    void update_keys()  //nach Baumänderung Schlüssel alle richtig aktualisieren
    {
        update_keys(root, "1"); // First step with 1 as key
    }

    void update_keys(Node<T>* node, std::string key)    //Helfer
    {
        node->setKey(stoull(key));  // setze neu

        if(node->getLeft()!=nullptr)
        {
            update_keys(node->getLeft(), key+'0');
        }

        if(node->getRight()!=nullptr)
        {
            update_keys(node->getRight(), key+'1');
        }
        return;
    }

    Node<T>* rotateLeft(int key)
    {
        Node<T>* x;                 //Teilbaumwurzel
        Node<T>* x_parent;          //Wurzelvater
        int x_parent_key;   //Wurzelvater Schlüssel

        x=getByKey(key); // Convert the string to int

        if(x->getRight()==nullptr) // Schaue ob rechtes kind existiert
            throw std::invalid_argument("Error in \"BinarySearchTree::rotate_l(...)\": Can not rotate if right subtree is empty.\n");

        x_parent_key=key;                                   //Vaterschlüssel
        if(key!=1)       //wenn x nicht Wurzel: Vater holen
        {
            string strkey = to_string(key);
            strkey.erase(strkey.size()-1, 1);   //Zeichen letztes entfernen
            x_parent_key = stoull(strkey);
            x_parent=getByKey(x_parent_key);    //Vater finden
        }
        else
        {//wenn x Wurzel:
            x_parent=nullptr;         //kein Vater
        }


        Node<T>* y=x->getRight();      //zuerst x' Kind rechts, danach x' Vater
        Node<T>* beta=y->getLeft();   //zuerst y Kind links, danach x' Kind rechts


        //rotieren
        x->setRight(beta);
        y->setLeft(x);

        //Wurzelvaterzeiger nachbiegen
        if(x_parent==nullptr)           //wenn über x kein Knoten:
            root=y;                     //y wird Wurzel
        else if(x==x_parent->getLeft())   //wenn x Kind links war:
            x_parent->setLeft(y);        //y neues Kind links
        else if(x==x_parent->getRight())   //wenn x Kind rechts war:
            x_parent->setRight(y);        //y neues Kind rechts
        else
            throw std::runtime_error("Error in \"BinarySearchTree::rotate_l\": x must be child of x' parent.\n");

        update_keys();                  //Schlüssel aktualiseren um
        return y;                       //y ist neuer Wurzelknoten des Teilbaums
    }

    Node<T>* rotateRight(int key)
   {
       Node<T>* y;                 //Teilbaumwurzel
       Node<T>* y_parent;          //Wurzelvater
       int y_parent_key;   //Wurzelvater Schlüssel

       y = getByKey(key); // Hole das rotationselement per schlüssel

       if(y->getLeft()==nullptr)
           throw std::invalid_argument("Error in \"BinarySearchTree::rotate_l(...)\": Can not rotate if left subtree is empty.\n");

       y_parent_key=key;                                   //Vaterschlüssel
       if(key!=1) // checke ob das element die wurzel ist
       {
           string strkey = to_string(key);
           strkey.erase(strkey.size()-1, 1);   //Zeichen letztes entfernen*/

           y_parent_key = stoull(strkey);
           //y_parent_key = int(key/10);
           y_parent=getByKey(y_parent_key);

       }
       else
       {//wenn y Wurzel:
           y_parent=nullptr;       //kein Vater
       }

       Node<T>* x=y->getLeft();      //zuerst y' Kind links, danach y' Vater
       Node<T>* beta=x->getRight();   //zuerst x' Kind rechts, danach y Kind links


       //rotieren
       y->setLeft(beta);
       x->setRight(y);


       //Wurzelvaterzeiger nachbiegen
       if(y_parent==nullptr)           //wenn über y kein Knoten:
           root=x;                     //x wird Wurzel
       else if(y==y_parent->getRight())   //wenn y Kind rechts war:
           y_parent->setRight(x);        //x neues Kind rechts
       else if(y==y_parent->getLeft())   //wenn y Kind links war:
           y_parent->setLeft(x);        //x neues Kind links
       else
           throw std::runtime_error("Error in \"BinarySearchTree::rotate_r\": y must be child of y' parent.\n");

       update_keys();                  //Schlüssel aktualiseren
       return x;                       //x ist neuer Wurzelknoten des Teilbaums
   }

    int getDepthLeft(Node<T>* anchor) // returns depth fro
    {
        int retLeft = 0;
        if(!rootEmpty()) // Check if root is empty
        {
            // Not empty, check tree
            if(anchor->leftExists())
            {
                retLeft += anchor->depth(anchor->getLeft());// Rufe Methode auf Rechtem Kind des ankers auf
            }
            return retLeft;
        }
        else
        {
            return 0;
        }

    }

    int getDepthRight(Node<T>* anchor) // returns depth fro
    {
        int retRight=0;
        if(!rootEmpty()) // Check if root is empty
        {
            // Not empty, check tree
            if(anchor->leftExists())
            {
                retRight += anchor->depth(anchor->getRight()); // Rufe Methode auf Rechtem Kind des ankers auf
            }
            return retRight;
        }
        else
        {
            return 0;
        }

    }

    // Code genommen aus dem internet: https://www.geeksforgeeks.org/level-order-tree-traversal/
    // Ansatz war: wir müssen den Baum level für level ablaufen, um so die einfügereihenfolge
    // aufrecht zu erhalten.
    void levelOrderTraverse(Node<T>* rootnode)
    {
        int h = rootnode->depth(rootnode); // Tiefe von anker

        for(int i = 0; i<= h; i++) // So oft wie der Baum tief ist ablaufen
        {
            doCurrentLevel(rootnode, i);
        }
        cout<<endl;
    }

    void doCurrentLevel(Node<T>* rootnode, int level) // Does the current level
    {
        if(rootnode==nullptr)
        {
            return;
        }
        if(level == 1)          // Wenn levelcounter auf 1: printe sich selbst
        {
            cout <<"|" <<rootnode->getData()<< ",";
            // Append to stream
            outstream << "#Kundennummer: "<<rootnode->getKey()<<endl;
            outstream << "#Name: "<<rootnode->getData()<<endl;
            outstream << "***************"<<endl;
        }
        else if(level > 1) // Wenn die tiefe größer als 1: Gebe weiter an level höher, sodass erst level oben und dann untere level bearbeitet werden
        {                   // level ist quasi als counter, zählt von max. tiefe herunter zu 1: sodass tiefere ebenen (höherer depth wert) später
                            // drankommen.
            cout<<level<<endl;
            doCurrentLevel(rootnode->getLeft(), level -1);
            doCurrentLevel(rootnode->getRight(), level -1);
        }

    }

    void dump() // Dump tree to file
    {
        levelOrderTraverse(root);

        string fname = "E:/QT_projects/Baumschule/dumped.txt"; // Get the filename
        cout << "Dumping database"<<endl;

        ofstream destfile(fname.c_str(), ios::out); // Instanciate a target file

        if(!destfile) // Error handling
        {
            cout << "There was an error while creating the destination file"<<endl;
            return;
        }

        destfile << outstream.rdbuf()<<endl;

        destfile.close();
    }

    void initTree()
    {
        char buffer[300]; // The buffer to write to
        ifstream source;
        string fname = "E:/QT_projects/Baumschule/dumped.txt";


        source.open(fname.c_str(),ios::in);

        if(!source) // Check if something went wrong
        {
            cout << "fuck" << endl;
            return;
        }

        string data;

        while(source.getline(buffer,300))
        {
            if(source.eof()) // Check if eof
            {
                source.close();
                cout << "End of file.";
                return;
            }

            data = buffer; // get from reading buffer to data string
            int readname; // the vars to read the data to
            int readkey; //**



            // Interpret string (data)
            if(data.find("***************") != std::string::npos) // its the read name
            {
                Node<T>* tempElement = new Node<T>; // set the attributes
                tempElement->setData(readname);
                tempElement->setKey(readkey);
                insert(tempElement);                // insert the element
            }

            if(data.find("#Name: ") != std::string::npos) // its the read name
            {
                readname = stoull(data.substr(7,data.size()-7));
            }

            if(data.find("#Kundennummer: ") != std::string::npos) // its the read name
            {
                readkey = stoull(data.substr(15,data.size()-15));
            }
        }

        source.close();


    }



    void balance(Node<T>* anchor)
    {
        int difference = 0; //difference btwn depths
        bool cond = false;

        difference=getDepthLeft(anchor)-getDepthRight(anchor);
        cout << "Difference is: "<<difference<<endl;

        if(std::abs(difference) > 1)
        {
            cond = true;
        }

        while(cond)
        {

            while(difference < -1)
            {
                rotateLeft(anchor->getKey());
                difference=getDepthLeft(anchor)-getDepthRight(anchor);
            }

            while(difference > 1)
            {
                rotateRight(anchor->getKey());
                difference=getDepthLeft(anchor)-getDepthRight(anchor);
            }

            if(std::abs(difference) > 1) // Redetermine condition
            {
                cond = true;
            }
            else
            {
                cond = false;
            }
        }

    }
};

#endif // BINARYSEARCHTREE_H
