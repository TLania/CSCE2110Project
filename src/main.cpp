// main.cpp - Main function
// Build (from the Project1 folder):  g++ -Iinclude -o go src/*.cpp
// Run   (from the Project1 folder):  ./go
#include <iostream>
#include <string>
#include <cstdlib>     // exit()
#include "ResourceManager.h"
#include "ReservationManager.h"
using namespace std;

// ---------------------------------------------------------------------------
// Input helper functions
// ---------------------------------------------------------------------------

// Removes spaces at the start and end of what the user typed
// (size_t is the type a string uses for positions)
string trim(string text) {
    size_t first = text.find_first_not_of(" \t");
    if (first == string::npos) {
        return ""; // nothing but spaces
    }
    size_t last = text.find_last_not_of(" \t");
    return text.substr(first, last - first + 1);
}

// Reads a whole number. Returns -1 if the user typed something that is not a number.
int readNumber(const string& prompt) {
    int number = 0;
    cout << prompt;
    cin >> number;

    if (cin.fail()) {
        if (cin.eof()) {
            cout << endl << "End of input. Exiting." << endl;
            exit(0);
        }
        cin.clear();            // clear the error so cin works again
        cin.ignore(1000, '\n'); // throw away the bad input
        return -1;
    }
    cin.ignore(1000, '\n');     // clear the newline so a later getline works
    return number;
}

// Reads a whole line of text (spaces allowed) and trims it
string readText(const string& prompt) {
    string text;
    cout << prompt;
    if (!getline(cin, text)) {
        cout << endl << "End of input. Exiting." << endl;
        exit(0);
    }
    return trim(text);
}

// ---------------------------------------------------------------------------
// Menu functions
// ---------------------------------------------------------------------------

void printMenu() {
    cout << endl;
    cout << "===== Campus Resource Reservation System =====" << endl;
    cout << "1. View Resources" << endl;
    cout << "2. Create Reservation" << endl;
    cout << "3. Cancel Reservation" << endl;
    cout << "4. View Waiting Lists" << endl;
    cout << "5. Undo Cancellation" << endl;
    cout << "6. Search Reservations" << endl;
    cout << "7. Sort Resources" << endl;
    cout << "8. Generate Report" << endl;
    cout << "9. Exit" << endl;
}

