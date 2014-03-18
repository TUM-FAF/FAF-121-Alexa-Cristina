#if defined(UNICODE) && !defined(_UNICODE)
  #define _UNICODE
  #elif defined(_UNICODE) && !defined(UNICODE)
  #define UNICODE
#endif

#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"

HINSTANCE hInst;
HWND hListBox, hScrBarOrizontSize;
TCHAR sz_class_name[] = _T("WindowClass");
LRESULT CALLBACK windowProcedure (HWND hwnd_, UINT message_, WPARAM wParam_, LPARAM lParam_);
BOOL CALLBACK dialogProc (HWND hdlg_, UINT message_, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain (HINSTANCE hThisInstance_, HINSTANCE hPrevInstance_,
                    LPSTR lpszArgument_, int nCmdShow_)
{
  HWND hwnd;               /* This is the handle for our window */
  MSG messages;            /* Here messages to the application are saved */
  WNDCLASSEX WindowClass;
  hInst = hThisInstance_;        /* Data structure for the windowclass */
  /* The Window structure */
  WindowClass.style = CS_HREDRAW | CS_VREDRAW;
  WindowClass.lpfnWndProc = windowProcedure;
  WindowClass.hInstance = hThisInstance_;
  WindowClass.lpszClassName = sz_class_name;  /* This function is called by windows */
  WindowClass.style = CS_DBLCLKS;               /* Catch double-clicks */
  WindowClass.cbSize = sizeof (WNDCLASSEX);
  /* Use default icon and mouse-pointer */
  WindowClass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  WindowClass.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
  WindowClass.hCursor = LoadCursor (NULL, IDC_ARROW);
  WindowClass.lpszMenuName = MAKEINTRESOURCE(MENU_MINE);
  WindowClass.cbClsExtra = 0;              /* No extra bytes after the window class */
  WindowClass.cbWndExtra = 0;             /* structure or the window instance */
  WindowClass.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(255, 255, 255));
  if (!RegisterClassEx (&WindowClass))
    return 0;
  hwnd = CreateWindowEx (0, /* Extended possibilites for variation */
                         sz_class_name,         /* Classname */
                         _T("1st Windows App"), /* Title Text */
                         WS_OVERLAPPEDWINDOW, /* default window */
                         CW_USEDEFAULT,       /* Windows decides the position */
                         CW_USEDEFAULT,     /* where the window ends up on the screen */
                         544,                 /* The programs width */
                         375,                 /* and height in pixels */
                         HWND_DESKTOP,        /* The window is a child-window to desktop */
                         NULL,                /* No menu */
                         hThisInstance_,       /* Program Instance handler */
                         NULL                 /* No Window Creation data */);

  ShowWindow (hwnd, nCmdShow_);
  UpdateWindow (hwnd);
  while (GetMessage (&messages, NULL, 0, 0))
  {
    TranslateMessage(&messages);
    DispatchMessage(&messages);
  }
  return messages.wParam;
}

LRESULT CALLBACK windowProcedure (HWND hwnd_, UINT message_, WPARAM wParam_, LPARAM lParam_)
{
  HMENU hMenu;
  static int cxClient, cyClient, cxIcon, cyIcon;
  HDC hdc;
  PAINTSTRUCT ps;
  HINSTANCE hInstance;
  switch(message_)
  {
    case WM_CREATE:
      hListBox = CreateWindowExW(WS_EX_CLIENTEDGE, L"LISTBOX",
                                NULL, WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_AUTOVSCROLL,
                                7, 35, 300, 200, hwnd_, NULL, hInstance, NULL);
      hScrBarOrizontSize = CreateWindowEx(TEXT("scrollbar"), NULL,
                                          WS_CHILD|WS_VISIBLE|WS_TABSTOP|SBS_VERT,
                                          0, 0, 0, 0, hwnd_, (HMENU),
                                          hInstance, NULL);
      hInstance = ((LPCREATESTRUCT) lParam_)->hInstance;
      hMenu = CreateMenu();
      return 0;
    case WM_PAINT:
      hdc = BeginPaint(hwnd_, &ps);
      EndPaint(hwnd_, &ps);
      return 0;
    case WM_COMMAND:
      hMenu = GetMenu(hwnd_);
      switch (LOWORD(wParam_))
      {
        case IDM_NEW_TRIAL:
          return 0;
        case IDM_CLEAR:
          return 0;
        case IDM_APP_EXIT:
          SendMessage(hwnd_, WM_CLOSE, 0, 0);
          return 0;
        case DLG_MAIN:
          DialogBox(hInstance, TEXT("TRa Ta Ta"), hwnd_, dialogProc);
          break;
      }
      return 0;
    case WM_SIZE:
      cxClient = LOWORD(lParam_);
      cyClient = HIWORD(lParam_);
      //InvalidateRect(hwnd_, &rect, TRUE);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      return DefWindowProc (hwnd_, message_, wParam_, lParam_);
  }
  return 0;
}

BOOL CALLBACK dialogProc (HWND hdlg_, UINT message_, WPARAM wParam, LPARAM lParam)
{
  switch (message_)
  {
    case WM_INITDIALOG:
      return 0;
    case WM_COMMAND:
      switch (LOWORD(wParam))
      {
        //case ID_OK:
        //return 0;
      }
      return 0;
  }
  return FALSE;
}
