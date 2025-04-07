#pragma once

#include "medic_list.cpp"
#include "patient_win.cpp"

using namespace std;

// Define button IDs
#define ID_BTN_SUBMIT 1
#define ID_BTN_EXIT   2

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    CreatePatientWindow(hInstance);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

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
