#include "utils.h"
#include "data.cpp"
#include "resource.h"
#include "menu_win.cpp"

inline INT_PTR CALLBACK WindowProcLogin(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BUTTON1:
            EndDialog(hDlg, 0);
           // DialogBox(hDlg, MAKEINTRESOURCE(IDD_DIALOG2), NULL, WindowProcMenu);
            return TRUE;
        case IDC_BUTTON2:
            EndDialog(hDlg, 0);
            return TRUE;
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
