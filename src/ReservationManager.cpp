// ReservationManager.cpp
#include "ReservationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Turns a ReservationResult into a message
string GetResultMessage(ReservationResult result) {
    switch (result) {
        case RES_SUCCESS:
            return "Success.";
        case RES_INVALID_STUDENT_ID:
            return "Student ID must be a positive whole number.";
        case RES_INVALID_NAME:
            return "Student name cannot be empty.";
        case RES_INVALID_DATE:
            return "Date must be a real date in MM/DD/YYYY format (for example 09/25/2026).";
        case RES_RESOURCE_NOT_FOUND:
            return "No resource with that Resource ID exists.";
        case RES_RESOURCE_UNAVAILABLE:
            return "That resource is currently Unavailable.";
        case RES_DATE_CONFLICT:
            return "That resource is already reserved on that date.";
    }
    return "Unknown error.";
}


// Private helper functions
// ------------------------

// Makes a lowercase copy so comparisons ignore upper/lower case
string ReservationManager::toLowerCase(string text) const {
    for (unsigned int i = 0; i < text.size(); ++i) {
        text.at(i) = tolower(text.at(i));
    }
    return text;
}

// True only for a date written exactly as MM/DD/YYYY
bool ReservationManager::isValidDate(const string& date) const {
    // Must be 10 characters with a '/' in positions 2 and 5
    if (date.size() != 10 || date.at(2) != '/' || date.at(5) != '/') {
        return false;
    }
    // Every other character must be a # digit
    for (unsigned int i = 0; i < date.size(); ++i) {
        if (i != 2 && i != 5 && (date.at(i) < '0' || date.at(i) > '9')) {
            return false;
        }
    }

    int month = stoi(date.substr(0, 2));
    int day = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (year < 2000 || year > 2100 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
        daysInMonth[1] = 29;
    }
    return day <= daysInMonth[month - 1];
}

// how many reservations a search found
void ReservationManager::showMatchCount(int matches) const {
    if (matches == 0) {
        cout << "No reservations found." << endl;
    } else {
        cout << matches << " reservation(s) found." << endl;
    }
}

// Public functions
// ----------------

// Constructor
ReservationManager::ReservationManager(ResourceManager* resourceManager)
    : resources(resourceManager), nextReservationID(1) {}

// Load reservations from a file. Each line looks like: 301|1001|Alice Smith|R101|09/15/2026, from txt.
int ReservationManager::LoadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        return -1; // file not opened
    }

    activeReservations.Clear();
    string line;
    int highestID = 0;

    while (getline(inFile, line)) {
        // Remove the extra '\r' that a Windows text file leaves at the end of each line
        if (!line.empty() && line.at(line.size() - 1) == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue; // skip blank lines
        }

        // Split the line at each '|'
        stringstream lineStream(line);
        string idText, studentText, name, resourceID, date;
        getline(lineStream, idText, '|');
        getline(lineStream, studentText, '|');
        getline(lineStream, name, '|');
        getline(lineStream, resourceID, '|');
        getline(lineStream, date);

        // stoi() turns the text "301" into the number 301
        int reservationID = stoi(idText);
        activeReservations.InsertEnd(Reservation(reservationID, stoi(studentText), name, resourceID, date));
        if (reservationID > highestID) {
            highestID = reservationID;
        }
    }

    inFile.close();
    nextReservationID = highestID + 1;
    return activeReservations.GetSize();
}

