#ifndef REPORT_H
#define REPORT_H

#include "ResourceManager.h"
#include "ReservationManager.h"
#include "WaitingList.h"

class Report {
private:
    ResourceManager& resources;
    ReservationManager& reservations;
    const WaitingList& waitingList;

public:
    Report(ResourceManager& resourceManager,
           ReservationManager& reservationManager,
           const WaitingList& waitingListManager);

    void ActiveReservations() const;
    void ResourceUtilization() const;
    void MostRequested() const;
    void WaitStats() const;
    void CompleteReport() const;
};

#endif
