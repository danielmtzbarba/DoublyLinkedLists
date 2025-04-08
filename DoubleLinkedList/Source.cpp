#pragma once

#include "medic_win.cpp"
#include "patient_win.cpp"
#include "login_win.cpp"

MedicList medic_list;
PatientList patient_list;
HINSTANCE hInst;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    hInst = hInstance;
    medic_list.loadFromFile();
    patient_list.loadFromFile();

    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WindowProcLogin);
    return 0;

    //HWND app = CreatePatientWindow(hInstance);
    //HWND hListBox = GetDlgItem(app, IDC_LISTBOX_PATIENTS);
    //LoadPatientsIntoListBox(hListBox, patient_list.head);

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
    list.loadFromFile();
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
