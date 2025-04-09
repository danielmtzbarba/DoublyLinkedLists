#include "data.cpp"
#include <algorithm>

// Binary search on vector of MedicNode*
MedicNode* binarySearch(const std::vector<MedicNode*>& nodes, const std::string& target) {
    int left = 0;
    int right = nodes.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nodes[mid]->lname1 == target) {
            return nodes[mid]; // Found
        }
        else if (nodes[mid]->lname1 < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return nullptr; // Not found
}

MedicNode* searchMedicByLname1(const std::string& lname1) {
    // Step 1: Use QuickSort based on `lname1`
    medic_list.quickSort(medic_list.head, medic_list.tail);

    // Step 2: Convert list to vector
    std::vector<MedicNode*> nodes = medic_list.extractToVector();

    // Step 3: Perform binary search on the sorted vector
    return binarySearch(nodes, lname1);
}
