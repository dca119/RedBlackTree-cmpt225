#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using std::fstream;
using std::string;
using std::vector;
using std::cout;
using std::endl;


// Template class for the node.
template <class T>
class NodeT
{
    public:
    T data;
    NodeT<T>* left;
    NodeT<T>* right;
    NodeT<T>* parent;
    bool isBlack;

    // Constructor that initializes the value of the node.
    NodeT(T val) : data(val), left(nullptr), right(nullptr), parent(nullptr), isBlack(false) { ; };
    // Constructor that initializes the value of the node and the boolean isBlack.
    NodeT(T val, bool isB) : data(val), left(nullptr), right(nullptr), parent(nullptr), isBlack(isB) { ; };
};


// Template class for the red black tree.
template <class T>
class RedBlackTree
{
public: 

    // Default constructor
    RedBlackTree();

    // Copy constructor
    RedBlackTree(const RedBlackTree<T> & rbt);

    // Operator=
    RedBlackTree<T> & operator=(const RedBlackTree<T> & rbt);

    // Destructor
    ~RedBlackTree();

    // Insert
    bool insert(T val);

    // Remove
    bool remove(T val);

    // Search
    bool search(T val) const;

    // Search
    std::vector<T> search(T r1, T r2) const;

    // ClosestLess
    T closestLess(T val);

    // ClosestGreater
    T closestGreater(T val);

    // Values
    std::vector<T> values();

    // Size
    int size() const;

    // Friend Function
    template <class Tjwme>
    friend NodeT<Tjwme>* JWMEgetRoot(const RedBlackTree<Tjwme> & rbt);


private:

    // Helper function to deep copy the red black tree.
    void copyRBT(NodeT<T>* original, NodeT<T>* copy);

    // Helper function to delete dynamic memory allocated by the tree.
    void removeAll(NodeT<T>* nd);

    // Performs a left rotation on the node parameter.
    void leftRotate(NodeT<T>* nd);

    // Performs a right rotation on the node parameter
    void rightRotate(NodeT<T>* nd);

    // Helper function that performs the normal binary search tree insert.
    void bstInsert(NodeT<T>* nd);

    // Helper function that returns the predecessor of the node parameter.
    NodeT<T>* predecessor(NodeT<T>* nd);

    // Helper function that fixes the red black tree after the removal of the node.
    void removeFix(NodeT<T>* nd, NodeT<T>* p, bool left);

    // Helper function that adds the values of a red black tree into a vector in ascending order.
    void inOrderAdd(NodeT<T>* nd, vector<T> &tree);

    // Helper function that adds the values of a red black tree that is less than its
    // val parameter to a vector in ascending order.
    void lessAdd(NodeT<T>* nd, vector<T> &tree, T val);

    // Helper function that adds the values of a red black tree that is more than its
    // val parameter to a vector in ascending order.
    void greaterAdd(NodeT<T>* nd, vector<T> &tree, T val);

    // Helper function that adds the values of a red black tree if it is within the 
    // r1, r2 parameter range into a vector.
    void specificAdd(T r1, T r2, NodeT<T>* nd, vector<T> &tree);

    // Private attribute that keeps track of the size.
    int sz;

    // Private attribute that keeps track of the root.
    NodeT<T>* root;

};


// REDBLACKTREE METHOD IMPLEMENTATIONS

// Default constructor
// Creates an empty tree whose root is a null pointer.
template <class T>
RedBlackTree<T>::RedBlackTree()
{
    sz = 0;
    root = nullptr;
}

// Copy constructor
// A constructor that creates a deep copy of its reference parameter.
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T> & rbt)
{   

    // Create a new root node.
    root = new NodeT<T>(rbt.root->data, rbt.root->isBlack);
    // Call the helper function to deep copy the parameter into the root.
    copyRBT(rbt.root, root);
    sz = rbt.sz;
}

