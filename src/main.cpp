// main.cpp - Main function
// Build (from the Project1 folder):  g++ -Iinclude -o go src/*.cpp
// Run   (from the Project1 folder):  ./go

#include <iostream>
#include <string>
#include <cstdlib>     // exit()
#include "ResourceManager.h"
#include "ReservationManager.h"
#include "CancellationHistory.h"
#include "WaitingList.h"

using namespace std;


// Input helper functions
// ----------------------

// Removes spaces at the start and end of what the user typed
string trim(string text) {
    size_t first = text.find_first_not_of(" \t");

    if (first == string::npos) {
        return "";
    }

    size_t last = text.find_last_not_of(" \t");

    return text.substr(first, last - first + 1);
}


// Reads a whole number
int readNumber(const string& prompt) {
    int number = 0;

    cout << prompt;
    cin >> number;

    if (cin.fail()) {

        if (cin.eof()) {
            cout << endl << "End of input. Exiting." << endl;
            exit(0);
        }

        cin.clear();
        cin.ignore(1000, '\n');

        return -1;
    }

    cin.ignore(1000, '\n');

    return number;
}


// Reads a whole line of text and trims it
string readText(const string& prompt) {
    string text;

    cout << prompt;

    if (!getline(cin, text)) {
        cout << endl << "End of input. Exiting." << endl;
        exit(0);
    }

    return trim(text);
}


// Menu functions
// --------------

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


// ---------------------------------------------------------
// OPTION 1
// Resource Management
// ---------------------------------------------------------

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
            resources.SearchByID(
                readText("Resource ID: ")
            );
            break;

        case 3:
            resources.SearchByName(
                readText("Name (or part of it): ")
            );
            break;

        case 4:
            resources.SearchByType(
                readText("Type (or part of it): ")
            );
            break;

        case 5: {

            cout << "1. Available" << endl;
            cout << "2. Unavailable" << endl;

            int statusChoice =
                readNumber("Enter Choice: ");

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

            cout << "Invalid choice. "
                 << "Please enter a number from the menu."
                 << endl;
    }
}


// ---------------------------------------------------------
// OPTION 2
// Create Reservation + Waiting List Integration
// ---------------------------------------------------------

void createReservation(
    ReservationManager& reservations,
    WaitingList& waitingLists
) {

    cout << endl
         << "--- Create Reservation ---"
         << endl;


    int studentID =
        readNumber("Student ID: ");


    if (studentID <= 0) {

        cout << GetResultMessage(
                    RES_INVALID_STUDENT_ID
                )
             << endl;

        return;
    }


    string name =
        readText("Student Name: ");

    string resourceID =
        readText("Resource ID: ");

    string date =
        readText(
            "Reservation Date (MM/DD/YYYY): "
        );


    Reservation created;


    ReservationResult result =
        reservations.CreateReservation(
            studentID,
            name,
            resourceID,
            date,
            created
        );


    // Reservation was successful
    if (result == RES_SUCCESS) {

        cout << "Reservation Created Successfully."
             << endl;

        cout << "Reservation ID: "
             << created.GetReservationID()
             << endl;
    }

    // Reservation failed
    else {

        cout << "Reservation could not be created: "
             << GetResultMessage(result)
             << endl;


        // -----------------------------------------
        // WAITING LIST INTEGRATION
        // -----------------------------------------

        if (result == RES_RESOURCE_UNAVAILABLE ||
            result == RES_DATE_CONFLICT) {

            string answer =
                readText(
                    "Would you like to join "
                    "the waiting list? (y/n): "
                );


            if (answer == "y" ||
                answer == "Y") {

                waitingLists.Enqueue(
                    studentID,
                    name,
                    resourceID,
                    date
                );


                cout << "Added to waiting list."
                     << endl;
            }

            else {

                cout << "Not added to waiting list."
                     << endl;
            }
        }
    }
}


// ---------------------------------------------------------
// OPTION 3
// Cancel Reservation
//
// Integrates BOTH:
//      Cancellation History
//      Waiting List
// ---------------------------------------------------------

