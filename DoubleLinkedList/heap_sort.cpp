#include "data.cpp"

inline void heapify(std::vector<std::pair<std::string, MedicNode*>>& arr, int size) {
	int n = arr.size();
	int mid, node;
	for (int i = 0; i <= size; i++) {
		node = i;
		mid = (node == 0) ? 0 : node / 2;
		while (mid >= 0 && node != 0) {
			if (arr[mid].first < arr[node].first)
				std::swap(arr[mid], arr[node]);

			node = mid;
			mid = (node == 0) ? 0 : node / 2;
		}
	}
}

inline std::vector<std::pair<std::string, MedicNode*>> heapSort(std::vector<std::pair<std::string, MedicNode*>> arr, int arrSize) {
	for (int i = arrSize - 1; i >= 0; i--) {
		heapify(arr, i);
		std::swap(arr[0], arr[i]);
	}
	return arr;
}
inline MedicList sortMedicsByName() {
	// Step 1: Extract and pair lname1 with full node
	std::vector<std::pair<std::string, MedicNode*>> sortable;
	MedicNode* current = medic_list.head;

	while (current) {
		sortable.push_back({ current->lname1, current });
		current = current->next;
	}

	// Step 2: Sort using heapsort
	sortable = heapSort(sortable, sortable.size());

	// Step 3: Rebuild the sorted list
	MedicList sorted_list;
	for (const auto& pair : sortable) {
		MedicNode* node = pair.second;
		sorted_list.addMedic(
			node->id,
			node->fname,
			node->lname1,
			node->lname2,
			node->email,
			node->phone,
			node->spec,
			node->userid
		);
		return sorted_list;
	}

}
