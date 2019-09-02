#include <vector>
#include <iostream>
using std::vector; using std::cout; using std::endl;
#include "BinarySearchTree.cpp"
#include "Exceptions.h"

template<typename T>
class Set {

 public:
  Set() = default;
  Set(vector<T> values);
  ~Set() = default;
  bool contains(T value) const;
  int size() const;
  void add(T value);
  void remove(T value);
  void clear();
  vector<T> getValues() const;
  bool isDisjoint(const Set<T> &other) const;
  bool isSubset(const Set<T> &other) const;
  bool isSuperset(const Set<T> &other) const;
  Set<T> unionWith(const Set<T> &other) const;
  Set<T> intersection(const Set<T> &other) const;
  Set<T> difference(const Set<T> &other) const;
  Set<T> symmetricDifference(const Set<T> &other) const;
 

 private:
  BinarySearchTree<T> tree;
};

template<typename T>
//constructor
Set<T>::Set(vector<T> values) {
  /* construct a set with all elements of values in it
     if there are duplicates, only add them once
  */
  for(int i = 0; i < values.size(); i++){
    tree.add(values.at(i));
  }
  //BinarySearchTree<T> tree(values);
  //tree.add(values);
  
}
template<typename T>
bool Set<T>::contains(T value) const {
  /*Test value for membership in the set, returns
  true if value is in the set, false otherwise
  */
  return( tree.search(value)!=nullptr ? true : false);
}

template<typename T>
int Set<T>::size() const {
  /*returns the size of the set, empty sets have size 0 */
  //return tree->size() == 0 ?  0: tree->size();
  return tree.size() == 0 ?  0: tree.size();
}

template<typename T>
void Set<T>::add(T value) {
  /*Adds value to the set, if value is already in the set
    do nothing */
  //tree->add(value); 
  tree.add(value); 
}

template<typename T>
void Set<T>::remove(T value) {
  /* removes value from the set, if value is not present, do nothing*/
  //tree->remove(value);
  tree.remove(value);
}

template<typename T>
void Set<T>::clear() {
  /*Removes all values in the set. One simple way to do this is to
    delete the BST and constuct a new one */
  //vector<T> tree_val = tree->getValues();
  vector<T> tree_val = tree.getValues();
  ~tree();
  tree = new BinarySearchTree<T>(tree_val);
}

template<typename T>
vector<T> Set<T>::getValues() const {
  /* Returns all values in the set, while by def a set is unordered, 
     use the in-order traversal from BST to produce a sorted output 
     for testing purposes
  */
     return tree.getValues();
}

template<typename T>
bool Set<T>::isDisjoint(const Set<T> &other) const {
  /* return true if the set has no elements in common with other.
     sets are disjoint if and only if their intersection is the 
     empty set
  */ 
  
  vector<T> vec = tree.getValues();
    
  for(int i = 0; i < vec.size(); i++){
    if(other.contains(vec.at(i)))
      return false; 
    }

    return true;
      
    
}

template<typename T>
bool Set<T>::isSubset(const Set<T> &other) const {
  /* test whether every element in the set is in other*/
  vector<T> vec = tree.getValues();
  
  for(int i = 0; i < vec.size(); i++){
    if(!other.contains(vec.at(i)))
      return false; 
  }
  return true; 
  /*int i = 0; 
 
  while(i != vec.size()){
    if(other.contains(vec.at(i)))
      i++;
  }
 
  return(i == vec.size());
  */
}

template<typename T>
bool Set<T>::isSuperset(const Set<T> &other) const {
  /* Test whether every element in OTHER is in the set */
  vector<T> vec = other.getValues();
  for(int i = 0; i < vec.size(); i++){
     if(tree.search(vec.at(i)) == nullptr)
      return false;
  }
  return true;
  /*int i = 0; 

  while(tree.contains(vec.at(i))){
    ++i;
  }

  return(i == vec.size());
  */
}

template<typename T>
Set<T> Set<T>::unionWith(const Set<T> &other) const {
  /* Return a new set with all elements of the set and all elements
     of other. This new set will not have any duplicates 
  */
  
    vector<T> vec1 = other.getValues();
    vector<T> vec2 = tree.getValues();

     Set<T> unionSet(vec1);

     
     for(int i = 0; i<vec2.size(); i++){
        unionSet.add(vec2.at(i));
     }

     return unionSet;
}

template<typename T>
Set<T> Set<T>::difference(const Set<T> &other) const {
  /* return a new set with elements that are in set but not in other */
 
  Set<T> diff;

  vector<T> vec = tree.getValues();
  for(int i = 0; i < vec.size(); i++){
      
      if(!other.contains(vec.at(i)))
          diff.add(vec.at(i));
}

  return diff;
}

template<typename T>
Set<T> Set<T>::intersection(const Set<T> &other) const {
  /* return a new set with elements in the set that are in common with other*/
  Set<T> intersect; 
  vector<T> vec = tree.getValues();
  for(int i = 0; i < vec.size(); i++){
    if(other.contains(vec.at(i)))
            intersect.add(vec.at(i));
  }
  return intersect; 
}

template<typename T>
Set<T> Set<T>::symmetricDifference(const Set<T> &other) const {
  /* return a new set with elements in either the set or other, but NOT both */
 
  vector<T> vec1 = tree.getValues();
  vector<T> vec2 = other.getValues();

  Set<T> set1(vec1);
  Set<T> set2(vec2);
  Set<T> set3 = set1.difference(set2); //gets the elements in set1
  Set<T> set4 = set2.difference(set1);

  vector<T> vec3 = set3.getValues();
  vector<T> vec4 = set4.getValues();

  Set<T> set5(vec3);
  for(int i = 0; i <vec4.size(); i++){
    set5.add(vec4.at(i));
  }
  
  return set5;  

}



int main(){

    vector<int> vecA{1, 2, 3, 4};
    vector<int> vecB{3, 4, 5, 6};
    vector<int> vecD{0,10, 7, 8};


    Set<int> setA = Set<int>(vecA);
    Set<int> setB = Set<int>(vecB);
    Set<int> setC = Set<int>(vecA);
    Set<int> setD = Set<int>(vecD);
   

    Set<int> ab = setA.unionWith(setB);
    vector<int> getAB = ab.getValues();
    cout<<"A U B: ";
    for(int i = 0; i < getAB.size(); i++){
      cout<<getAB.at(i)<<" ";
    }
   cout<<endl;


   Set<int> ba = setB.unionWith(setA);
   vector<int> getBA = ba.getValues();
  cout<<"B U A: ";
   for(int i = 0; i < getBA.size(); i++){
      cout<<getBA.at(i)<<" ";
    }
   cout<<endl;

  

  /*  Set<int> setE = setA.symmetricDifference(setB); 
    vector<int> e = setE.getValues();
    for(int i = 0; i <e.size(); i++){
      cout<<e.at(i)<<" ";
    }
    cout<<endl;

  */
}



















