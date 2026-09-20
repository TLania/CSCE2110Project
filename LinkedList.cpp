#include "LinkedList.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

Reservations::Reservations(){ // Constructor
   head = nullptr; // Point head to tail node.
}

Reservations::~Reservations() { // Destructor
  Node* current = head;
  while (current != nullptr){
    Node* temp = current;
    current = current->next;
    delete temp;
  }
}

// Function to check if times overlap, for inserting functions
bool checkTimes(const string& newStart, const string& newEnd, const string& start, const string& end,
  const string& newLocation, const string& location){
  return (newStart < end && newEnd > start && location == newLocation);
}
// Insert Reservations
void Reservations::AddReservation(int id, const string& name, const string& location, const string& date,
  const string& start, const string& end) {

    Node* current = head;
    while (current != nullptr) { // Cycle through list to check for overlaps
      if(current-> resDate == date && checkTimes(start, end, current->startTime, current->endTime, location, current->resLocation)){
        cout << "Error: Reservation overlaps with an existing reservation. Please try another time.";
        return; 

      }
      current = current->next; 
    }

    Node* newNode = new Node(id, name, location, date, start, end); // Assign new node values
    if (head == nullptr){ // Enter node into new/empty list
      head = newNode;
      return;
    }
    current = head;
    while(current-> next != nullptr){ // Enter node at the end
      current = current->next;
    }
    current->next = newNode;
  }


// Remove reservation by ID
bool Reservations::removeReservation(int resID){
  if(head == nullptr){ // Check if the list is empty.
    return false;
  }
  if(head ->resID == resID){
    Node* temp = head;
    head = head->next; 
    delete temp;
    return true;
  }
  Node* current = head;
  while (current->next != nullptr && current->next->resID != resID){ // Cycle through list
    current = current->next;
  }

  if(current->next == nullptr){
    return false; // Return if the ID is not found.
  }

  Node* temp = current->next;
  current->next = current->next->next;
  delete temp;

  return true;
}
// Traverse reservations
void Reservations::traverse(void(*visit)(int, const string&, const string&, const string&)) const{
  Node* current = head;
  while(current != nullptr){
    visit(current->resID, current->resName, current->resLocation, current->resDate);
    
    current = current->next; // Cycle through list.
  }
}

// Display all reservations
void Reservations::display() const{
  Node* current = head;
  if(current == nullptr){ // Check if empty
    cout << "No reservations found." << endl;
    return;
  }

  cout << "********************Reservation List********************" << endl;
  cout << "| ID      | Name         | Date          | Location  |" << endl;
  cout << "--------------------------------------------------------" << endl;
  while(current != nullptr) {
    cout << " " << current->resID << setw(7) << " " << current->resName << setw(13) <<
      " " << current->resDate << setw(14) << " " << current->resLocation
       << setw(12) << endl;
    
    current = current->next;
  }
  cout << "--------------------------------------------------------" << endl;
}
  

// Temporary, TBD.
  int main(){

  return 0;
}