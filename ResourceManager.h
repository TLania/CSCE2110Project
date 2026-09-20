// ResourceManager.h
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "Resource.h"
using namespace std;

class ResourceManager {
private:
    vector<Resource> resources; // Resource inventory

public:
    // File input
    int LoadFromFile(const string& filename);

    // Accessors
    int GetSize() const;
    Resource GetResourceAt(int index) const;

    // Display
    void DisplayAll() const;

    // Search, FindByID returns the index in the vector
    int FindByID(const string& id) const;
    void SearchByID(const string& id) const;
    void SearchByName(const string& keyword) const;
    void SearchByType(const string& keyword) const;
    void SearchByStatus(const string& status) const;

    // Sort
    void SortByID();
    void SortByName();
    void SortByType();
    void SortByStatus();
};

#endif // RESOURCE_MANAGER_H