void cancelReservation(
    ReservationManager& reservations,
    CancellationHistory& cancellationHistory,
    WaitingList& waitingLists
) {

    cout << endl
         << "--- Cancel Reservation ---"
         << endl;


    int reservationID =
        readNumber("Reservation ID: ");


    if (reservationID <= 0) {

        cout << "Invalid Reservation ID. "
             << "Please enter a positive whole number "
             << "(for example 301)."
             << endl;

        return;
    }


    Reservation cancelled;


    // Try to cancel reservation
    if (reservations.CancelReservation(
            reservationID,
            cancelled
        )) {


        cout << "Reservation Cancelled."
             << endl;


        // =========================================
        // CANCELLATION HISTORY INTEGRATION
        // =========================================

        cancellationHistory.Push(cancelled);

        cout << "Added to cancellation history."
             << endl;


        // =========================================
        // WAITING LIST INTEGRATION
        // =========================================

        // Look for the FIRST student waiting
        // for this exact resource and date.

        WaitingRequest nextStudent;


        bool studentWaiting =
            waitingLists.RemoveNextFor(
                cancelled.GetResourceID(),
                cancelled.GetDate(),
                nextStudent
            );


        if (studentWaiting) {

            cout << "Student found on waiting list."
                 << endl;


            Reservation created;


            ReservationResult result =
                reservations.CreateReservation(
                    nextStudent.studentID,
                    nextStudent.studentName,
                    nextStudent.resourceID,
                    nextStudent.reservationDate,
                    created
                );


            // Automatic assignment worked
            if (result == RES_SUCCESS) {

                cout << "Waiting student automatically "
                     << "assigned reservation."
                     << endl;

                cout << "Student: "
                     << nextStudent.studentName
                     << endl;

                cout << "Reservation ID: "
                     << created.GetReservationID()
                     << endl;
            }

            // Something prevented the automatic
            // reservation from being created
            else {

                cout << "Could not automatically "
                     << "assign reservation: "
                     << GetResultMessage(result)
                     << endl;


                // Do not lose the student.
                // Put them back into the queue.
                waitingLists.Enqueue(
                    nextStudent.studentID,
                    nextStudent.studentName,
                    nextStudent.resourceID,
                    nextStudent.reservationDate
                );
            }
        }
    }

    else {

        cout << "No active reservation found with ID "
             << reservationID
             << "."
             << endl;
    }
}


// ---------------------------------------------------------
// OPTION 4
// View Waiting List
// ---------------------------------------------------------

void viewWaitingLists(
    const WaitingList& waitingLists
) {

    cout << endl
         << "--- View Waiting Lists ---"
         << endl;


    waitingLists.Display();
}


// ---------------------------------------------------------
// OPTION 5
// Undo Cancellation
// ---------------------------------------------------------

void undoCancellation(
    ReservationManager& reservations,
    CancellationHistory& cancellationHistory
) {

    cout << endl
         << "--- Undo Cancellation ---"
         << endl;


    Reservation restored;


    // Pop the most recent cancellation
    if (!cancellationHistory.Pop(restored)) {

        cout << "Cancellation history is empty."
             << endl;

        return;
    }


    // Try to restore the reservation
    ReservationResult result =
        reservations.RestoreReservation(
            restored
        );


    if (result == RES_SUCCESS) {

        cout << "Reservation Restored Successfully."
             << endl;

        cout << "Reservation ID: "
             << restored.GetReservationID()
             << endl;
    }

    else {

        cout << "Could not restore: "
             << GetResultMessage(result)
             << endl;


        // Restoration failed.
        // Put it back on top of the stack
        // so the history is not lost.

        cancellationHistory.Push(
            restored
        );
    }
}


// ---------------------------------------------------------
// OPTION 6
// Search Reservations
// ---------------------------------------------------------

void searchReservations(
    ReservationManager& reservations
) {

    cout << endl
         << "--- Search Reservations ---"
         << endl;

    cout << "1. View all active reservations"
         << endl;

    cout << "2. Search by Reservation ID"
         << endl;

    cout << "3. Search by Student ID"
         << endl;

    cout << "4. Search by Student Name"
         << endl;

    cout << "5. Search by Resource ID"
         << endl;

    cout << "6. Search by Date (MM/DD/YYYY)"
         << endl;

    cout << "0. Back"
         << endl;


    int choice =
        readNumber("Enter Choice: ");


    switch (choice) {

        case 0:

            return;


        case 1:

            reservations.DisplayAll();

            break;


        case 2:

            reservations.SearchByReservationID(
                readNumber(
                    "Reservation ID: "
                )
            );

            break;


        case 3:

            reservations.SearchByStudentID(
                readNumber(
                    "Student ID: "
                )
            );

            break;


        case 4:

            reservations.SearchByStudentName(
                readText(
                    "Student Name (or part of it): "
                )
            );

            break;


        case 5:

            reservations.SearchByResourceID(
                readText(
                    "Resource ID: "
                )
            );

            break;


        case 6:

            reservations.SearchByDate(
                readText(
                    "Date (MM/DD/YYYY): "
                )
            );

            break;


        default:

            cout << "Invalid choice. "
                 << "Please enter a number "
                 << "from the menu."
                 << endl;
    }
}


