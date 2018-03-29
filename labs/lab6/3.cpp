#include <iostream>
#include <list>
#include <string>

// ===========================================================================

// A SIMPLE LINKED LIST CLASS
// (note: it's ok that all the member variables are public for this tiny class)

class Node {
public:
  int value;
  Node* ptr;
};


// ===========================================================================

// a helper function to print the contents of a linked list of Nodes
void print_linked_list(const std::string &name, Node *my_linked_list) {
  // print the name of this list
  std::cout << name;
  // use a temporary pointer to walk down the list
  Node *tmp = my_linked_list;
  while (tmp != NULL) {
    // print out each element
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}


// YOU NEED TO WRITE THIS FUNCTION
Node* make_linked_list_from_STL_list( std::list<int> &lst ) {
  Node *head, *node1, *node2;
  std::list<int>::iterator i;
  for ( i=lst.begin(); i!=lst.end(); ++i){
    node1 = new Node;
    node1->value = *i;
    if ( i == lst.begin() ) head = node1;
    else node2->ptr = node1;
    node2 = node1;
    node1->ptr= NULL;
  } 
  return head;
}


// YOU NEED TO WRITE THIS FUNCTION
Node* reverse_nodes_in_linked_list(Node *input) {
  
  if ( input->ptr == NULL && input NULL) return input;
  Node *nextNode = input->ptr;  
  input->ptr = NULL;  
  Node *reverseRest = reverse_nodes_in_linked_list(nextNode);  
  nextNode->ptr = input;  
  return reverseRest;
}



// ===========================================================================

int main() {

  // manually create a linked list of notes with 4 elements
  Node* a = new Node; 
  a->value = 6; 
  a->ptr = new Node;
  a->ptr->value = 7;
  a->ptr->ptr = new Node;
  a->ptr->ptr->value = 8;
  a->ptr->ptr->ptr = new Node;
  a->ptr->ptr->ptr->value = 9;
  a->ptr->ptr->ptr->ptr = NULL;
  print_linked_list("a",a);

                                                      //1 elements
  std::list<int> b1;
  b1.push_back(10);
  //b.push_back(11);
  //b.push_back(12);
  //b.push_back(13);
  Node* b2 = make_linked_list_from_STL_list(b1);
  print_linked_list("b:",b2);
  Node* b3 = reverse_nodes_in_linked_list(b2);
  print_linked_list("b reversed:",b3);

                                                      //19 elements
  std::list<int> c1;
  for (int i=1; i<20; i++) 
    c1.push_back(i*3);
  Node* c2 = make_linked_list_from_STL_list(c1);
  print_linked_list("c:",c2);
  Node* c3 = reverse_nodes_in_linked_list(c2);
  print_linked_list("c reversed:",c3);

                                                      //0 elements
  std::list<int> d1;
  Node* d2 = make_linked_list_from_STL_list(d1);
  print_linked_list("d:",d2);
  Node* d3 = reverse_nodes_in_linked_list(d2);
  print_linked_list("d reversed:",d3);

  // NOTE: We are not deleting any of the Nodes we created...  so this
  //       program has some memory leaks!  More on this in future
  //       lectures & labs :)

}