// Overload operator
// Overloads the assignment operator for the RedBlackTree objects 
// and deep copies its reference parameter into the calling object.
template <class T>
RedBlackTree<T> & RedBlackTree<T>::operator=(const RedBlackTree<T> & rbt)
{   
    // Check if the parameter tree is the same as the calling object.
    if(&rbt!=this){
        // Deallocate all dynamic memory that was associated with the calling object.
        removeAll(root);
        sz = 0;
        // Create a new root node.
        root = new NodeT<T>(rbt.root->data, rbt.root->isBlack);
        // Call the helper function to deep copy the parameter into the root.
        copyRBT(rbt.root, root);
        sz = rbt.sz;
    }
    return *this;
}

// Destructor
// Deletes dynamic memory allocated by the tree
template <class T>
RedBlackTree<T>::~RedBlackTree()
{   
    // Call the helper function to deallocate all dynamic memory associated with the
    // calling object.
    removeAll(root);
    sz = 0;
}

// Insert
// If the tree does not contain the method's parameter, inserts the parameter.
template <class T>
bool RedBlackTree<T>::insert(T val)
{   
    // Check if the node is already in the tree.
    if(!search(val)){
        NodeT<T>* nd = new NodeT<T>(val);
        // Call a helper function to insert the node using the binary search
        // tree method.
        bstInsert(nd);
        nd->isBlack = false;
        // Repeat until the root or a black parent is reached.
        while (nd!=root && nd->parent->isBlack==false){
            // Check if the node's parent is a left child.
            if (nd->parent == nd->parent->parent->left){
                NodeT<T>* rUncle = nd->parent->parent->right;
                if (rUncle!=nullptr && !rUncle->isBlack){
                    // Both the node's parent and the right uncle are red therefore, 
                    // they can be made red. Then, the node can become it's grandparent.
                    nd->parent->isBlack = true;
                    rUncle->isBlack = true;
                    nd->parent->parent->isBlack = false;
                    nd = nd->parent->parent;
                }
                else{
                    // The node's grandparent must be black, therefore arrage the 
                    // node and it's parent in a line, and rotate the node's grandparent
                    // to balance the tre. Then, fix the colours of the tree.
                    if (nd==nd->parent->right){
                        nd = nd->parent;
                        leftRotate(nd);
                    }
                    nd->parent->isBlack = true;
                    nd->parent->parent->isBlack = false;
                    rightRotate(nd->parent->parent);
                }
            }
            // Symmetric to the if statement.
            else{
                NodeT<T>* lUncle = nd->parent->parent->left;
                if (lUncle!=nullptr && !lUncle->isBlack){
                    nd->parent->isBlack = true;
                    lUncle->isBlack = true;
                    nd->parent->parent->isBlack = false;
                    nd = nd->parent->parent;
                }
                else{
                    if (nd==nd->parent->left){
                        nd = nd->parent;
                        rightRotate(nd);
                    }
                    nd->parent->isBlack = true;
                    nd->parent->parent->isBlack = false;
                    leftRotate(nd->parent->parent);
                }
            }
        }
        // Colour the root black and increment the size of the tree.
        root->isBlack = true;
        sz++;
        return true;
    }
    return false;
}

