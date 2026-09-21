#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Reservation.h"
#include <iostream>
using namespace std;

// Call back node information from Reservations
class ReservationNode{
    public:
        Reservation data;
        ReservationNode* next;

        ReservationNode(const Reservation& r) : data(r), next(nullptr){}
};
class ReservationList {
    private:
        ReservationNode* head;
        int count; // Total number of reservations on the list.
    public:
        ReservationList(); // Default Constructor
        ReservationList(const ReservationList& other); // Copy Constructor
        ~ReservationList(); // Destructor
        ReservationList& operator =(const ReservationList& other); // Overloaded Assignment Operator
        
        // Insert, remove, traverse, and display functions.
        void InsertEnd(const Reservation& reservation);
        void Remove(int reservationID, Reservation& removed);
        void Clear();

        bool Contains(int reservationID) const; // Check if Node exists.
        void Traverse() const;
        ReservationNode* GetHead() const; // Find the first reservation in the list.
        int GetSize() const; // Total amount of reservations.
        void Display() const;

};


#endif

