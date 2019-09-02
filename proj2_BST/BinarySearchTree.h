//Sarah Sherman
//Project 2, cse331
#ifndef PROJECT_BST_BINARYSEARCHTREE_H
#define PROJECT_BST_BINARYSEARCHTREE_H
/** DO NOT MODIFY THE LINE BELOW THIS. IT WILL BE USED FOR TESTING. */
#define UNIT_TEST

#include "Exceptions.h"
#include <vector>
using std::vector;
#include <ostream>
using std::ostream;

template<typename T>
struct Node {
  T value;
  Node *left;
  Node *right;
  Node(T val) : value(val), left(nullptr), right(nullptr) {};
};

template<typename T>
class BinarySearchTree {

    /** any friends for testing
     */
#if defined(UNIT_TEST)
    FRIEND_TEST(BSTProjectTests, TestBSTAdd);
    FRIEND_TEST(BSTProjectTests, TestBSTSearch);
    FRIEND_TEST(BSTProjectTests, TestBSTRemove);
    FRIEND_TEST(BSTProjectTests, TestBSTInstance);
    FRIEND_TEST(BSTProjectTests, TestSetInstance);
    FRIEND_TEST(BSTProjectTests, TestSetAdd);
    FRIEND_TEST(BSTProjectTests, TestSetRemove);
    FRIEND_TEST(BSTProjectTests, TestSetContains);
    FRIEND_TEST(BSTProjectTests, TestBSTInorderTraversal);
    FRIEND_TEST(BSTProjectTests, TestSetClear);
#endif

    public:
    //constructors
    BinarySearchTree();
    BinarySearchTree(vector<T> values);
    
    //destructor        
    ~BinarySearchTree();
    
    //mutators & accessors
    void add(T val);
    const T *search(T val) const;
    void remove(T val);//removes a val from the tree, must accound for all three cases of removal:
                      // no children, 1 child, 2 children. Use
    vector<T> getValues() const;
    int size() const;
    //bool isEmpty() const {return root == nullptr;}
 
  private:
    Node<T> *root = nullptr;//root
    
    void add(Node<T> *&root_node, Node<T> *&new_node);
    Node<T> *remove(Node<T> *&root_node, T val);
    void inOrderTraversal(Node<T> *node, vector<T> &values) const;
    int size(Node<T> *node) const;
    void destroy(Node<T> *&node);
    const Node<T> *search(Node<T> *root_node, T val) const;
};


//default constructor
template<typename T>
BinarySearchTree<T>::BinarySearchTree() {}

//constructor 
template<typename T>
BinarySearchTree<T>::BinarySearchTree(vector<T> values) {
  //adds every element of values to the tree
  //std:sort(values.begin(), values.end());

  //need to set root as middle value in the vector ?

  //add the rest of the vector to the tree
  for(int i = 0; i < values.size(); i++){
         add(values.at(i));
  }
}


//destructor 
template<typename T>
BinarySearchTree<T>::~BinarySearchTree(){ 
  destroy(root);
}

//memeber funcitons
template<typename T>
void BinarySearchTree<T>::add(T val) {
  //adds a val to the tree, if already there does not modify tree
  
  Node<T> *n = new Node<T>(val);
  add(root, n);
}

template<typename T>
void BinarySearchTree<T>::add(Node<T> *&root_node, Node<T> *&new_node) {
  if(root_node == nullptr)//empty tree
     root_node = new_node;
  else if(new_node->value < root_node->value)//new_node to the left side tree
     add(root_node->left, new_node);
  else if( new_node->value > root_node->value)//new_node to right side tree
     add(root_node->right, new_node);
  else
    return; //already in tree, do nothing
  
}

template<typename T>
const T *BinarySearchTree<T>::search(T val) const {
  //returns a pointer to the value of the node if found
  //returns nullptr if not, use const Node<T> *root_node, T val) 
  //const; recursively to find the val using standard binary search algorithm
  
 auto b = search(root, val);
  
  if( b == nullptr){
    return nullptr;
  }

    return &b->value;//search(root, val);
}

template<typename T>
const Node<T> *BinarySearchTree<T>::search(Node<T> *root_node, T val) const {
  //Base cases, root is nul or value is root
  if(root_node == nullptr)
     return nullptr;
  
  if(root_node->value == val)
    return root_node;
  
  //val smaller than root, search left side of tree
  if(root_node->value > val)
    return search(root_node->left, val);
  
  //val larger than root, search right side of tree
  //if(root_node->value < val)
  return search(root_node->right, val);
}

template<typename T>
void BinarySearchTree<T>::remove(T val) {
  remove(root, val);
}


template<typename T>
vector<T> BinarySearchTree<T>::getValues() const {

  vector<T> tree_val; 
  if(root == nullptr)
    return tree_val;
  if(root->left == nullptr && root->right == nullptr){
    tree_val.push_back(root->value);
    return tree_val; 
  }
  else
    inOrderTraversal(root, tree_val);
  
  return tree_val; 
}

template<typename T>
void BinarySearchTree<T>::inOrderTraversal(Node<T> *node, vector<T> &values) const {
  if(node == nullptr)
    return;
  inOrderTraversal(node->left, values);
  
  values.push_back(node->value);

  inOrderTraversal(node->right, values);


  
}

template<typename T>
int BinarySearchTree<T>::size() const {
  size(root);
}

template<typename T>
int BinarySearchTree<T>::size(Node<T> *node) const {

  return(node == nullptr) ? 0 : 1 + size(node->left) + size(node->right);

}

template<typename T>
Node<T> *BinarySearchTree<T>::remove(Node<T> *&root_node, T val) {
   //base case
  if(root_node == nullptr)//empty tree
    return root_node; 
  if(val < root_node->value){
    root_node->left = remove(root_node->left, val);
  }
  else if(val > root_node->value){
    root_node->right = remove(root_node->right, val);
  }
  else{
    if(root_node->left == nullptr){
      Node<T> *temp = root_node->right;
      return temp;
    }
    else if(root_node->right == nullptr){
      Node<T> *temp = root_node->left;
      delete root_node;
      return temp;
    }
    Node<T> *temp = root_node->right;
    
    while(temp->left != nullptr){
      temp = temp->left;
    }
      
    root_node->value = temp->value;
    root_node->right = remove(root_node->right, temp->value);
  }

  return root_node; 
  
  
}

template<typename T>
void BinarySearchTree<T>::destroy(Node<T> *&node) {//used in destructor 
  if(node !=nullptr){
    destroy(node ->left);
    destroy(node ->right);
    delete node; 
  }
  node = nullptr;
}




#endif //PROJECT_BST_BINARYSEARCHTREE_H
