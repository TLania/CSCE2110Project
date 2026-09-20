#ifndef WAITING_LIST_H
#define WAITING_LIST_H

#include <iostream>
#include <string>

using namespace std;


// Stores the information for one student
// waiting for a resource.
struct WaitingRequest {
    int studentID;
    string studentName;
    string resourceID;
    string reservationDate;
};


// Node used to build the waiting list queue.
struct WaitingNode {
    WaitingRequest data;
    WaitingNode* next;

    WaitingNode(const WaitingRequest& request)
        : data(request), next(nullptr) {
    }
};


// Waiting List Queue
class WaitingList {
private:

    // First student in the queue
    WaitingNode* front;

    // Last student in the queue
    WaitingNode* rear;

    // Number of students currently waiting
    int size;


public:

    // Constructor
    WaitingList();


    // Destructor
    ~WaitingList();


    // Add a student to the back of the queue
    void Enqueue(
        int studentID,
        const string& studentName,
        const string& resourceID,
        const string& reservationDate
    );


    // Remove the student at the front of the queue
    bool Dequeue(
        WaitingRequest& removed
    );


    // Find and remove the FIRST student waiting
    // for a specific resource and date.
    bool RemoveNextFor(
        const string& resourceID,
        const string& reservationDate,
        WaitingRequest& removed
    );


    // Check whether the queue is empty
    bool IsEmpty() const;


    // Return number of students waiting
    int GetSize() const;


    // Display everyone currently waiting
    void Display() const;
};


#endif
