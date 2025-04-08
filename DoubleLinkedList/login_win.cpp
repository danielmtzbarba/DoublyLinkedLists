#include "utils.h"
#include "data.cpp"
#include "resource.h"

inline INT_PTR CALLBACK WindowProcLogin(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        CenterWindow(hDlg);
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BTN_LOGIN:
            EndDialog(hDlg, 0);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), NULL, WindowProcMenu);
            return TRUE;
        case IDC_BTN_SIGNUP:
            EndDialog(hDlg, 0);
           DialogBox(hInst, MAKEINTRESOURCE(CU_VENTANAG), NULL, WindowProcSignUp);
            return TRUE;
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}

inline INT_PTR CALLBACK WindowProcSignUp(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        CenterWindow(hDlg);
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BTN_REGISTRAR:
            return TRUE;
        case IDC_BTN_RETURN:
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