// ---------------------------------------------------------
// OPTION 7
// Sort Resources
// ---------------------------------------------------------

void sortResources(
    ResourceManager& resources
) {

    cout << endl
         << "--- Sort Resources ---"
         << endl;


    cout << "1. Resource ID"
         << endl;

    cout << "2. Resource Name"
         << endl;

    cout << "3. Resource Type"
         << endl;

    cout << "4. Availability Status"
         << endl;

    cout << "0. Back"
         << endl;


    int choice =
        readNumber("Sort by: ");


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

            cout << "Invalid choice. "
                 << "Please enter a number "
                 << "from the menu."
                 << endl;

            return;
    }


    cout << "Resources sorted."
         << endl;


    resources.DisplayAll();
}


// ---------------------------------------------------------
// OPTION 8
// Generate Report
// ---------------------------------------------------------

void generateReport() {

    // Report Generator integration
    // will eventually go here.

    cout << "Generate Report is not connected yet "
         << "(Report Generator part)."
         << endl;
}


// ---------------------------------------------------------
// MAIN
// ---------------------------------------------------------

int main() {


    // =============================================
    // MAIN PROJECT OBJECTS
    // =============================================

    ResourceManager resources;


    ReservationManager reservations(
        &resources
    );


    // =============================================
    // PROMISE'S DATA STRUCTURES
    // =============================================

    // Stack
    CancellationHistory cancellationHistory;


    // Queue
    WaitingList waitingLists;


    // =============================================
    // LOAD RESOURCES
    // =============================================

    // Resources must be loaded first because
    // reservations use them.

    int resourceCount =
        resources.LoadFromFile(
            "data/resources.txt"
        );


    if (resourceCount == -1) {

        cout << "Error: could not open "
             << "data/resources.txt"
             << endl;

        cout << "Run the program from "
             << "the Project1 folder."
             << endl;

        return 1;
    }


    cout << "Loaded "
         << resourceCount
         << " resources."
         << endl;


    // =============================================
    // LOAD RESERVATIONS
    // =============================================

    int reservationCount =
        reservations.LoadFromFile(
            "data/reservations.txt"
        );


    if (reservationCount == -1) {

        cout << "Warning: could not open "
             << "data/reservations.txt. "
             << "Starting with no reservations."
             << endl;
    }

    else {

        cout << "Loaded "
             << reservationCount
             << " reservations."
             << endl;
    }


    // =============================================
    // MAIN MENU LOOP
    // =============================================

    int choice = 0;


    do {

        printMenu();


        choice =
            readNumber("Enter Choice: ");


        switch (choice) {


            // Resource Management
            case 1:

                viewResources(
                    resources
                );

                break;


            // Reservation + Waiting List
            case 2:

                createReservation(
                    reservations,
                    waitingLists
                );

                break;


            // Cancellation History + Waiting List
            case 3:

                cancelReservation(
                    reservations,
                    cancellationHistory,
                    waitingLists
                );

                break;


            // Waiting List
            case 4:

                viewWaitingLists(
                    waitingLists
                );

                break;


            // Cancellation History
            case 5:

                undoCancellation(
                    reservations,
                    cancellationHistory
                );

                break;


            // Reservation Management
            case 6:

                searchReservations(
                    reservations
                );

                break;


            // Resource Management
            case 7:

                sortResources(
                    resources
                );

                break;


            // Report Generator
            case 8:

                generateReport();

                break;


            // Exit
            case 9:

                cout << "Goodbye!"
                     << endl;

                break;


            default:

                cout << "Invalid choice. "
                     << "Please enter a number "
                     << "from 1 to 9."
                     << endl;
        }


    } while (choice != 9);


    return 0;
}