// Remove
// If the tree contains the method parameter, removes the parameter.
template <class T>
bool RedBlackTree<T>::remove(T val)
{
    // Check if the node to be removed is in the tree.
    if (search(val)){
        NodeT<T>* nd = root;
        // Find the node to be removed and set the node to "nd".
        while (nd!=nullptr && nd->data!=val){
            if (nd->data>val){
                nd = nd->left;
            }
            else if (nd->data<val){
                nd = nd->right;
            }
        }
        NodeT<T>* y, *x;
        bool isLeft = false;
        // Check if the node has one or no children or two children.
        if (nd->left==nullptr || nd->right==nullptr){
            y = nd;
        }
        else{
            // Find the predecessor if the node has two children.
            y = predecessor(nd);
        }
        // Check if the node's child is a left or right child and set that child
        // to "x".
        if (y->left!=nullptr){
            x = y->left;
        }
        else{
            x = y->right;
        }
        // Detach x from the node if x is not null.
        if (x!=nullptr){
            x->parent = y->parent;
        }
        // If the node is the root, set the root to x.
        if (y->parent==nullptr){
            root = x;
        }
        else{
            // Else, attach x to the node's parent
            if (y==y->parent->left){
                y->parent->left = x;
                isLeft = true;
            }
            else{
                y->parent->right = x;
                isLeft = false;
            }
        }
        // If the predecessor was used, replace the node's data with 
        // the predecessor's data. Then, call the helper function to fix the 
        // red black tree.
        if (y!=nd){
            nd->data = y->data;
            delete y;
            if (nd->isBlack){
               removeFix(x, nd, nd->left==x);
            }
        }
        else {
            delete nd;
            if (y->isBlack){
               removeFix(x, y->parent, isLeft);
            }
        }
        sz--;
        return true;
    }
    return false;
}

// Search
// Searches the tree for the method's parameter and returns true if found.
template <class T>
bool RedBlackTree<T>::search(T val) const
{   
    NodeT<T>* nd = root;
    // Search through the tree, go left if the node value is greater than the parameter value
    // and vice versa until the node is found or no node is found.
    while (nd!=nullptr){
        if (nd->data==val){
            return true;
        }
        if (nd->data>val){
            nd = nd->left;
        }
        else{
            nd = nd->right;
        }
    }
    return false;
}

// Search
// Returns a vector that contains all of the values between the method's first and second parameters.
template <class T>
std::vector<T> RedBlackTree<T>::search(T r1, T r2) const
{   
    // Call the helper function to add specific values
    // within the range of the parameters into a vector
    // then return that vector.
    vector<T> list;
    specificAdd(r1, r2, root, list);
    return list;
}

// ClosestLess
// Return the largest value stored in the tree that is less than the method's parameter.
template <class T>
T RedBlackTree<T>::closestLess(T val) 
{   
    // Call the helper function to add all the values
    // less than the parameter into a vector in ascending order.
    // Then, return the last element added.
    vector<T> tree;
    lessAdd(root,tree,val);
    if (tree.empty()){
        return val;
    }
    return tree.back();
}

// ClosestGreater
// Return the smallest value stored in the tree that is less than the method's parameter.
template <class T>
T RedBlackTree<T>::closestGreater(T val) 
{
    // Call the helper function to add all the values
    // greater than the parameter into a vector in ascending order.
    // Then, return the first element added.
    vector<T> tree;
    greaterAdd(root,tree,val);
    if (tree.empty()){
        return val;
    }
    return tree.front();
}

// Values
// Returns a vector that contains all of the values in the tree. (Contents are in ascending order.)
template <class T>
std::vector<T> RedBlackTree<T>::values() 
{
    // Call the helper function to add all the values of the tree
    // into a vector in ascending order.
    vector<T> tree;
    inOrderAdd(root, tree);
    return tree;
}

// Size
// Returns the number of values stored in the tree.
template <class T>
int RedBlackTree<T>::size() const
{
    // Return the private attribute sz.
    return sz;
}


// HELPER FUNCTIONS

// Helper function that creates a deep copy of the original parameter into the copy parameter.
// Recursive deep copy function that copies the nodes by copying the subtrees of each node.
template <class T>
void RedBlackTree<T>::copyRBT(NodeT<T>* original, NodeT<T>* copy){
    if (original!=nullptr){
        if (original->left!=nullptr){
            copy->left = new NodeT<T>(original->left->data, original->left->isBlack);
        }
        if (original->right!=nullptr){
            copy->right = new NodeT<T>(original->right->data, original->right->isBlack);
        }
        // Remember to set the parent attribute of each node.
        if (copy->left!=nullptr){
            copy->left->parent = copy;
        }
        if (copy->right!=nullptr){
            copy->right->parent = copy;
        }
        // Copy left subtree.
        copyRBT(original->left, copy->left);
        // Copy right subtree.
        copyRBT(original->right, copy->right);
    }
}

