// Resource.cpp - Class Definition
#include "Resource.h"
#include <iostream>
using namespace std;

// Private helper: only "Available" or "Unavailable"
void Resource::validateStatus(const string& status) {
    if (status == "Available" || status == "Unavailable") {
        availabilityStatus = status;
    } else {
        cout << "Invalid status, setting to Unavailable by default." << endl;
        availabilityStatus = "Unavailable";
    }
}

// Default Constructor
Resource::Resource() : resourceID("none"), resourceName("none"), resourceType("none"),
    availabilityStatus("Unavailable") {}

// Overloaded Constructor
Resource::Resource(const string& id, const string& name, const string& type, const string& status)
    : resourceID(id), resourceName(name), resourceType(type) {
    validateStatus(status);
}

// Accessors
string Resource::GetID() const {
    return resourceID;
}

string Resource::GetName() const {
    return resourceName;
}

string Resource::GetType() const {
    return resourceType;
}

string Resource::GetStatus() const {
    return availabilityStatus;
}

bool Resource::IsAvailable() const {
    return availabilityStatus == "Available";
}

// Mutators
void Resource::SetID(const string& id) {
    resourceID = id;
}

void Resource::SetName(const string& name) {
    resourceName = name;
}

void Resource::SetType(const string& type) {
    resourceType = type;
}

void Resource::SetStatus(const string& status) {
    validateStatus(status);
}

// Display one resource on a single line
void Resource::Display() const {
    cout << "ID: " << resourceID << " | "
         << "Name: " << resourceName << " | "
         << "Type: " << resourceType << " | "
         << "Status: " << availabilityStatus << endl;
}
