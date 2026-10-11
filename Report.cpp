#include "Report.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// *** Helper Functions ***
struct Counter{ // Vector values to count
    string resourceType;
    int count;

};

Resource Report::SearchResult(const string& sourceID){ // Function to search and return each corresponding resource by ID
    int value = AllResources.FindByID(sourceID);

    if(value == 0){ // Check if there is an ID 
        return Resource();
    }

    return AllResources.GetResourceAt(value);
}



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
    vector<Counter> TypeCounter; // vector to store counted values by Resource Type

    // Class objects and head node
    ReservationNode* current = ResList.GetHead(); 
    
    if(current == nullptr){ // Check to see if list is empty.
        cout << "No active reservations have been made." << endl;
        return;
    }
    while(current != nullptr){ // Cycles through list to count and find resource types.
        int temp = AllResources.FindByID(current->data.GetResourceID()); // temp value to store the ID

        bool reoccuring = false;
        if(temp != 0){
            Resource resource = AllResources.GetResourceAt(temp); // Find corresponding Resource
            string type = resource.GetType(); // Get specific type

            for(int i = 0; i <TypeCounter.size();++i){ // Begin count if it hasn't been counted yet
                if(TypeCounter[i].resourceType == type){
                    TypeCounter[i].count++;
                    reoccuring = true;
                    break;
                }
            }

            if(!reoccuring){ // The resource has been counted.
                Counter tempCount;
                tempCount.resourceType = type;
                tempCount.count = 1;

                TypeCounter.push_back(tempCount);


            }
        }

        current = current->next; // Point to next value
    }
}
