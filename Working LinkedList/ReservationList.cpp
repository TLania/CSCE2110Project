// ReservationList.cpp
#include "ReservationList.h"
#include <iostream>
using namespace std;

// Default Constructor
ReservationList::ReservationList() : head(nullptr), count(0) {}

// Copy Constructor
ReservationList::ReservationList(const ReservationList& other) : head(nullptr), count(0) {
    ReservationNode* current = other.head;
    while (current != nullptr) {
        InsertEnd(current->data);
        current = current->next;
    }
}

// Destructor
ReservationList::~ReservationList() {
    Clear();
}

// Overloaded assignment operator
ReservationList& ReservationList::operator=(const ReservationList& other) {
    if (this != &other) {
        Clear();
        ReservationNode* current = other.head;
        while (current != nullptr) {
            InsertEnd(current->data);
            current = current->next;
        }
    }
    return *this;
}

// Insert a reservation at the end of the list
void ReservationList::InsertEnd(const Reservation& reservation) {
    ReservationNode* newNode = new ReservationNode(reservation);
    if (head == nullptr) {
        head = newNode;
    } else {
        ReservationNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
}

// Remove the reservation with this ID
// The removed reservation is copied into "removed" so the caller can keep it
// Returns false if no reservation has that ID
bool ReservationList::Remove(int reservationID, Reservation& removed) {
    ReservationNode* current = head;
    ReservationNode* previous = nullptr;

    // Walk down the list until the ID is found or the end is reached
    while (current != nullptr && current->data.GetReservationID() != reservationID) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        return false; // not found
    }

    removed = current->data;

    if (previous == nullptr) {
        head = current->next;          // removing the first node
    } else {
        previous->next = current->next; // skip over the node being removed
    }

    delete current;
    count--;
    return true;
}

// Delete every node
void ReservationList::Clear() {
    while (head != nullptr) {
        ReservationNode* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
}

// Check if a reservation ID is already in the list
bool ReservationList::Contains(int reservationID) const {
    ReservationNode* current = head;
    while (current != nullptr) {
        if (current->data.GetReservationID() == reservationID) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Lets the manager walk through the list itself
ReservationNode* ReservationList::GetHead() const {
    return head;
}

int ReservationList::GetSize() const {
    return count;
}

// Traverse the list: visit every reservation from the first node to the last
// and show each one
void ReservationList::Traverse() const {
    ReservationNode* current = head;
    while (current != nullptr) {
        current->data.Display();
        current = current->next;
    }
}

// Display every reservation in the list, followed by the total
void ReservationList::Display() const {
    if (head == nullptr) {
        cout << "No active reservations." << endl;
        return;
    }

    Traverse();
    cout << "Total reservations: " << count << endl;
}

