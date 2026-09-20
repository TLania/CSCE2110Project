// ReservationList.h
// Linked list that stores the ACTIVE reservations.
//
// Note: the Linked List is my teammate's part. This just lets the
// Resource/Reservation code compile and run. If it's replaced, the new list must
// keep these functions because ReservationManager calls them:
// InsertEnd, Remove, Clear, Contains, GetHead (nodes have .data and .next), GetSize, Display
#ifndef RESERVATION_LIST_H
#define RESERVATION_LIST_H

#include <iostream>
#include "Reservation.h"
using namespace std;

// One node of the list
class ReservationNode {
public:
    Reservation data;
    ReservationNode* next;

    ReservationNode(const Reservation& r) : data(r), next(nullptr) {}
};

class ReservationList {
private:
    ReservationNode* head;
    int count; // number of reservations in the list

public:
    // Constructors
    ReservationList();
    ReservationList(const ReservationList& other); // Copy constructor

    // Destructor
    ~ReservationList();

    // Overloaded assignment operator
    ReservationList& operator=(const ReservationList& other);

    // Insert and remove
    void InsertEnd(const Reservation& reservation);
    bool Remove(int reservationID, Reservation& removed);
    void Clear();

    // Search and traverse
    bool Contains(int reservationID) const;
    void Traverse() const;
    ReservationNode* GetHead() const;
    int GetSize() const;

    // Display method
    void Display() const;
};

#endif // RESERVATION_LIST_H
