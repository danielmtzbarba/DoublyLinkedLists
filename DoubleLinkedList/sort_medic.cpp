#include "data.cpp"

inline void heapify(std::vector<MedicNode*>& heap, int n, int i, bool maxHeap = true, bool sortByLname1 = false) {
    int largest = i;  // For max heap
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If left child is larger (for max heap)
    if (left < n &&
        (maxHeap ?
            (sortByLname1 ? heap[left]->lname1 > heap[largest]->lname1 : heap[left]->id > heap[largest]->id)
            : (sortByLname1 ? heap[left]->lname1 < heap[largest]->lname1 : heap[left]->id < heap[largest]->id)))
        largest = left;

    // If right child is larger
    if (right < n &&
        (maxHeap ?
            (sortByLname1 ? heap[right]->lname1 > heap[largest]->lname1 : heap[right]->id > heap[largest]->id)
            : (sortByLname1 ? heap[right]->lname1 < heap[largest]->lname1 : heap[right]->id < heap[largest]->id)))
        largest = right;

    // If largest is not root
    if (largest != i) {
        std::swap(heap[i], heap[largest]);

        // Recursively heapify the affected sub-tree
        heapify(heap, n, largest, maxHeap, sortByLname1);
    }
}

inline void buildHeap(std::vector<MedicNode*>& heap, bool maxHeap = true, bool sortByLname1 = false) {
    int n = heap.size();
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i, maxHeap);
    }
}

inline void heapSort(std::vector<MedicNode*>& heap, bool maxHeap = true, bool sortByLname1 = false) {
    int n = heap.size();

    buildHeap(heap, maxHeap, sortByLname1);

    // One by one extract elements from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to the end
        std::swap(heap[0], heap[i]);

        // Call heapify on the reduced heap
        heapify(heap, i, 0, maxHeap, sortByLname1);
    }
}

inline std::vector<MedicNode*> listToArray() {
    std::vector<MedicNode*> nodes;
    MedicNode* current = medic_list.head;
    while (current) {
        nodes.push_back(current);
        current = current->next;
    }
    return nodes;
}

inline void rebuildListFromArray(const std::vector<MedicNode*>& sortedNodes) {
    medic_list.clear();
    for (MedicNode* node : sortedNodes) {
        medic_list.append(node);
    }
}

inline void sortMedicList(MedicList& medicList, bool maxHeap = true, bool sortByLname1 = false) {
    std::vector<MedicNode*> nodes = listToArray();
    heapSort(nodes, maxHeap, sortByLname1);
    rebuildListFromArray(nodes);
}
