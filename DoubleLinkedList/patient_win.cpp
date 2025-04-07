#pragma once

#include "utils.h"

inline LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BTN_ADD:
            MessageBox(hwnd, L"Agregar paciente", L"Acción", MB_OK);
            break;
        case IDC_BTN_EDIT:
            MessageBox(hwnd, L"Editar paciente", L"Acción", MB_OK);
            break;
        case IDC_BTN_SEARCH_EMAIL:
            MessageBox(hwnd, L"Buscar por correo", L"Acción", MB_OK);
            break;
        case IDC_BTN_SAVE:
            MessageBox(hwnd, L"Guardado", L"Acción", MB_OK);
            break;
        case IDC_BTN_CANCEL:
            MessageBox(hwnd, L"Cancelado", L"Acción", MB_OK);
            break;
        case IDC_BTN_DELETE:
            MessageBox(hwnd, L"Eliminar paciente", L"Acción", MB_OK);
            break;
        case IDC_BTN_SEARCH_NAME:
            MessageBox(hwnd, L"Buscar por nombre", L"Acción", MB_OK);
            break;
        }
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

inline void CreatePatientWindow(HINSTANCE hInstance) {
    const wchar_t CLASS_NAME[] = L"PatientApp";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"PACIENTES",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 700, 500,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) return;

    // Listbox
    CreateWindow(L"STATIC", L"LISTA DE PACIENTES", WS_VISIBLE | WS_CHILD,
        20, 20, 160, 20, hwnd, NULL, hInstance, NULL);

    CreateWindow(L"LISTBOX", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
        20, 45, 160, 360, hwnd, (HMENU)IDC_LISTBOX_PATIENTS, hInstance, NULL);

    // Labels & Edit Boxes
    int labelX = 200, editX = 320, y = 40, height = 20, spacing = 35, width = 200;

    CreateWindow(L"STATIC", L"Nombre Completo", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_NAME, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Correo", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_EMAIL, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Género", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_GENDER, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Teléfono", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_PHONE, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Número", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_NUMBER, hInstance, NULL);

    y += spacing;
    CreateWindow(L"STATIC", L"Edad", WS_VISIBLE | WS_CHILD, labelX, y, 110, height, hwnd, NULL, hInstance, NULL);
    CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, editX, y, width, height, hwnd, (HMENU)IDC_EDIT_AGE, hInstance, NULL);

    // Buttons
    int btnY = y + 40;
    CreateWindow(L"BUTTON", L"editar pacientes", WS_VISIBLE | WS_CHILD, 200, btnY, 120, 25, hwnd, (HMENU)IDC_BTN_EDIT, hInstance, NULL);
    CreateWindow(L"BUTTON", L"agregar pacientes", WS_VISIBLE | WS_CHILD, 340, btnY, 130, 25, hwnd, (HMENU)IDC_BTN_ADD, hInstance, NULL);
    CreateWindow(L"BUTTON", L"Buscar por Correo", WS_VISIBLE | WS_CHILD, 480, btnY, 140, 25, hwnd, (HMENU)IDC_BTN_SEARCH_EMAIL, hInstance, NULL);

    btnY += 35;
    CreateWindow(L"BUTTON", L"Guardar", WS_VISIBLE | WS_CHILD, 200, btnY, 80, 25, hwnd, (HMENU)IDC_BTN_SAVE, hInstance, NULL);
    CreateWindow(L"BUTTON", L"Cancelar", WS_VISIBLE | WS_CHILD, 300, btnY, 80, 25, hwnd, (HMENU)IDC_BTN_CANCEL, hInstance, NULL);

    btnY += 35;
    CreateWindow(L"BUTTON", L"Eliminar pacientes", WS_VISIBLE | WS_CHILD, 200, btnY, 130, 25, hwnd, (HMENU)IDC_BTN_DELETE, hInstance, NULL);
    CreateWindow(L"BUTTON", L"Buscar por Nombre", WS_VISIBLE | WS_CHILD, 340, btnY, 140, 25, hwnd, (HMENU)IDC_BTN_SEARCH_NAME, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
}


