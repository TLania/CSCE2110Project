#include "Report.h"
#include <iostream>

using namespace std;

Report::Report(ResourceManager& resourceManager,
               ReservationManager& reservationManager,
               const WaitingList& waitingListManager)
    : resources(resourceManager),
      reservations(reservationManager),
      waitingList(waitingListManager) {
}

void Report::ActiveReservations() const {
    cout << endl;
    cout << "--- Active Reservations ---" << endl;
    reservations.DisplayAll();
}

void Report::ResourceUtilization() const {
    cout << endl;
    cout << "--- Resource Utilization ---" << endl;

    if (resources.GetSize() == 0) {
        cout << "No resources loaded." << endl;
        return;
    }

    for (int i = 0; i < resources.GetSize(); i++) {
        Resource resource = resources.GetResourceAt(i);
        int activeCount =
            reservations.CountForResource(resource.GetID());

        cout << resource.GetID()
             << " | " << resource.GetName()
             << ": " << activeCount
             << " active reservation(s)"
             << endl;
    }
}

void Report::MostRequested() const {
    cout << endl;
    cout << "--- Most Requested Resource(s) ---" << endl;

    if (resources.GetSize() == 0) {
        cout << "No resources loaded." << endl;
        return;
    }

    int highestDemand = -1;

    // Current demand = active reservations + students currently waiting.
    for (int i = 0; i < resources.GetSize(); i++) {
        Resource resource = resources.GetResourceAt(i);

        int currentDemand =
            reservations.CountForResource(resource.GetID()) +
            waitingList.CountForResource(resource.GetID());

        if (currentDemand > highestDemand) {
            highestDemand = currentDemand;
        }
    }

    for (int i = 0; i < resources.GetSize(); i++) {
        Resource resource = resources.GetResourceAt(i);

        int currentDemand =
            reservations.CountForResource(resource.GetID()) +
            waitingList.CountForResource(resource.GetID());

        if (currentDemand == highestDemand) {
            cout << resource.GetID()
                 << " | " << resource.GetName()
                 << ": " << currentDemand
                 << " current request(s)"
                 << endl;
        }
    }
}

void Report::WaitStats() const {
    waitingList.DisplayStatistics();
}

void Report::CompleteReport() const {
    cout << endl;
    cout << "========== SYSTEM REPORT ==========" << endl;

    ActiveReservations();
    ResourceUtilization();
    MostRequested();
    WaitStats();

    cout << endl;
    cout << "===================================" << endl;
}