// Check the request. If everything is valid, create the reservation and add it to the list
ReservationResult ReservationManager::CreateReservation(int studentID, const string& studentName, const string& resourceID, const string& date, Reservation& created) {
    if (studentID <= 0) {
        return RES_INVALID_STUDENT_ID;
    }
    if (studentName.empty()) {
        return RES_INVALID_NAME;
    }
    if (!isValidDate(date)) {
        return RES_INVALID_DATE;
    }

    int index = resources->FindByID(resourceID);
    if (index == -1) {
        return RES_RESOURCE_NOT_FOUND;
    }

    Resource resource = resources->GetResourceAt(index);
    if (!resource.IsAvailable()) {
        return RES_RESOURCE_UNAVAILABLE; // main.cpp, offer the waiting list here
    }
    if (IsResourceBooked(resource.GetID(), date)) {
        return RES_DATE_CONFLICT;        // main.cpp, offer the waiting list here
    }

    created = Reservation(nextReservationID, studentID, studentName, resource.GetID(), date);
    activeReservations.InsertEnd(created);
    nextReservationID++;
    return RES_SUCCESS;
}

// Remove an active reservation
// "cancelled" receives a copy (push it on the undo stack)
// Returns false if no active reservation has that ID
bool ReservationManager::CancelReservation(int reservationID, Reservation& cancelled) {
    return activeReservations.Remove(reservationID, cancelled);
}

// Put a cancelled reservation back, used by Undo Cancellation. It keeps its original ID
// It fails if someone else booked that resource on that date
ReservationResult ReservationManager::RestoreReservation(const Reservation& reservation) {
    // this reservation already existed before it was cancelled
    if (IsResourceBooked(reservation.GetResourceID(), reservation.GetDate())) {
        return RES_DATE_CONFLICT;
    }

    activeReservations.InsertEnd(reservation);
    if (reservation.GetReservationID() >= nextReservationID) {
        nextReservationID = reservation.GetReservationID() + 1;
    }
    return RES_SUCCESS;
}

// Accessors
int ReservationManager::GetSize() const {
    return activeReservations.GetSize();
}


bool ReservationManager::IsResourceBooked(const string& resourceID, const string& date) const {
    ReservationNode* current = activeReservations.GetHead();
    while (current != nullptr) {
        if (toLowerCase(current->data.GetResourceID()) == toLowerCase(resourceID) &&
            current->data.GetDate() == date) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Display every active reservation
void ReservationManager::DisplayAll() const {
    activeReservations.Display();
}

// Searches: walk through the list and show every reservation that matches
void ReservationManager::SearchByReservationID(int reservationID) const {
    int matches = 0;
    ReservationNode* current = activeReservations.GetHead();
    while (current != nullptr) {
        if (current->data.GetReservationID() == reservationID) {
            current->data.Display();
            matches++;
        }
        current = current->next;
    }
    showMatchCount(matches);
}

void ReservationManager::SearchByStudentID(int studentID) const {
    int matches = 0;
    ReservationNode* current = activeReservations.GetHead();
    while (current != nullptr) {
        if (current->data.GetStudentID() == studentID) {
            current->data.Display();
            matches++;
        }
        current = current->next;
    }
    showMatchCount(matches);
}

// Name search matches any part of the name, ignoring upper/lower case
void ReservationManager::SearchByStudentName(const string& keyword) const {
    string lowerKeyword = toLowerCase(keyword);
    int matches = 0;
    ReservationNode* current = activeReservations.GetHead();
    while (current != nullptr) {
        if (toLowerCase(current->data.GetStudentName()).find(lowerKeyword) != string::npos) {
            current->data.Display();
            matches++;
        }
        current = current->next;
    }
    showMatchCount(matches);
}

void ReservationManager::SearchByResourceID(const string& resourceID) const {
    string lowerID = toLowerCase(resourceID);
    int matches = 0;
    ReservationNode* current = activeReservations.GetHead();
    while (current != nullptr) {
        if (toLowerCase(current->data.GetResourceID()) == lowerID) {
            current->data.Display();
            matches++;
        }
        current = current->next;
    }
    showMatchCount(matches);
}

void ReservationManager::SearchByDate(const string& date) const {
    int matches = 0;
    ReservationNode* current = activeReservations.GetHead();
    while (current != nullptr) {
        if (current->data.GetDate() == date) {
            current->data.Display();
            matches++;
        }
        current = current->next;
    }
    showMatchCount(matches);
}
