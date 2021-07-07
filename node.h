#ifndef NODE_H
#define NODE_H
#include <string>

#include <iostream>
using namespace std;
template <typename T>

class Node
{
private:
    int key;            // Schluessel
    T data;             // Daten
    Node* left;
    Node* right;        // Linkes, rechtes Kind


public:    
    Node()              // Default constructor
    {
        left = nullptr;
        right = nullptr;
    }

    Node(Node* theleft, Node* theright)
    {
        left = theleft;
        right = theright;
    }

    bool rightExists()
    {
        /*if()
        {
            return false;
        }
        return true;*/
        return !(right == nullptr);
    }

    bool leftExists()
    {
        if(left == nullptr)
        {
            return false;
        }
        return true;
    }

    bool isLeaf()                       // Checked ob das node ein leaf sist
    {
        if(!rightExists() && !leftExists())
        {
            return true;
        }
        return false;
    }

    void print(std::string indent)      // Pre order
    {
        cout << indent << "> "<<key<<"|"<<data << endl;

        if(left != nullptr)
        {
            left->print(indent + "| ");
        }
        if(right != nullptr)
        {
            right->print(indent+ "| ");
        }
    }

    void printMe()
    {
        cout << "Returning current in PrintMe:"<<data<<" Key: "<< key<<endl;
    }

    void printChildren() // gebe children left right aus
    {
        if(leftExists())
        {
            cout<<"L: "<<left->getData()<<endl;
        }
        if(rightExists())
        {
            cout<<"R: "<<right->getData()<<endl;
        }
    }

    void printInOrder(std::string indent) // gebe in order aus
    {
        if(leftExists()) // Check if left exists
        {
            left->printInOrder(indent+"| ");
        }

        cout << indent << "> "<<key<<"|"<<data << endl; // show self

        if(rightExists()) // same for right
        {
            right->printInOrder(indent+"| ");
        }

    }

    void printPreOrder(std::string indent) // Gebe pre order aus
    {
        cout << indent << "> "<<key<<"|"<<data << endl; // show self

        if(leftExists()) // Check if left exists
        {
            left->printPreOrder(indent+"| ");
        }

        if(rightExists()) // same for right
        {
            right->printPreOrder(indent+"| ");
        }

    }

    void printPostOrder(string indent) // Gebe post order aus
    {
        if(leftExists()) // Check if left exists
        {
            left->printPostOrder(indent+"| ");
        }

        if(rightExists()) // same for right
        {
            right->printPostOrder(indent+"| ");
        }

        cout << indent << "> "<<key<<"|"<<data << endl; // show self

    }

    Node* searchByKey(int searchedKey) // Returns Node by key search
    {
        Node<T>* rightRet = nullptr, *leftRet = nullptr;

        if(key == searchedKey) // Wenn man selbst der gesuchte ist, return self
        {
            cout << "Node found:\nData:"<<data<<"\nKey:"<<key<<endl;
            return this;
        }

        if(leftExists()) // ansonsten halt weiter unten nachschauen
        {
            leftRet = left->searchByKey(searchedKey);
            cout << ".."<<endl;
        }
        if(rightExists())
        {
            rightRet = right->searchByKey(searchedKey);
            cout<<".."<<endl;
        }

        if(leftRet)
        {
            return leftRet;
        }
        else if (rightRet)
        {
            return rightRet;
        }
        else
        {
            return nullptr;
        }
    }
    // Füge an semantisch richtiger position ein
    void insert(Node* toIns, string thekey)
    {
        T insData = toIns->getData();

        if(insData < data) // insert data smaller
        {
            thekey = to_string(key) + "0"; // Baue key
            if(leftExists()) // Go left!
            {
                // append a 0 to the keystring
                left->insert(toIns,thekey);
            }
            else
            {
                int k = stoull(thekey);
                toIns->setKey(k); // set the new key
                left = toIns;
            }
        }
        else
        {
            thekey = to_string(key) + "1"; // Baue key
            if(rightExists())
            {
                 // append a 1 to the keystring
                right->insert(toIns,thekey);
            }
            else
            {  
                int k = stoull(thekey);
                toIns->setKey(k); // set the new key
                right = toIns;
            }
        }
    }
    // Funktionen um Spezielle nodes zu erhalten
    Node* getFarRightR()
    {
        if(rightExists())
        {
            return right->getFarRightR();
        }
        else
        {
            return this;
        }
    }

