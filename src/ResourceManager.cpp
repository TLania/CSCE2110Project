// ResourceManager.cpp
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;

// Helper function, makes a lowercase copy of a string so searches and sorting ignore upper/lower case
string toLowerCase(string text) {
    for (unsigned int i = 0; i < text.size(); ++i) {
        text.at(i) = tolower(text.at(i));
    }
    return text;
}

// Comparison functions used by sort()
bool CompareByID(const Resource& a, const Resource& b) {
    return a.GetID() < b.GetID();
}

bool CompareByName(const Resource& a, const Resource& b) {
    string nameA = toLowerCase(a.GetName());
    string nameB = toLowerCase(b.GetName());
    if (nameA == nameB) {
        return a.GetID() < b.GetID();
    }
    return nameA < nameB;
}

bool CompareByType(const Resource& a, const Resource& b) {
    string typeA = toLowerCase(a.GetType());
    string typeB = toLowerCase(b.GetType());
    if (typeA == typeB) {
        return a.GetID() < b.GetID();
    }
    return typeA < typeB;
}

bool CompareByStatus(const Resource& a, const Resource& b) {
    if (a.GetStatus() == b.GetStatus()) {
        return a.GetID() < b.GetID();
    }
    return a.GetStatus() < b.GetStatus();
}

// Forward declaration so mergeSort can call merge 
void merge(vector<Resource>& arr, int left, int mid, int right, bool (*compare)(const Resource&, const Resource&));

// Recursive Merge Sort
void mergeSort(vector<Resource>& arr, int left, int right, bool (*compare)(const Resource&, const Resource&)) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, compare);       // Sort left
    mergeSort(arr, mid + 1, right, compare);  // Sort right
    merge(arr, left, mid, right, compare);    // Merge sorted halves
}

void merge(vector<Resource>& arr, int left, int mid, int right, bool (*compare)(const Resource&, const Resource&)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Resource> leftArr(n1);
    vector<Resource> rightArr(n2);

    for (int i = 0; i < n1; i++)        // Copy into temporary arrays
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {          // Merge the temporary arrays back
        if (compare(leftArr[i], rightArr[j])) { arr[k] = leftArr[i]; i++; }
        else                                   { arr[k] = rightArr[j]; j++; }
        k++;
    }
    while (i < n1) { arr[k] = leftArr[i]; i++; k++; }   // Copy any remaining left elements
    while (j < n2) { arr[k] = rightArr[j]; j++; k++; }  // Copy any remaining right elements
}

// Load resources from a file. Each line looks like: R101|Study Room 101|Study Room|Available, from TXT file.
int ResourceManager::LoadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        return -1; // file not opened
    }

    resources.clear();
    string line;

    while (getline(inFile, line)) {
        // Remove the extra '\r' that a Windows text file leaves
        if (!line.empty() && line.at(line.size() - 1) == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue; // skip blank lines
        }

        // Split the line at each '|'
        stringstream lineStream(line);
        string id, name, type, status;
        getline(lineStream, id, '|');
        getline(lineStream, name, '|');
        getline(lineStream, type, '|');
        getline(lineStream, status);

        resources.push_back(Resource(id, name, type, status));
    }

    inFile.close();
    return resources.size();

}

// Accessors
int ResourceManager::GetSize() const {
    return resources.size();
}

Resource ResourceManager::GetResourceAt(int index) const {
    return resources.at(index);
}

// Display all resource
void ResourceManager::DisplayAll() const {
    if (resources.empty()) {
        cout << "No resources loaded." << endl;
        return;
    }
    for (const Resource& item : resources) {
        item.Display();
    }
    cout << "Total resources: " << resources.size() << endl;
}

// Find a resource by its exact ID
// Returns its position in the vector
int ResourceManager::FindByID(const string& id) const {
    for (unsigned int i = 0; i < resources.size(); ++i) {
        if (toLowerCase(resources.at(i).GetID()) == toLowerCase(id)) {
            return i;
        }
    }
    return -1;
}

void ResourceManager::SearchByID(const string& id) const {
    int index = FindByID(id);
    if (index == -1) {
        cout << "No resource found with ID " << id << "." << endl;
    } else {
        resources.at(index).Display();
    }
}

// Name and type searches match any part of the text,string::npos means "not found"
void ResourceManager::SearchByName(const string& keyword) const {
    string lowerKeyword = toLowerCase(keyword);
    int matches = 0;

    for (const Resource& item : resources) {
        if (toLowerCase(item.GetName()).find(lowerKeyword) != string::npos) {
            item.Display();
            matches++;
        }
    }
    if (matches == 0) {
        cout << "No resources found." << endl;
    } else {
        cout << matches << " resource(s) found." << endl;
    }
}

void ResourceManager::SearchByType(const string& keyword) const {
    string lowerKeyword = toLowerCase(keyword);
    int matches = 0;

    for (const Resource& item : resources) {
        if (toLowerCase(item.GetType()).find(lowerKeyword) != string::npos) {
            item.Display();
            matches++;
        }
    }
    if (matches == 0) {
        cout << "No resources found." << endl;
    } else {
        cout << matches << " resource(s) found." << endl;
    }
}

// Status must match exactly
void ResourceManager::SearchByStatus(const string& status) const {
    string lowerStatus = toLowerCase(status);
    int matches = 0;

    for (const Resource& item : resources) {
        if (toLowerCase(item.GetStatus()) == lowerStatus) {
            item.Display();
            matches++;
        }
    }
    if (matches == 0) {
        cout << "No resources found." << endl;
    } else {
        cout << matches << " resource(s) found." << endl;
    }
}

// Sort using mergeSort() and the comparison functions
void ResourceManager::SortByID() {
    int size = resources.size();
    mergeSort(resources, 0, size - 1, CompareByID);
}

void ResourceManager::SortByName() {
    int size = resources.size();
    mergeSort(resources, 0, size - 1, CompareByName);
}

void ResourceManager::SortByType() {
    int size = resources.size();
    mergeSort(resources, 0, size - 1, CompareByType);
}

void ResourceManager::SortByStatus() {
    int size = resources.size();
    mergeSort(resources, 0, size - 1, CompareByStatus);
}