// Helper function that deallocates all nodes in a red black tree.
template <class T>
void RedBlackTree<T>::removeAll(NodeT<T>* nd)
{   
    // If the node to be removed is not null then call it's 
    // right subtree and left subtree. Then, delete the node.
    if(nd!=nullptr){
        removeAll(nd->left);
        removeAll(nd->right);
        delete nd;
    }
}

// Helper function that rotates the tree towards the left.
template <class T>
void RedBlackTree<T>::leftRotate(NodeT<T>* nd)
{
    NodeT<T>* rChild = nd->right;
    nd->right = rChild->left;

    // Set the node's parent references.
    // rChild's left child.
    if(rChild->left!=nullptr){
        rChild->left->parent = nd;
    }
    rChild->parent = nd->parent;

    // Set the child reference of the node's parent.
    // Check if the node was the root.
    if(nd->parent==nullptr){
        root = rChild;
    }
    else if (nd==nd->parent->left){
        nd->parent->left = rChild;
    }
    else{
        nd->parent->right = rChild;
    }
    // Make the node, rChild's left child.
    rChild->left = nd;
    nd->parent = rChild;
}

// Helper function that rotates the tree towards the right.
template <class T>
void RedBlackTree<T>::rightRotate(NodeT<T>* nd)
{
    NodeT<T>* lChild = nd->left;
    nd->left = lChild->right;

    // Set the node's parent references.
    // lChild's right child.
    if(lChild->right!=nullptr){
        lChild->right->parent = nd;
    }
    lChild->parent = nd->parent;

    // Set the child reference of the node's parent.
    // Check if the node was the root.
    if(nd->parent==nullptr){
        root = lChild;
    }
    else if (nd==nd->parent->right){
        nd->parent->right = lChild;
    }
    else{
        nd->parent->left = lChild;
    }
    // Make the node, lChild's right child.
    lChild->right = nd;
    nd->parent = lChild;
}

// Helper function that does a binary search tree insertion.
template <class T>
void RedBlackTree<T>::bstInsert(NodeT<T>* nd)
{
    NodeT<T>* p = root;
    NodeT<T>* next = root;

    if(sz==0){
        root = nd;
    }
    else{
        // Find the parent of the new node
        while(next!=nullptr){
            p = next;
            if (nd->data < p->data){
                next = p->left;
            }
            else{
                next = p->right;
            }
        }

        nd->parent = p;
        // Insert new node.
        if(nd->data < p->data){
            p->left = nd;
        }
        else{
            p->right = nd;
        }
    }
}

// Helper function that finds the predecessor.
template <class T>
NodeT<T>* RedBlackTree<T>::predecessor(NodeT<T>* nd)
{
    if (nd->left!=nullptr){
        // Go into the left subtree and keep going right
        // until the predecessor is found.
        NodeT<T>* temp = nd->left;
        while(temp->right!=nullptr){
            temp = temp->right;
        }
        return temp;
    }
    return nullptr;
}

