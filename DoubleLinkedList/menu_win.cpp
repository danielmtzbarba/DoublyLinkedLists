#include "utils.h"
#include "data.cpp"
#include "resource.h"

inline INT_PTR CALLBACK WindowProcMenu(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BUTTON1:
            EndDialog(hDlg, 0);
           // DialogBox(hDlg, MAKEINTRESOURCE(IDD_DIALOG2), NULL, WindowProc);
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
