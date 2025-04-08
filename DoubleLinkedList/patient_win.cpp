#pragma once

#include "resource.h"
#include "utils.h"
#include "data.cpp"

inline void LoadPatientsIntoListBox(HWND hwndListBox, PatientNode* head) {
    SendMessage(hwndListBox, LB_RESETCONTENT, 0, 0); // Clear existing content
    
    PatientNode* current = head;
    while (current != nullptr) {
        std::wstring displayText = StringToWString(current->lname1);
        SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)displayText.c_str());
        current = current->next;
    }
}

inline LRESULT CALLBACK WindowProcPatient(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        std::string id, lname1, lname2, fname, email, phone, gender, age;
        switch (LOWORD(wParam)) {
        case IDC_BTN_ADD:
            HWND hwndBox;
            id = ReadTextBox(hwnd, IDC_EDIT_ID);
            lname1  = ReadTextBox(hwnd, IDC_EDIT_LNAME1);
            lname2 = ReadTextBox(hwnd, IDC_EDIT_LNAME2);
            fname = ReadTextBox(hwnd, IDC_EDIT_FNAME);
            email = ReadTextBox(hwnd, IDC_EDIT_EMAIL);
            phone = ReadTextBox(hwnd, IDC_EDIT_PHONE);
            gender = ReadTextBox(hwnd, IDC_EDIT_GENDER);
            age = ReadTextBox(hwnd, IDC_EDIT_AGE);
            patient_list.addPatient(id, fname, lname1, lname2, email, phone, gender, age, "Treviño");
            patient_list.saveToFile();
            hwndBox = GetDlgItem(hwnd, IDC_LISTBOX_PATIENTS);
            LoadPatientsIntoListBox(hwndBox, patient_list.head);
            MessageBox(hwnd, L"Paciente registrado exitosamente!", L"Info", MB_OK);
            break;
        case IDC_BTN_EDIT:
            medic_list.printList();
            MessageBox(hwnd, L"Paciente editado!", L"Acción", MB_OK);
            break;
        case IDC_BTN_DELETE:
            MessageBox(hwnd, L"Paciente elimninado exitosamente!", L"Acción", MB_OK);
            break;
        }
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

inline HWND CreatePatientWindow(HINSTANCE hInstance) {
    const wchar_t CLASS_NAME[] = L"PatientApp";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProcPatient;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Pacientes",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 700, 500,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) return hwnd;

    // Listbox
    CreateWindow(L"STATIC", L"Pacientes", WS_VISIBLE | WS_CHILD,
        20, 20, 160, 20, hwnd, NULL, hInstance, NULL);

    CreateWindow(L"LISTBOX", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
        20, 45, 160, 360, hwnd, (HMENU)IDC_LISTBOX_PATIENTS, hInstance, NULL);

    // Labels & Edit Boxes
    int labelX = 200, editX = 320, y = 40, height = 20, spacing = 35, width = 200;

    CreateWindow(L"STATIC", L"ID", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_ID, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Apellido Paterno", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_LNAME1, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Apellido Materno", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_LNAME2, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Nombre(s)", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_FNAME, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Correo", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_EMAIL, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Teléfono", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_PHONE, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Género", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_SPEC, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Edad", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_SPEC, hInstance, NULL);

    y += spacing;
    // Buttons
    CreateWindow(L"BUTTON", L"Agregar", WS_VISIBLE | WS_CHILD, labelX, y, 110, 25, hwnd, (HMENU)IDC_BTN_ADD, hInstance, NULL);
    labelX += 140;
    CreateWindow(L"BUTTON", L"Editar", WS_VISIBLE | WS_CHILD, labelX, y, 110, 25, hwnd, (HMENU)IDC_BTN_EDIT, hInstance, NULL);
    labelX += 140;
    CreateWindow(L"BUTTON", L"Eliminar", WS_VISIBLE | WS_CHILD, labelX, y, 110, 25, hwnd, (HMENU)IDC_BTN_DELETE, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    return hwnd;
}

inline void RegisterPatientWindow(HINSTANCE hInstance) {

    WNDCLASS wc = {};

    if (GetClassInfo(hInst, L"PatientWindow", &wc)) {
        MessageBox(nullptr, L"Class already registered.", L"Error", MB_OK);
        return;
    }

    wc.lpfnWndProc = WindowProcPatient;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName =L"PatientWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);
}
