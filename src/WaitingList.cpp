#include "WaitingList.h"


// ---------------------------------------------------------
// Constructor
// ---------------------------------------------------------

WaitingList::WaitingList()
    : front(nullptr),
      rear(nullptr),
      size(0) {
}


// ---------------------------------------------------------
// Destructor
// ---------------------------------------------------------

WaitingList::~WaitingList() {

    // Remove every remaining node
    // so dynamically allocated memory is freed.

    while (!IsEmpty()) {

        WaitingRequest removed;

        Dequeue(removed);
    }
}


// ---------------------------------------------------------
// Enqueue
//
// Adds a student to the BACK of the waiting queue.
//
// Time Complexity: O(1)
// ---------------------------------------------------------

void WaitingList::Enqueue(
    int studentID,
    const string& studentName,
    const string& resourceID,
    const string& reservationDate
) {

    // Create the waiting request
    WaitingRequest request;

    request.studentID = studentID;
    request.studentName = studentName;
    request.resourceID = resourceID;
    request.reservationDate = reservationDate;


    // Create a new node containing the request
    WaitingNode* newNode =
        new WaitingNode(request);


    // If the queue is empty,
    // this node becomes both front and rear.
    if (IsEmpty()) {

        front = newNode;
        rear = newNode;
    }

    // Otherwise, attach the new node
    // to the current rear.
    else {

        rear->next = newNode;

        rear = newNode;
    }


    size++;
}


// ---------------------------------------------------------
// Dequeue
//
// Removes the student at the FRONT of the queue.
//
// Time Complexity: O(1)
// ---------------------------------------------------------

bool WaitingList::Dequeue(
    WaitingRequest& removed
) {

    // Nothing to remove
    if (IsEmpty()) {

        return false;
    }


    // Save the current front node
    WaitingNode* temp = front;


    // Copy its data before deleting it
    removed = front->data;


    // Move front to the next student
    front = front->next;


    // Delete the old front node
    delete temp;


    size--;


    // If the queue became empty,
    // rear must also become nullptr.
    if (front == nullptr) {

        rear = nullptr;
    }


    return true;
}


// ---------------------------------------------------------
// RemoveNextFor
//
// Finds and removes the FIRST student waiting for
// a specific resource AND reservation date.
//
// Because the search begins at the front of the queue,
// the earliest matching student is selected first.
//
// Time Complexity: O(n)
// ---------------------------------------------------------

bool WaitingList::RemoveNextFor(
    const string& resourceID,
    const string& reservationDate,
    WaitingRequest& removed
) {

    // Queue is empty
    if (IsEmpty()) {

        return false;
    }


    WaitingNode* current = front;

    WaitingNode* previous = nullptr;


    // Search from FRONT toward REAR
    while (current != nullptr) {


        // Does this request match the resource/date
        // that just became available?
        if (
            current->data.resourceID == resourceID &&
            current->data.reservationDate == reservationDate
        ) {


            // Save the student's information
            // before deleting the node.
            removed = current->data;


            // -----------------------------------------
            // CASE 1:
            // Matching student is at the FRONT
            // -----------------------------------------

            if (current == front) {

                front = front->next;


                // If that was the only node,
                // the queue is now empty.
                if (front == nullptr) {

                    rear = nullptr;
                }
            }


            // -----------------------------------------
            // CASE 2:
            // Matching student is somewhere after front
            // -----------------------------------------

            else {

                // Skip over the node being removed.
                previous->next =
                    current->next;


                // If we removed the last node,
                // update rear.
                if (current == rear) {

                    rear = previous;
                }
            }


            // Free memory
            delete current;


            size--;


            return true;
        }


        // Move forward through the queue
        previous = current;

        current = current->next;
    }


    // No student was waiting for
    // this resource/date.
    return false;
}


// ---------------------------------------------------------
// IsEmpty
//
// Returns true when there are no students waiting.
//
// Time Complexity: O(1)
// ---------------------------------------------------------

bool WaitingList::IsEmpty() const {

    return front == nullptr;
}


// ---------------------------------------------------------
// GetSize
//
// Returns number of waiting students.
//
// Time Complexity: O(1)
// ---------------------------------------------------------

int WaitingList::GetSize() const {

    return size;
}


// ---------------------------------------------------------
// Display
//
// Displays waiting requests from FRONT to REAR.
//
// Time Complexity: O(n)
// ---------------------------------------------------------

void WaitingList::Display() const {

    if (IsEmpty()) {

        cout << "Waiting list is empty."
             << endl;

        return;
    }


    cout << endl;

    cout << "--- Waiting List ---"
         << endl;


    WaitingNode* current = front;


    while (current != nullptr) {

        cout << "Student ID: "
             << current->data.studentID

             << " | Name: "
             << current->data.studentName

             << " | Resource: "
             << current->data.resourceID

             << " | Date: "
             << current->data.reservationDate

             << endl;


        current = current->next;
    }


    cout << size
         << " student(s) waiting."
         << endl;
}