// Helper function that fixes the red black tree after removal.
template <class T>
void RedBlackTree<T>::removeFix(NodeT<T>* nd, NodeT<T>* p, bool left)
{
    // Passed the node and the node's parent, just in case the node is null.
    NodeT<T>* y;
    bool isB = false;
    // Check if the node parameter is null.
    if (nd==nullptr){
        isB = true;
    }
    else {
        isB = nd->isBlack;
    }
    // Keep repeating until the node is the root or the node is black.
    while (nd!=root && isB){
        // If the node is the left child.
        if (left){
            // Set y to be x's sibling.
            y = p->right;
            if (y!=nullptr && !y->isBlack){
                y->isBlack = true;
                // x's parent must have been black since y is red.
                p->isBlack = false;
                if (p->right!=nullptr){
                    leftRotate(p);
                }
                y = p->right;
            }
            // Check if y is null pointer or if y's children are nullptrs.
            if ((y==nullptr) || ((y->left!=nullptr && y->right!=nullptr) && (y->left->isBlack && y->right->isBlack))){

                if (y!=nullptr){
                    y->isBlack = false;
                }
                nd = p;
                // Check if the node's parent is null before using the node's parent.
                if (p->parent!=nullptr){
                    p = p->parent;
                    if (nd == p->left){
                        left = true;
                    }
                    else{
                        left = false;
                    }
                }
                // Into the while loop again.
            }
            else{
                // Check if y is null pointer or if y's children are nullptrs.
                if ((y==nullptr) || (y->right==nullptr) || (y->right->isBlack)){
                    if (y!=nullptr){
                        if (y->left!=nullptr){
                            y->left->isBlack = true;
                        }
                        y->isBlack = false;
                        if (y->left!=nullptr){
                            rightRotate(y);
                        }
                    }
                    y = p->right;
                }
                if (y!=nullptr){
                    y->isBlack = p->isBlack;
                }
                p->isBlack = true;
                if (y!=nullptr&&y->right!=nullptr){
                    y->right->isBlack = true;
                }
                if (p->right!=nullptr){
                    leftRotate(p);
                }
                nd = root;
            }
        }
        // Symmetric to if statement.
        else{
            y = p->left;
            if (y!=nullptr && !y->isBlack){
                y->isBlack = true;
                p->isBlack = false;
                if (p->left!=nullptr){
                    rightRotate(p);
                }
                y = p->left;
            }
            if ((y==nullptr) || ((y->left!=nullptr && y->right!=nullptr) && (y->left->isBlack && y->right->isBlack))){
                if (y!=nullptr){
                    y->isBlack = false;
                }
                nd = p;
                if (p->parent!=nullptr){
                    p = p->parent;
                    if (nd == p->left){
                        left = true;
                    }
                    else{
                        left = false;
                    }
                }
            }
            else{
                if (y==nullptr || y->left==nullptr || y->left->isBlack){
                    if (y!=nullptr){
                        if (y->right!=nullptr){
                            y->right->isBlack = true;
                        }
                        y->isBlack = false;
                        if (y->right!=nullptr){
                            leftRotate(y);
                        }
                    }
                    y = p->left;
                }
                if (y!=nullptr){
                    y->isBlack = p->isBlack;
                }
                p->isBlack = true;
                if (y!=nullptr&&y->left!=nullptr){
                    y->left->isBlack = true;   
                }
                if (p->left!=nullptr){
                    rightRotate(p);
                }
                nd = root;
            }
        }
    }
    if (nd!=nullptr){
        nd->isBlack = true;
    }
}

// Helper function that only adds values to the vector if it is in the range of the 
// first two parameters.
template <class T>
void RedBlackTree<T>::specificAdd(T r1, T r2, NodeT<T>* nd, vector<T> &tree)
{
    // Recursive base case where the node does not equal a nullptr.
    if (nd!=nullptr){
        // Check the left subtree. (Check left first to be in order.)
        specificAdd(r1, r2, nd->left, tree);
        // Add when r2 is the base of the range and r1 is the height of the range
        // and the value is in the range.
        if (nd->data>r2 && nd->data<r1){
            tree.push_back(nd->data);
        }
        // Add when r1 is the base of the range and r2 is the height of the range
        // and the value is in the range.
        if (nd->data<=r2 && nd->data>=r1){
            tree.push_back(nd->data);
        }
        // Check the right subtree.
        specificAdd(r1, r2, nd->right, tree);
    }
}

