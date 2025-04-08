#pragma once

#include "medic_list.h"
#include "patient_list.h"

extern HINSTANCE hInst;

extern INT_PTR CALLBACK WindowProcLogin(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcSignUp(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcMenu(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcMedic(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK WindowProcPatient(HWND, UINT, WPARAM, LPARAM);

extern HWND CreateMedicWindow(HINSTANCE hInstance);
extern HWND CreatePatientWindow(HINSTANCE hInstance);
extern void LoadMedicsIntoListBox(HWND hwndListBox, MedicNode* head);
extern void LoadPatientsIntoListBox(HWND hwndListBox, PatientNode* head);
