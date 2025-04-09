#pragma once
#include "data.cpp"
HINSTANCE hInst;

#include "medic_win.cpp"
#include "patient_win.cpp"
#include "login_win.cpp"

MedicList medic_list;
PatientList patient_list;
UserList user_list;
SpecList spec_list;
ConsultoryList consultory_list;
AppointmentList appointment_list;

void GenerateData() {
    medic_list.clear();
    medic_list.saveToFile();
    medic_list.addMedic("001", "Juan", "Pérez", "García", "juanperez@example.com", "555-1234", "Cardiólogo", "juanperez123");
    medic_list.addMedic("002", "María", "González", "Sánchez", "mariagonzalez@example.com", "555-5678", "Pediatra", "mariagonzalez456");
    medic_list.addMedic("003", "Carlos", "Rodríguez", "Martínez", "carlosrodriguez@example.com", "555-2345", "Cirujano", "carlosrod123");
    medic_list.addMedic("004", "Laura", "Martínez", "López", "lauramartinez@example.com", "555-6789", "Dermatóloga", "lauramartinez789");
    medic_list.addMedic("005", "Andrés", "López", "Ramírez", "andreslopez@example.com", "555-3456", "Neurólogo", "andreslopez321");
    medic_list.addMedic("006", "Sofía", "Sánchez", "Torres", "sofisanchez@example.com", "555-8901", "Ginecóloga", "sofisanchez654");
    medic_list.addMedic("007", "David", "Fernández", "Morales", "davidfernandez@example.com", "555-4567", "Endocrinólogo", "davidfernandez987");
    medic_list.addMedic("008", "Elena", "García", "Vázquez", "elenagarcia@example.com", "555-5670", "Oftalmóloga", "elenagarcia432");
    medic_list.addMedic("009", "Francisco", "Díaz", "Pérez", "franciscodiaz@example.com", "555-6780", "Oncólogo", "franciscodiaz111");
    medic_list.addMedic("010", "Isabel", "Álvarez", "Jiménez", "isabelalvarez@example.com", "555-8902", "Urgencióloga", "isabelalvarez222");
    medic_list.saveToFile();
    medic_list.loadFromFile();
    return;
}

void QuickSortMedic() {
    std::ofstream log("log.txt", std::ios::app);
    log << "Original list: " << "\n";
    medic_list.printList();
    medic_list.quickSort(medic_list.head, medic_list.tail);
    log << "Sorted list: " << "\n";
    medic_list.printList();

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    hInst = hInstance;
    GenerateData();
    user_list.loadFromFile();
    patient_list.loadFromFile();
    spec_list.loadFromFile();
    consultory_list.loadFromFile();
    appointment_list.loadFromFile();
    
    QuickSortMedic();

    RegisterMedicWindow(hInst);
    RegisterPatientWindow(hInst);

    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WindowProcLogin);
    return 0;


}


