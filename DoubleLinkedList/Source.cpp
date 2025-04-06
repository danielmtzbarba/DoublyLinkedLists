#include <iostream>
#include "medic_list.cpp"

using namespace std;


int main() {
    MedicList list;

    // Add medics
    //list.addMedic("001", "Alice", "Lopez", "Garcia", "alice@example.com", "555-1234", "Cardiology", "0");
    //list.addMedic("002", "Bob", "Martinez", "Ramirez", "bob@example.com", "555-5678", "Neurology", "0");
    //list.addMedic("003", "Carol", "Fernandez", "Rojas", "carol@example.com", "555-9012", "Pediatrics", "0");
    //list.saveToFile("medics.bin");
    list.loadFromFile("medics.bin");
    std::cout << "Initial list:\n";
    list.printList();

    // Update Bob
    std::cout << "\nUpdating Bob (ID: 002)...\n";
    bool updated = list.updateMedicById("002", "Bobby", "Martinez", "Lopez", "bobby@example.com", "555-0000", "Oncology", "0");
    if (!updated) std::cout << "Medic not found!\n";

    // Remove Carol
    std::cout << "\nRemoving Carol (ID: 003)...\n";
    bool removed = list.removeMedicById("003");
    if (!removed) std::cout << "Medic not found!\n";

    std::cout << "\nFinal list:\n";
    list.printList();

    return 0;
}
