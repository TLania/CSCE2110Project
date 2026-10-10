#include "Report.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Helper Functions
struct Counter{ // Vector values to count
    string resourceType;
    int count;

};

// Constructor
Report::Report() : AllReservations(0) { // Initialize Reservations and requests to 0
    
    requests = 0;
}

// Show Active Reservations
void Report::ActiveReservations() const{
    cout << "Active Reservations" << endl;
    cout << "----------------------------------------" << endl;
    AllReservations.DisplayAll(); // Prints every active Reservation.
    cout << "----------------------------------------" << endl;
}

// Show information using the resource type and amount of corresponding reservations.
void Report::ResourceUtilization() const{
    vector<Counter> TypeCounter; // vector to store counted values
    ReservationManager current = ResList.GetHead();

}


