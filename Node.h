#ifndef NODE_H
#define NODE_H

// Template class Node which can hold any type T
template <typename T>
class Node {
public:
    T data;        // Holds the data (in our case, a Story object)
    Node* left;    // Pointer to the left child node
    Node* right;   // Pointer to the right child node

    // Constructor: Initializes the node with the provided data and sets child pointers to nullptr
    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

#endif // NODE_H