// Helper function that adds values to its vector parameter if the values are lower than 
// or equal to the val parameter.
template <class T>
void RedBlackTree<T>::lessAdd(NodeT<T>* nd, vector<T> &tree, T val)
{
    // Recursive base case where the node does not equal a nullptr.
    if (nd!=nullptr){
        // Check the left subtree. (Check left first to be in order.)
        lessAdd(nd->left, tree, val);
        // If the node's data is less than the val parameter, add the node's data
        // into the vector.
        if (nd->data<val){
            tree.push_back(nd->data);
        }
        // Check the right subtree.
        lessAdd(nd->right, tree, val);
    }
} 

// Helper function that adds values to its vector parameter if the values are larger than 
// or equal to its val parameter.
template <class T>
void RedBlackTree<T>::greaterAdd(NodeT<T>* nd, vector<T> &tree, T val)
{
    // Recursive base case where the node does not equal a nullptr.
    if (nd!=nullptr){
        // Check the left subtree. (Check left first to be in order.)
        greaterAdd(nd->left, tree, val);
        // If the node's data is greater than the val parameter, add the node's data
        // into the vector.
        if (nd->data>val){
            tree.push_back(nd->data);
        }
        // Check the right subtree.
        greaterAdd(nd->right, tree, val);
    }
} 

// Helper function that adds values of a red black tree in order to its vector 
// parameter.
template <class T>
void RedBlackTree<T>::inOrderAdd(NodeT<T>* nd, vector<T> &tree)
{
    // Recursive base case where the node does not equal a nullptr.
    if (nd!=nullptr){
        // Check the left subtree. (Check left first to be in order.)
        inOrderAdd(nd->left, tree);
        // Add the node's data into the vector.
        tree.push_back(nd->data);
        // Check the right subtree.
        inOrderAdd(nd->right, tree);
    }
} 


// PART 2 

void statistics(string filename){
    // Open the file and check if the file was opened properly.
    fstream file;
    file.open(filename, fstream::in);
    if (!file.is_open()){
        return;
    }
    RedBlackTree<double> object;
    double value;
    // Add the doubles into a vector.
    while(file >> value){
        object.insert(value);
    }
    // Close the file because we will not be using it anymore.
    file.close();

    // Check if there were any values in the file.
    if (object.size()!=0){
        // Use the size() function to print the number of unique values.
        // Note that because we used the insert function, no duplicates
        // will be in the tree. Therefore, all the values in the tree
        // are unique.
        cout << "Number of Unique Values: " << object.size() << endl;

        // Move all the values in the tree to a vector using the values() function.
        // Then add all the values in the vector and divide the sum by the size of
        // the vector to get the average.
        vector<double> findVal = object.values();
        double average = 0;
        for (int i=0; i<findVal.size(); i++){
            average = average + findVal.at(i);
        }
        average = average/findVal.size();
        cout << "Average: " << average << endl;

        // Check if the size is even or odd. If it is even, add the middle two 
        // values together and divide them by two to find the median.
        // Else if the size is odd, print the median.
        int median;
        if (object.size()%2==0){
            median = findVal.at(findVal.size()/2) + findVal.at((findVal.size()/2)-1);
            median = median/2;
            cout << "Median: " << median << endl;
        }
        else{
            median = (findVal.size()-1)/2;
            cout << "Median: " << findVal.at(median) << endl;
        }

        // Use the closestLess function to get the closest less value to 42.
        // Then, do the same for the greatest. Check if the function returned
        // 42 or not. If it did, then there was no value greater or less than
        // 42.
        double closeLess = object.closestLess(42.0);
        double closeGreater = object.closestGreater(42.0);
        if (closeLess != 42.0){
            cout << "Closest Less Than 42: " << closeLess << endl;
        }
        else{
            cout << "Closest Less Than 42: None" << endl;
        }
        if (closeGreater != 42.0){
            cout << "Closest Greater Than 42: " << closeGreater << endl;
        }
        else{
            cout << "Closest Greater Than 42: None" << endl;
        }
    }
    else{
        cout << "No doubles in file." << endl;
    }
}