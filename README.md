# linked_list
 ## Implementation of the simple linked list
 
The provided code implements a template class for a doubly linked list. 
The list allows the insertion and deletion of elements at both the front and back ends. 
Each node contains data of a generic type T and pointers to the previous and next nodes, 
facilitating bidirectional traversal.

## Here’s a detailed description of the components:

### Node<T>: 
A template class representing a node in the list holds a data item of type T and points to the previous and next nodes.

### dList<T>: 
A template class for the doubly linked list with methods to 
add and remove elements from both ends 

- add_front
- add_back
- remove_front
- remove_back

check if the list is empty
- is_empty
  
and 

display the list contents in forward and backward order.
- display_forward
- display_backward

The code throws a std::runtime_error to handle exceptions, particularly when attempting to remove an element from an empty list. 

## Notes: 
1. The code was tested using online compiler https:// https://godbolt.org
2. The unit test for the doubly linked list was implemented using assert for simplicity

