# CSCE2110 Project - Campus Resource Reservation System

The main objective is to replicate the core functionality of the UNT Campus Resource Reservation System using GitHub to collaborate with each other as a team.

The program is a menu-driven C++ command-line application. Students can reserve campus resources (study rooms, laptops, calculators, lab equipment, and tutoring appointments), join waiting lists for resources that are taken, cancel reservations, and undo the most recent cancellation.


GitHub repository: https://github.com/TLania/CSCE2110Project

# Team
 Member | Components 
 Taylor Lania | Linked List Implementation, Complexity Analysis
 Lance Manuel| Resource Management, Reservation Management
 Nnamdi Emenike | Cancellation History, Waiting List Management
Each member developed on a feature branch (Linked-Lists, Resource-Management, Reservation-Management, Cancellation-History, Waiting-List-Management) and merged into main.

# Build and Run

Requires a C++ compiler. Run these commands from the project1 folder, the folder that contains `include/`, `src/`, `data/`, and `Working LinkedList/`:
Line1:
g++ -Iinclude -o go src/*.cpp
Line2:
./go

## The program opens data/resources.txt and data/reservations.txt , so it must be started from the project folder. If data/resources.txt cannot be opened, the program prints an error and exits.

# Menu

===== Campus Resource Reservation System =====
1. View Resources
2. Create Reservation
3. Cancel Reservation
4. View Waiting Lists
5. Undo Cancellation
6. Search Reservations
7. Sort Resources
8. Generate Report
9. Exit

 Options | What it does
 1. View Resources | Displays all resources, or searches by Resource ID, name, type, or availability.
 2. Create Reservation | Asks for Student ID, name, Resource ID, and date. If the resource is unavailable or already booked on that date, the student can join the waiting list.
 3. Cancel Reservation | Removes a reservation by ID, records it in the cancellation history, and automatically gives the freed slot to the first student waiting for that resource and date.
 4. View Waiting Lists | Displays every student currently waiting.
 5. Undo Cancellation | Restores the most recently cancelled reservation.
 6. Search Reservations | Views all active reservations, or searches by reservation ID, student ID, student name, resource ID, or date.
 7. Sort Resources | Sorts the resources by ID, name, type, or availability.
 8. Generate Report | Placeholder.
 9. Exit | Ends the program. 

# Input Files

Both files use one record per line with fields separated by `|`.

FILE1: data/resources.txt
ResourceID|ResourceName|ResourceType|Available or Unavailable
R101|Study Room 101|Study Room|Available

FILE2: data/reservations.txt
ReservationID|StudentID|StudentName|ResourceID|MM/DD/YYYY
301|1001|Alice Smith|R101|09/15/2026

Blank lines are skipped, and Windows line endings are handled. The loaders expect the files to be well formatted.

# Project Structure

include/                     Header files
src/                         Source files (main.cpp holds main())
data/                        resources.txt, reservations.txt


File(s) | Purpose

 Resource, ResourceManager | A resource record (ID, name, type, status) and the manager that stores them in a `vector`, loads the file, and displays, searches, and sorts them.
 Reservation, ReservationManager | A reservation record (reservation ID, student ID, student name, resource ID, date) and the manager that loads, creates, cancels, restores, and searches reservations.
 ReservationList | Singly linked list that stores the active reservations: insert, remove, traverse, display.
 WaitingList | Queue (front and rear pointers) of waiting requests. First come, first served.
 CancellationHistory | Stack of cancelled reservations. Last in, first out.
 main.cpp | Menu and the code that connects all of the components.

# Data Structures

Structure | Used for | Where

Linked list | Active reservations | ReservationList
 Queue | Waiting lists | WaitingList
 Stack | Cancellation history and undo | CancellationHistory 
 Vector | Resource inventory |  ResourceManager

# Reservation Rules

A new reservation is accepted only when these are true:

- The Resource ID exists in the resource list (the search ignores upper/lower case, so r102 works).
- The resource is Available.
- The date is a real calendar date written as MM/DD/YYYY.
- The resource is not already reserved on that date.
- The Student ID is a positive whole number and the name is not empty.

Other behavior:

- Reservation IDs are created automatically, continue after the highest ID in the file, and are never reused.
- A resource marked Unavailable can still have reservations in the input file. Unavailable only stops new reservations.
- A waiting student is only assigned when a reservation for the same resource and date is cancelled.
- Undo fails, with a message, if the cancelled slot was taken by someone else in the meantime.

# Sample Run

Enter Choice: 2
Student ID: 1001
Student Name: Alice Smith
Resource ID: R102
Reservation Date (MM/DD/YYYY): 09/20/2026
Reservation Created Successfully.
Reservation ID: 321

Enter Choice: 3
Reservation ID: 301
Reservation Cancelled.
Added to cancellation history.

Enter Choice: 5
Reservation Restored Successfully.
Reservation ID: 301

# Testing

Expectation | How to see it
 File input works | Start the program: Loaded 20 resources. and Loaded 20 reservations., then choose 1, then 1 to list the resources.
 Reservations can be created | Option 2 with Student ID 1001, Alice Smith, R102, 09/30/2026.
 Reservations can be cancelled | Option 3 with Reservation ID 301.
 Waiting lists work | Option 2 for a slot that is taken (for example R101 on 09/15/2026), answer `y`, then use option 4. Cancel reservation 301 with option 3 and the waiting student is assigned.
 Undo works | Cancel a reservation with option 3, then use option 5.
 Invalid input is handled | Try an unknown resource (EX:R999), an unavailable resource, a bad date, letters where a number is expected, or a menu choice such as 10.

# Known Limitations

- Changes made while the program runs are not written back to the data files.
- Option 8 (Generate Report) is not implemented.
- Dates must be typed exactly as MM/DD/YYYY.
