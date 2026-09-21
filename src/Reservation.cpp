// Reservation.cpp
#include "Reservation.h"
#include <iostream>
using namespace std;

// Default Constructor
Reservation::Reservation() : reservationID(0), studentID(0), studentName("none"),
    resourceID("none"), reservationDate("none") {}

// Overloaded Constructor
Reservation::Reservation(int id, int studentId, const string& name, const string& resourceId, const string& date)
    : reservationID(id), studentID(studentId), studentName(name), resourceID(resourceId),
      reservationDate(date) {}

// Accessors
int Reservation::GetReservationID() const {
    return reservationID;
}

int Reservation::GetStudentID() const {
    return studentID;
}

string Reservation::GetStudentName() const {
    return studentName;
}

string Reservation::GetResourceID() const {
    return resourceID;
}

string Reservation::GetDate() const {
    return reservationDate;
}

// Mutators
void Reservation::SetReservationID(int id) {
    reservationID = id;
}

void Reservation::SetStudentID(int id) {
    studentID = id;
}

void Reservation::SetStudentName(const string& name) {
    studentName = name;
}

void Reservation::SetResourceID(const string& id) {
    resourceID = id;
}

void Reservation::SetDate(const string& date) {
    reservationDate = date;
}

// Display one reservation on a single line
void Reservation::Display() const {
    cout << "Reservation ID: " << reservationID << " | "
         << "Student ID: " << studentID << " | "
         << "Name: " << studentName << " | "
         << "Resource: " << resourceID << " | "
         << "Date: " << reservationDate << endl;
}
