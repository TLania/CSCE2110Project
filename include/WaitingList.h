#ifndef WAITING_LIST_H
#define WAITING_LIST_H

#include <iostream>
#include <string>
using namespace std;


// Stores information about one student waiting for a resource
struct WaitingRequest {
    int studentID;
    string studentName;
    string resourceID;
    string reservationDate;
};


// Node used to build the waiting list queue
struct WaitingNode {
    WaitingRequest data;
    WaitingNode* next;

    WaitingNode(const WaitingRequest& request)
        : data(request), next(nullptr) {}
};


class WaitingList {
private:
    WaitingNode* front;
    WaitingNode* rear;
    int size;

public:
    // Constructor
    WaitingList();

    // Destructor
    ~WaitingList();

    // Queue operations
    void Enqueue(int studentID,
                 const string& studentName,
                 const string& resourceID,
                 const string& reservationDate);

    bool Dequeue(WaitingRequest& removed);

    bool IsEmpty() const;

    int GetSize() const;

    // Display everyone currently waiting
    void Display() const;
};

#endif