// Option 1: display or search resources (Resource Management)
void viewResources(ResourceManager& resources) {
    cout << endl << "--- View Resources ---" << endl;
    cout << "1. Display all resources" << endl;
    cout << "2. Search by Resource ID" << endl;
    cout << "3. Search by Name" << endl;
    cout << "4. Search by Type" << endl;
    cout << "5. Filter by Availability" << endl;
    cout << "0. Back" << endl;
    int choice = readNumber("Enter Choice: ");

    switch (choice) {
        case 0:
            return;
        case 1:
            resources.DisplayAll();
            break;
        case 2:
            resources.SearchByID(readText("Resource ID: "));
            break;
        case 3:
            resources.SearchByName(readText("Name (or part of it): "));
            break;
        case 4:
            resources.SearchByType(readText("Type (or part of it): "));
            break;
        case 5: {
            cout << "1. Available" << endl;
            cout << "2. Unavailable" << endl;
            int statusChoice = readNumber("Enter Choice: ");
            if (statusChoice == 1) {
                resources.SearchByStatus("Available");
            } else if (statusChoice == 2) {
                resources.SearchByStatus("Unavailable");
            } else {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice. Please enter a number from the menu." << endl;
    }
}

// Option 2: create a reservation (Reservation Management)
void createReservation(ReservationManager& reservations) {
    cout << endl << "--- Create Reservation ---" << endl;

    int studentID = readNumber("Student ID: ");
    if (studentID <= 0) {
        cout << GetResultMessage(RES_INVALID_STUDENT_ID) << endl;
        return;
    }
    string name = readText("Student Name: ");
    string resourceID = readText("Resource ID: ");
    string date = readText("Reservation Date (MM/DD/YYYY): ");

    Reservation created;
    ReservationResult result = reservations.CreateReservation(studentID, name, resourceID, date, created);

    if (result == RES_SUCCESS) {
        cout << "Reservation Created Successfully." << endl;
        cout << "Reservation ID: " << created.GetReservationID() << endl;
    } else {
        cout << "Reservation could not be created: " << GetResultMessage(result) << endl;

        if (result == RES_RESOURCE_UNAVAILABLE || result == RES_DATE_CONFLICT) {
            // INTEGRATION POINT (Waiting List teammate):
            // The resource can't be reserved right now, so offer to add this student to
            // that resource's waiting list (queue), for example:
            //     waitingLists.AddStudent(resourceID, studentID, name);
        }
    }
}

// Option 3: cancel a reservation (Reservation Management)
void cancelReservation(ReservationManager& reservations) {
    cout << endl << "--- Cancel Reservation ---" << endl;

    int reservationID = readNumber("Reservation ID: ");
    if (reservationID <= 0) {
        cout << "Invalid Reservation ID. Please enter a positive whole number (for example 301)." << endl;
        return;
    }

    Reservation cancelled;
    if (reservations.CancelReservation(reservationID, cancelled)) {
        cout << "Reservation Cancelled." << endl;

        // INTEGRATION POINT (Cancellation History teammate):
        // Push the cancelled reservation onto the stack, for example:
        //     cancellationHistory.Push(cancelled);
        //     cout << "Added to cancellation history." << endl;
        //
        // INTEGRATION POINT (Waiting List teammate):
        // If a student is waiting for cancelled.GetResourceID(), take the first one off the
        // queue and reserve cancelled.GetDate() for them.
    } else {
        cout << "No active reservation found with ID " << reservationID << "." << endl;
    }
}

// Option 4: view waiting lists (Waiting List teammate)
void viewWaitingLists() {
    // INTEGRATION POINT: waitingLists.Display();
    cout << "View Waiting Lists is not connected yet (Waiting List part)." << endl;
}

// Option 5: undo the most recent cancellation (Cancellation History teammate)
void undoCancellation() {
    // INTEGRATION POINT: pass the ReservationManager into this function, then
    //     Reservation restored = cancellationHistory.Pop();
    //     ReservationResult result = reservations.RestoreReservation(restored);
    //     if (result == RES_SUCCESS) {
    //         cout << "Reservation Restored Successfully." << endl;
    //     } else {
    //         cout << "Could not restore: " << GetResultMessage(result) << endl;
    //     }
    cout << "Undo Cancellation is not connected yet (Cancellation History part)." << endl;
}

// Option 6: view or search reservations (Reservation Management)
void searchReservations(ReservationManager& reservations) {
    cout << endl << "--- Search Reservations ---" << endl;
    cout << "1. View all active reservations" << endl;
    cout << "2. Search by Reservation ID" << endl;
    cout << "3. Search by Student ID" << endl;
    cout << "4. Search by Student Name" << endl;
    cout << "5. Search by Resource ID" << endl;
    cout << "6. Search by Date (MM/DD/YYYY)" << endl;
    cout << "0. Back" << endl;
    int choice = readNumber("Enter Choice: ");

    switch (choice) {
        case 0:
            return;
        case 1:
            reservations.DisplayAll();
            break;
        case 2:
            reservations.SearchByReservationID(readNumber("Reservation ID: "));
            break;
        case 3:
            reservations.SearchByStudentID(readNumber("Student ID: "));
            break;
        case 4:
            reservations.SearchByStudentName(readText("Student Name (or part of it): "));
            break;
        case 5:
            reservations.SearchByResourceID(readText("Resource ID: "));
            break;
        case 6:
            reservations.SearchByDate(readText("Date (MM/DD/YYYY): "));
            break;
        default:
            cout << "Invalid choice. Please enter a number from the menu." << endl;
    }
}

// Option 7: sort the resources (Resource Management)
void sortResources(ResourceManager& resources) {
    cout << endl << "--- Sort Resources ---" << endl;
    cout << "1. Resource ID" << endl;
    cout << "2. Resource Name" << endl;
    cout << "3. Resource Type" << endl;
    cout << "4. Availability Status" << endl;
    cout << "0. Back" << endl;
    int choice = readNumber("Sort by: ");

    switch (choice) {
        case 0:
            return;
        case 1:
            resources.SortByID();
            break;
        case 2:
            resources.SortByName();
            break;
        case 3:
            resources.SortByType();
            break;
        case 4:
            resources.SortByStatus();
            break;
        default:
            cout << "Invalid choice. Please enter a number from the menu." << endl;
            return;
    }
    cout << "Resources sorted." << endl;
    resources.DisplayAll();
}

// Option 8: generate a report (Report Generator)
void generateReport() {
    // INTEGRATION POINT: the report can use the resource and reservation managers
    cout << "Generate Report is not connected yet (Report Generator part)." << endl;
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
int main() {
    ResourceManager resources;
    ReservationManager reservations(&resources); // & gives the manager the address of the resource list

    // Resources must be loaded first because reservations use them
    int resourceCount = resources.LoadFromFile("data/resources.txt");
    if (resourceCount == -1) {
        cout << "Error: could not open data/resources.txt" << endl;
        cout << "Run the program from the Project1 folder." << endl;
        return 1;
    }
    cout << "Loaded " << resourceCount << " resources." << endl;

    int reservationCount = reservations.LoadFromFile("data/reservations.txt");
    if (reservationCount == -1) {
        cout << "Warning: could not open data/reservations.txt. Starting with no reservations." << endl;
    } else {
        cout << "Loaded " << reservationCount << " reservations." << endl;
    }

    // INTEGRATION POINT: create the other team members' objects here, for example
    //     WaitingList waitingLists;
    //     CancellationHistory cancellationHistory;

    int choice = 0;
    do {
        printMenu();
        choice = readNumber("Enter Choice: ");

        switch (choice) {
            case 1:
                viewResources(resources);
                break;
            case 2:
                createReservation(reservations);
                break;
            case 3:
                cancelReservation(reservations);
                break;
            case 4:
                viewWaitingLists();
                break;
            case 5:
                undoCancellation();
                break;
            case 6:
                searchReservations(reservations);
                break;
            case 7:
                sortResources(resources);
                break;
            case 8:
                generateReport();
                break;
            case 9:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 9." << endl;
        }
    } while (choice != 9);

    return 0;
}
