#include "CancellationHistory.h"


// Constructor
CancellationHistory::CancellationHistory()
    : top(nullptr), size(0) {
}


// Destructor
CancellationHistory::~CancellationHistory() {

    while (!IsEmpty()) {
        Reservation removed;
        Pop(removed);
    }
}


// Add a cancelled reservation to the top of the stack
void CancellationHistory::Push(const Reservation& reservation) {

    CancellationNode* newNode =
        new CancellationNode(reservation);

    newNode->next = top;

    top = newNode;

    size++;
}


// Remove the most recently cancelled reservation
bool CancellationHistory::Pop(Reservation& removed) {

    if (IsEmpty()) {
        return false;
    }

    CancellationNode* temp = top;

    removed = top->data;

    top = top->next;

    delete temp;

    size--;

    return true;
}


// View the most recent cancellation without removing it
bool CancellationHistory::Peek(Reservation& reservation) const {

    if (IsEmpty()) {
        return false;
    }

    reservation = top->data;

    return true;
}


// Check whether the stack is empty
bool CancellationHistory::IsEmpty() const {
    return top == nullptr;
}


// Return number of cancelled reservations
int CancellationHistory::GetSize() const {
    return size;
}


// Display cancellation history from newest to oldest
void CancellationHistory::Display() const {

    if (IsEmpty()) {
        cout << "Cancellation history is empty." << endl;
        return;
    }

    cout << endl;
    cout << "--- Cancellation History ---" << endl;

    CancellationNode* current = top;

    while (current != nullptr) {

        current->data.Display();

        current = current->next;
    }

    cout << size << " cancelled reservation(s)." << endl;
}