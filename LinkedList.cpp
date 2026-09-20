#include "LinkedList.h"
#include <iostream>
#include <string>

using namespace std;

Reservations::Reservations(){ // Constructor
   head = nullptr; // Point head to tail node.
}

Reservations::~Reservations() {
  Node* current = head;
  while (current != nullptr){
    Node* temp = current;
    current = current->next;
    delete temp;
  }
}


// Temporary, TBD.
int main(){

  return 0;
}