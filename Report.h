#ifndef REPORT_H
#define REPORT_H
using namespace std;
#include "include/LinkedList.h" // For resource and reservation information
#include "include/Resource.h" // For resource type
#include "include/ReservationManager.h" // For Reservation list


class Report {
    protected:
    ReservationManager AllReservations; // Linked List of all active reservations.
    ReservationList ResList; // Pulls linked list of Reservations
    ResourceManager AllResources; // Object for linked lists
    int requests; // Count how many times a resource is reserved.

    public:
        Report(); // Constructor
        ~Report(); // Destructor

        Resource SearchResult(const string& resourceID); // Helper function to search

        // Print function for all active reservations
        void ActiveReservations() const;

        // How many reservations each resource type has
        void ResourceUtilization() const;

        // Show which resource has the highest amount of reservations
        void MostRequested() const;

        // Show statistics based on reservation waitlist data
        void WaitStats() const;

        void CompleteReport() const;
};


#endif
