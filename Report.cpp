#include "Report.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// *** Helper Functions ***
vector<Counter> Report::GetCounts() const{
    vector<Counter> TypeCounter; // vector to store counted values by Resource Type

// Class objects and head node
    ReservationNode* current = ResList.GetHead(); 

    if(current == nullptr){ // Check to see if list is empty.
        cout << "No active reservations have been made." << endl;
        return TypeCounter;
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

    return TypeCounter;

}

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

// Destructor
Report::~Report() {}
// Show Active Reservations
void Report::ActiveReservations() const{
    cout << "Active Reservations" << endl;
    cout << "----------------------------------------" << endl;
    AllReservations.DisplayAll(); // Prints every active Reservation.
    cout << "----------------------------------------" << endl;
}

// Show information using the resource type and amount of corresponding reservations.
void Report::ResourceUtilization() const{
   vector<Counter> TypeCounter = GetCounts(); // Call vector helper functions

   if(TypeCounter.empty()){ // Check if vector is empty
    cout << "There are no reservations made." << endl;
    return;
   }

    // Printing
    cout << "------Resource Utilization Report-------" << endl;
    cout << "----------------------------------------" << endl;

    for( int i = 0; i < TypeCounter.size(); ++i){ // Loops through vector
        cout << TypeCounter[i].resourceType << " usage amount: " << TypeCounter[i].count << endl;
    }
}


void Report::MostRequested() const{
    vector<Counter> TypeCounter = GetCounts(); // recall same functions

    if(TypeCounter.empty()){
        cout << "There is no active reservations." << endl;
        return;
    }

    int most = TypeCounter[0].count;
    string mostResource = TypeCounter[0].resourceType;

    for(int i = 1; i <TypeCounter.size(); ++i){
        if(TypeCounter[i].count > most){
            most = TypeCounter[i].count;
            mostResource = TypeCounter[i].resourceType;
        }
    }

    cout << "Most requested Resource: " << mostResource << " -- Requested " << most << " times." << endl;

}

// Displayu Waiting List Statistics
void Report::WaitStats() const{
    // ***Calculations***
    Report rep;
    // Least requested
    vector<Counter> TypeCounter = GetCounts();
    if(TypeCounter.empty()){
        cout << "There is no active reservations." << endl;
        return;
    }
    int least = TypeCounter[0].count;
    string leastResource = TypeCounter[0].resourceType;
    for(int i = 1; i < TypeCounter.size(); ++i){
        if(TypeCounter[i].count < least){
            least = TypeCounter[i].count;
            leastResource = TypeCounter[i].resourceType;
        }
    }

    cout << "Waiting List Statistics" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Current waiting list size: " << WaitList.GetSize() << endl;
    MostRequested(); // Prints previous stats
    cout << "Least requested resource: " << leastResource << " -- Requested " << least << " times." << endl;
    cout << "Number of resources available: " << AllResources.GetSize() << endl;    
}
