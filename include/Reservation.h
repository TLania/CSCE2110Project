// Reservation.h
#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <string>
using namespace std;

class Reservation {
private:
    int reservationID;
    int studentID;
    string studentName;
    string resourceID;
    string reservationDate; // stored as MM/DD/YYYY

public:
    // Constructors
    Reservation();
    Reservation(int id, int studentId, const string& name, const string& resourceId, const string& date);

    // Accessors (Getters)
    int GetReservationID() const;
    int GetStudentID() const;
    string GetStudentName() const;
    string GetResourceID() const;
    string GetDate() const;

    // Mutators (Setters)
    void SetReservationID(int id);
    void SetStudentID(int id);
    void SetStudentName(const string& name);
    void SetResourceID(const string& id);
    void SetDate(const string& date);

    // Display method
    void Display() const;
};

#endif // RESERVATION_H
