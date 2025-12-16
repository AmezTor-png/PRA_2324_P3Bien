#ifndef NODE_H
#define NODE_H

#include <ostream>

using namespace std;

template <typename T>

class Node
{
    public:
        T data;
        Node<T>* next;

        Node(T data, Node <T>* next = nullptr)  /*constructor*/
        {
            this->data = data;
            this->next = next;
        }

        friend ostream&operator<<(ostream &out, const Node<T> &node)  /*sobrecarga del operador*/
        {
            out << node.data;
            return out;
        }
}; 

#endif
