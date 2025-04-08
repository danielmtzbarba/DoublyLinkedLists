#include "utils.h"
#include "data.cpp"
#include "resource.h"

inline INT_PTR CALLBACK WindowProcMenu(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        CenterWindow(hDlg);
        return TRUE;
    case WM_COMMAND:
        HWND medic_win, patient_win;
        MSG msg;
        switch (LOWORD(wParam)) {
        case IDC_BTN_TOMEDIC:
            medic_win = CreateMedicWindow(hInst);
            EndDialog(hDlg, 0);
             while (GetMessage(&msg, NULL, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                }
            return TRUE;
        case IDC_BTN_TOPATIENT:
            EndDialog(hDlg, 0);
            patient_win = CreatePatientWindow(hInst);
             while (GetMessage(&msg, NULL, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                }
            return TRUE;
        case IDC_BTN_TOCONSULT:
            EndDialog(hDlg, 0);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WindowProcLogin);
            return TRUE;
        case IDC_BTN_TOCITAS:
            EndDialog(hDlg, 0);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WindowProcLogin);
            return TRUE;
        case IDC_BTN_TOSPEC:
            EndDialog(hDlg, 0);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WindowProcLogin);
            return TRUE;
        case IDC_BTN_LOGOFF:
            EndDialog(hDlg, 0);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WindowProcLogin);
            return TRUE;
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
