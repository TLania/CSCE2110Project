#include "LinkedList.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

ReservationList::ReservationList(){ // Constructor
   head = nullptr; // Point head to tail node.
   cout = 0;
}
ReservationList::ReservationList(const ReservationList& other) : head(nullptr), count(0){
  ReservationNode* current = other.head;
  while(current != nullptr){
    InsertEnd(current->data);
    current = current->next;
  } // Copy Constructor

}

ReservationList::~ReservationList() { // Destructor
  clear();
}

ReservationList& ReservationList::operator=(const ReservationList& other){ // Overloaded assignment operator
  if(this != &other){
    clear();
    ReservationNode* current = other.head;
    while(current != nullptr){
      InsertEnd(current->data);
      current = current-> next;
    }
  }  

  return *this;
}

// Insert ReservationList
void ReservationList::InsertEnd](const Reservation& reservation) {
  ReservationNode* newNode = new ReservationNode(reservation);
  if(head == nullptr) {
    head = newNode;
  } else{
    ReservationNode* current = head;
    while(current->next != nullptr){
      current = curent->next;
    }
    current->next = newNode;
  }

  count++;
  }


// Remove reservation by ID
bool ReservationList::Remove(int reservationID, Reservation& removed){
  ReservationNode* current = head;
  ReservationNode* previous = nullptr;

  // Cycle through list
  while(current != nullptr && current->data.GetReservationID() != reservationID){
    previous = current;
    current = current->next;
  }

  // If ID is not found
  if(current == nullptr){
    return false;
  }
  removed = current->data;

  if(previous == nullptr){
    head = current-> next; // Reassign head if head was removed.
  } else {
    previous->next = current->next;
  }

  delete current;
  cout--;
  return true;
}

// Delete every node in the list
void ReservationList::Clear(){
  while (head != nullptr){
    ReservationNode* temp = head;
    head = head->next;
    delete temp;
  }

  count = 0;
}

// Check if the reservation ID already exists
bool ReservationList::Contains(int reservationID) const{
  ReservationNode* current = head;
  while(current != nullptr){
    if(current->data.GetReservationID() == reservationID){
      return true;
    }
    current = current->next;
  }
  return false;
}

// Function to find head value and size of List
ReservationNode* ReservationList::GetHead() const {
    return head;
}
int ReservationList::GetSize() const {
    return count;
}

// Traverse ReservationList, printing each one
void ReservationList::Traverse() const{
  ReservationNode* current = head;
  while(current != nullptr){
    current->data.Display();
    current = current->next;
  }
}

// Display all ReservationList
void ReservationList::Display() const{
  if (head == nullptr){
    cout << "No active reservations." << endl;
    return;
  }

  Traverse();
  cout << "Total Reservations: " << count << endl;
}
  

// Temporary, TBD.
  int main(){

  return 0;
}
