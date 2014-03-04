#if defined(UNICODE) && !defined(_UNICODE)
  #define _UNICODE
  #elif defined(_UNICODE) && !defined(UNICODE)
  #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "resource.h"

#define IDC_1ST_BUTTON      101
#define IDC_MAIN_EDIT       102
#define IDC_SECOND_EDIT     103
#define IDC_2ND_BUTTON      104
#define IDC_TEXT            105
#define IDC_TEXT_2ND        106
#define IDC_BUTTON_CLEAR    107

COLORREF clrRedish = RGB(255, 25, 2);
COLORREF clrGreenish = RGB(50, 200, 100);
HINSTANCE hInst;
HBRUSH hBrushColor;
TCHAR szClassName[ ] = _T("Le Window");

HWND hEdit, hEditSecond, hWndButtonClear;
HWND hWndButton, hWndButton2, hWndText, hWndTextSecond;

LRESULT CALLBACK windowProcedure (HWND, UINT, WPARAM, LPARAM);
void sendEditToTextControl(HWND hEdit, HWND hWndText, HGDIOBJ hFont);
