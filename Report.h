#ifndef REPORT_H
#define REPORT_H
using namespace std;
#include "LinkedList.h"
#include "Resource.h"


class Report {
    protected:
    ReservationNode* head; // Head reservation to start traversal.
    int requests; // Count how many times a resource is reserved.

    public:
        Report(); // Constructor
        ~Report(); // Destructor

        // Print function for all active reservations
        void ActiveReservations() const;

        // How many reservations each resource type has
        void ResourceUtilization() const;

        // Show which resource has the highest amount of reservations
        void MostRequested() const;

        // Show statistics based on reservation waitlist data
        void WaitStats() const;
};


#endif
