// ReservationManager.h
// Handles reservation operations: load, create, cancel, view, search, restore.
// Relation to teammates:
//   - Active reservations are kept in a ReservationList (linked list).
//   - CancelReservation() gives back the cancelled reservation so it can be pushed onto  
// the cancellation-history stack. RestoreReservation() takes one popped from that stack.
//   - CreateReservation() reports WHY it failed (see ReservationResult), so main.cpp can
//     offer the waiting list when the resource is unavailable or booked
#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <iostream>
#include <string>
#include "Reservation.h"
#include "LinkedList.h"
#include "ResourceManager.h"
using namespace std;

// Names for the outcomes of creating or restoring a reservation
enum ReservationResult {
    RES_SUCCESS,
    RES_INVALID_STUDENT_ID,
    RES_INVALID_NAME,
    RES_INVALID_DATE,
    RES_RESOURCE_NOT_FOUND,
    RES_RESOURCE_UNAVAILABLE,
    RES_DATE_CONFLICT
};

// Turns a ReservationResult into a readable
string GetResultMessage(ReservationResult result);

class ReservationManager {
private:
    ReservationList activeReservations; // linked list of active reservations
    ResourceManager* resources;         // used to check resource IDs
    int nextReservationID;              // ID given to the next new reservation

    // Private helper func
    string toLowerCase(string text) const;
    bool isValidDate(const string& date) const;
    void showMatchCount(int matches) const;

public:
    // Constructor 
    ReservationManager(ResourceManager* resourceManager);

    // File input,returns number of reservations loaded
    int LoadFromFile(const string& filename);

    // Create, cancel, restore
    ReservationResult CreateReservation(int studentID, const string& studentName, const string& resourceID, const string& date, Reservation& created);
    bool CancelReservation(int reservationID, Reservation& cancelled);
    ReservationResult RestoreReservation(const Reservation& reservation);

    // Accessors
    int GetSize() const;
    bool IsResourceBooked(const string& resourceID, const string& date) const;

    // Display
    void DisplayAll() const;

    // Search
    void SearchByReservationID(int reservationID) const;
    void SearchByStudentID(int studentID) const;
    void SearchByStudentName(const string& keyword) const;
    void SearchByResourceID(const string& resourceID) const;
    void SearchByDate(const string& date) const;
};

#endif // RESERVATION_MANAGER_H