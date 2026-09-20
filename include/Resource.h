// Resource.h - Class Declaration
#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <string>
using namespace std;

class Resource {
private:
    string resourceID;
    string resourceName;
    string resourceType;
    string availabilityStatus; // "Available" or "Unavailable"

    // Private helper function
    void validateStatus(const string& status);

public:
    // Constructors
    Resource();
    Resource(const string& id, const string& name, const string& type, const string& status);

    // Accessors (Getters)
    string GetID() const;
    string GetName() const;
    string GetType() const;
    string GetStatus() const;
    bool IsAvailable() const;

    // Mutators (Setters)
    void SetID(const string& id);
    void SetName(const string& name);
    void SetType(const string& type);
    void SetStatus(const string& status);

    // Display method
    void Display() const;
};

#endif // RESOURCE_H