    Node* getFarRightI(Node* p)
    {
        while(p->rightExists())
        {
            p = p->getRight();
        }
        return p;
    }

    Node* getFarLeftR()
    {
        if(leftExists())
        {
            return left->getFarLeftR();
        }
        else
        {
            return this;
        }

    }

    Node* getFarLeftI(Node* p)
    {
        while(p->leftExists())
        {
            p = p->getLeft();
        }
        return p;
    }

    Node<T>* deleteRec(Node<T>* n, int key) // entferne node mit key                // setzt über return kanten neu
    {
        if(n == nullptr)
        {
            return n;
        }
        else if(key < n->getKey())                          // rekursive suche start
        {
            n->setLeft(deleteRec(n->getLeft(),key));
        }
        else if(key > n->getKey())
        {
            n->setRight(deleteRec(n->getRight(),key));
                                                            // rekursive suche ende
        }
        else
        {
            // found
            if(n->getLeft() == nullptr && n->getRight() == nullptr)
            {
                delete n;
                n = nullptr;
            }
            else if(n->getLeft() == nullptr) // Ein kind
            {
                Node<T>* temp = n;
                n = n->getRight(); // ersetze
                delete temp;        // delete
            }
            else if(n->getRight() == nullptr) // ein kind
            {
                Node<T>* temp = n;
                n = n->getLeft();   // ersetze kante über return
                delete temp;        // delete
            }
            else
            {
                Node<T>* temp = getFarRightR(); // Nehme ganz rechtes und schiebe nach
                n->setData(temp->getData());
                n->setKey(temp->getKey());                
                n->setRight(deleteRec(n->getRight(),temp->getKey()));   // Rekursives löschen

            }

        }
        return n;
    }


    void wipeSubtree(bool self) // Wipes the whole tree following this node. self: destroy calling node y/n
    {
        if(rightExists())
        {
            right->wipeSubtree(true);
        }
        if(leftExists())
        {
            left->wipeSubtree(true);
        }
        if(self == true)
        {
            delete this;
        }
    }

    int depth(Node<T>* node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        else
        {
            int lh = depth(node->getLeft()); // subtree  depth left
            int rh = depth(node->getRight()); //right

            if(lh > rh) // take larger
            {
                return lh+1;
            }
            else
            {
                return rh+1;
            }

        }
    }




    // Getter / Setter
    int getKey()
    {
        return key;
    }

    void setKey(int value)
    {
        key = value;
    }

    T getData()
    {
        return data;
    }

    void setData(T value)
    {
        data = value;
    }

    Node* getLeft()
    {
        return left;
    }

    void setLeft(Node* value)
    {
        left = value;
    }

    Node* getRight()
    {
        return right;
    }

    void setRight(Node* value)
    {
        right = value;
    }

};
// Operatoren
template<typename T>
bool operator==(Node<T> a, Node<T> b)
{
    return a.getData()==b.getData();
}

template<typename T>
bool operator<(Node<T> a, Node<T> b)
{
    return a.getData()<b.getData();
}

template<typename T>
bool operator>(Node<T> a, Node<T> b)
{
    return a.getData()>b.getData();
}

template<typename T>
bool operator<=(Node<T> a, Node<T> b)
{
    return a.getData()<=b.getData();
}

template<typename T>
bool operator>=(Node<T> a, Node<T> b)
{
    return a.getData()>=b.getData();
}
#endif // NODE_H
