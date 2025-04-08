#include "utils.h"
#include "data.cpp"
#include "resource.h"

inline INT_PTR CALLBACK WindowProcLogin(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    std::string id, password;
    switch (message) {
    case WM_INITDIALOG:
        CenterWindow(hDlg);
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BTN_LOGIN:
            id = ReadTextBox(hDlg, IDC_EDIT5);
            password = ReadTextBox(hDlg, IDC_EDIT4);
            if (user_list.UserLoginById(id, password)){
                EndDialog(hDlg, 0);
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), NULL, WindowProcMenu);
            }
            else {
            MessageBox(hDlg, L"Usuario o Contraseña incorrectos!", L"Info", MB_OK);
            }

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
    std::string id, lname1, lname2, fname, email, date, password;
    switch (message) {

    case WM_INITDIALOG:
        CenterWindow(hDlg);
        return TRUE;
    case WM_COMMAND:

        switch (LOWORD(wParam)) {
        case IDC_BTN_REGISTRAR:
            lname1  = ReadTextBox(hDlg, IDC_EDIT2);
            lname2 = ReadTextBox(hDlg, IDC_EDIT3);
            fname = ReadTextBox(hDlg, IDC_EDIT1);
            password = ReadTextBox(hDlg, IDC_EDIT4);
            email = ReadTextBox(hDlg, IDC_EDIT6);
            date = ReadTextBox(hDlg, IDC_EDIT5);
            id = email;
            user_list.addUser(id, fname, lname1, lname2, email, password, date);
            user_list.saveToFile();
            MessageBox(hDlg, L"Usuario registrado exitosamente!", L"Info", MB_OK);
            break;
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
