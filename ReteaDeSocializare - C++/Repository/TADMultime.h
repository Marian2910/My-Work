#ifndef MULTIMEORDONATA_H
#define MULTIMEORDONATA_H

#include <vector>
#include <iostream>
using namespace std;

template<class T>
class MultimeOrdonata {
private:
    struct Node {
        T val;
        Node* st;
        Node* dr;
    };

    Node* root;
    void adauga(Node*& root, T val);
    void distruge(Node* root);
    void sterge(Node*& root, T val) ;
    bool exista(Node* root, T val);
    void get_ordered_lista(Node* root, vector<T> &l) const ;
public:
    MultimeOrdonata();
    ~MultimeOrdonata();
    void adauga(T val);
    void sterge(T val);
    bool exista(T val);
    vector<T> get_lista_ordonata();
};

template<class T>
void MultimeOrdonata<T>::adauga(MultimeOrdonata::Node *&root, T val) {
    if (root == nullptr) {
        root = new Node;
        root->val = val;
        root->st = nullptr;
        root->dr = nullptr;
    }
    else if (val < root->val) {
        adauga(root->st, val);
    }
    else if (val > root->val) {
        adauga(root->dr, val);
    }
}

template<class T>
void MultimeOrdonata<T>::distruge(MultimeOrdonata::Node *root) {
    if (root != nullptr) {
        distruge(root->st);
        distruge(root->dr);
        delete root;
    }
}

template<class T>
void MultimeOrdonata<T>::sterge(MultimeOrdonata::Node *&root, T val) {
    if (root != nullptr) {
        if (val < root->val) {
            sterge(root->st, val);
        }
        else if (val > root->val) {
            sterge(root->dr, val);
        }
        else {
            if (root->st == nullptr && root->dr == nullptr) {
                delete root;
                root = nullptr;
            }
            else if (root->st == nullptr) {
                Node* temp = root;
                root = root->dr;
                delete temp;
            }
            else if (root->dr == nullptr) {
                Node* temp = root;
                root = root->st;
                delete temp;
            }
            else {
                Node* temp = root->dr;
                while (temp->st != nullptr) {
                    temp = temp->st;
                }
                root->val = temp->val;
                sterge(root->dr, temp->val);
            }
        }
    }
}

template<class T>
bool MultimeOrdonata<T>::exista(MultimeOrdonata::Node *root, T val) {
    {
        if (root != nullptr) {
            if (val < root->val) {
                exista(root->st, val);
            } else if (val > root->val) {
                exista(root->dr, val);
            } else {
                return true;
            }
        } else {
            return false;
        }
    }
}

template<class T>
void MultimeOrdonata<T>::get_ordered_lista(MultimeOrdonata::Node *root, vector<T> &l) const
{
    if (root != nullptr) {
        get_ordered_lista(root->st, l);
        l.push_back(root->val);
        get_ordered_lista(root->dr, l);
    }
}

template<class T>
MultimeOrdonata<T>::MultimeOrdonata() {
    {
        root = nullptr;
    }
}

template<class T>
MultimeOrdonata<T>::~MultimeOrdonata() {
    {
        distruge(root);
    }
}

template<class T>
void MultimeOrdonata<T>::adauga(T val) {
        adauga(root, val);
    }

template<class T>
void MultimeOrdonata<T>::sterge(T val) {
    {
        sterge(root, val);
    }
}

template<class T>
bool MultimeOrdonata<T>::exista(T val) {
    {
        return exista(root, val);
    }
}

template<class T>
vector<T> MultimeOrdonata<T>::get_lista_ordonata() {
    {
        vector<T> l;
        get_ordered_lista(root, l);
        return l;
    }
}


#endif // MULTIMEORDONATA_H
