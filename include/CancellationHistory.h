#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H

#include <iostream>
#include "Reservation.h"
using namespace std;


// Node used to build the cancellation history stack
struct CancellationNode {
    Reservation data;
    CancellationNode* next;

    CancellationNode(const Reservation& reservation)
        : data(reservation), next(nullptr) {}
};


class CancellationHistory {
private:
    CancellationNode* top;
    int size;

public:
    // Constructor
    CancellationHistory();

    // Destructor
    ~CancellationHistory();

    // Stack operations
    void Push(const Reservation& reservation);

    bool Pop(Reservation& removed);

    bool Peek(Reservation& reservation) const;

    bool IsEmpty() const;

    int GetSize() const;

    // Display cancellation history
    void Display() const;
};

#endif