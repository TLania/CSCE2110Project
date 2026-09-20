#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

class Reservations {
    protected:
        // Node and all information that is stored in each one.
        struct Node {
            int resID; // So reservations do not overlap.
            string resName;
            string resLocation;
            string resDate;
            string startTime;
            string endTime;
            Node* next; // Pointer that points to next node.

            // Header node to assign values.

            Node(int id, const string& name,const string& location, const string& date,const string& start, const string& end){
                resID = id;
                resName = name;
                resLocation = location;
                resDate = date;
                startTime = start;
                endTime = end;
                next = nullptr; // Points to tail/next node.
            }
        };

        // Declare head node
        Node* head;
        
    public:
        Reservations(); // Default Constructor
        ~Reservations(); // Destructor

        // Insert, remove, traverse, and display functions.
        void AddReservation(int id, const string& name, const string& location, const string& date, const string& start, const string& end);
        bool removeReservation(int resID); // Remove reservation of given ID
        void traverse (void (*visit)(int, const string&, const string&, const string&)) const;
        void display() const;

};


#endif

