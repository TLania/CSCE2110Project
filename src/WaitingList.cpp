#include "WaitingList.h"


// Constructor
WaitingList::WaitingList()
    : front(nullptr), rear(nullptr), size(0) {
}


// Destructor
WaitingList::~WaitingList() {

    while (!IsEmpty()) {
        WaitingRequest removed;
        Dequeue(removed);
    }
}


// Add a student to the back of the waiting queue
void WaitingList::Enqueue(int studentID,
                          const string& studentName,
                          const string& resourceID,
                          const string& reservationDate) {

    WaitingRequest request;

    request.studentID = studentID;
    request.studentName = studentName;
    request.resourceID = resourceID;
    request.reservationDate = reservationDate;

    WaitingNode* newNode = new WaitingNode(request);

    if (IsEmpty()) {
        front = newNode;
        rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }

    size++;
}


// Remove the student at the front of the waiting queue
bool WaitingList::Dequeue(WaitingRequest& removed) {

    if (IsEmpty()) {
        return false;
    }

    WaitingNode* temp = front;

    removed = front->data;

    front = front->next;

    delete temp;

    size--;

    if (front == nullptr) {
        rear = nullptr;
    }

    return true;
}


// Check whether the queue is empty
bool WaitingList::IsEmpty() const {
    return front == nullptr;
}


// Return the number of students waiting
int WaitingList::GetSize() const {
    return size;
}


// Display the waiting queue
void WaitingList::Display() const {

    if (IsEmpty()) {
        cout << "Waiting list is empty." << endl;
        return;
    }

    WaitingNode* current = front;

    cout << endl;
    cout << "--- Waiting List ---" << endl;

    while (current != nullptr) {

        cout << "Student ID: " << current->data.studentID
             << " | Name: " << current->data.studentName
             << " | Resource: " << current->data.resourceID
             << " | Date: " << current->data.reservationDate
             << endl;

        current = current->next;
    }

    cout << size << " student(s) waiting." << endl;
}