#include "lab_header.h"

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
  WindowClass.lpszClassName = szClassName;  /* This function is called by windows */
  WindowClass.style = CS_DBLCLKS;               /* Catch double-clicks */
  WindowClass.cbSize = sizeof (WNDCLASSEX);
  /* Use default icon and mouse-pointer */
  WindowClass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  WindowClass.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
  WindowClass.hCursor = LoadCursor (NULL, IDC_ARROW);
  WindowClass.lpszMenuName = NULL;                 /* No menu */
  WindowClass.cbClsExtra = 0;              /* No extra bytes after the window class */
  WindowClass.cbWndExtra = 0;             /* structure or the window instance */
  WindowClass.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(255, 255, 255));
  if (!RegisterClassEx (&WindowClass))
    return 0;
  hwnd = CreateWindowEx (0, /* Extended possibilites for variation */
                         szClassName,         /* Classname */
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

//-----------------------------------------------------------------------------
LRESULT CALLBACK windowProcedure (HWND hwnd_, UINT message_, WPARAM wParam_, LPARAM lParam_)
{
  static RECT rect;
  static int cxChar=LOWORD(GetDialogBaseUnits());
  static int cyChar=HIWORD(GetDialogBaseUnits());
  static int cxLength, cyHeight;
  int closeMessageBox;
  HDC hdc;
  PAINTSTRUCT ps ;
  LPDRAWITEMSTRUCT pdis;
  static HFONT FontCustom, FontClear;
  HGDIOBJ hfDefault=GetStockObject(DEFAULT_GUI_FONT);
  HGDIOBJ hFont = GetStockObject(ANSI_FIXED_FONT);
  switch (message_)
  {
    case WM_CREATE:
    {
      hEdit=CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                           WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
                           0, 0, 0, 0, hwnd_, (HMENU)IDC_MAIN_EDIT,
                           (HINSTANCE) GetWindowLong(hwnd_, GWL_HINSTANCE), NULL);
      SendMessage(hEdit, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE,0));
      SendMessage(hEdit, WM_SETTEXT, (WPARAM)NULL, (LPARAM)"");

      hEditSecond=CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                           WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
                           0, 0, 0, 0, hwnd_, (HMENU)IDC_SECOND_EDIT,
                           (HINSTANCE)GetWindowLong(hwnd_, GWLP_HINSTANCE), NULL);
      SendMessage(hEditSecond, WM_SETFONT, (WPARAM)FontCustom, MAKELPARAM(TRUE,0));
      SendMessage(hEditSecond, WM_SETTEXT, (WPARAM)NULL, (LPARAM)"");

      hWndButton = CreateWindowEx (NULL, "BUTTON", "OK",
                                   WS_TABSTOP|WS_VISIBLE|WS_BORDER|WS_ACTIVECAPTION|WS_CHILD|BS_PUSHBUTTON|BS_TEXT,
                                   0, 0, 0, 0, hwnd_,
                                   (HMENU) IDC_1ST_BUTTON, GetModuleHandle(NULL), NULL);
      SendMessage(hWndButton, BM_SETSTATE, 1, 0);
      SendMessage(hWndButton, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE,0));

      hWndButton2 = CreateWindowEx (NULL, "BUTTON", "WRITE",
                                    WS_TABSTOP|WS_CHILD|WS_VISIBLE|WS_ACTIVECAPTION|BS_OWNERDRAW|BS_TEXT,
                                    0, 0, 100, 20, hwnd_,
                                   (HMENU) IDC_2ND_BUTTON, GetModuleHandle(NULL), NULL);
      SendMessage(hWndButton2, BM_SETSTATE, 1, 0);
      SendMessage(hWndButton2, WM_SETFONT, (WPARAM)FontCustom, TRUE);

      hWndButtonClear = CreateWindowEx(NULL, "BUTTON", "CLEAR",
                                      WS_TABSTOP|WS_VISIBLE|WS_BORDER|WS_ACTIVECAPTION|WS_CHILD|BS_PUSHBUTTON|BS_TEXT,
                                      0, 0, 0, 0, hwnd_,
                                      (HMENU)IDC_BUTTON_CLEAR, GetModuleHandle(NULL), NULL);
      SendMessage(hWndButtonClear, WM_SETFONT, (WPARAM)FontClear, TRUE);
      SendMessage(hWndButton2, WM_SETFONT, (WPARAM)FontCustom, TRUE);

      hWndText = CreateWindow (TEXT("Static"), NULL, WS_CHILD|WS_VISIBLE|SS_LEFT, cxChar, cyChar,
                               GetSystemMetrics(SM_CXSCREEN), cyChar, hwnd_, (HMENU) IDC_TEXT,
                               (HINSTANCE)GetWindowLong(hwnd_, GWL_HINSTANCE), NULL);
      hWndTextSecond = CreateWindow(TEXT("Static"), NULL, WS_CHILD|WS_VISIBLE|SS_LEFT, cxChar, cyChar,
                                    GetSystemMetrics(SM_CXSCREEN), cyChar, hwnd_, (HMENU) IDC_TEXT_2ND,
                                    (HINSTANCE)GetWindowLong(hwnd_, GWL_HINSTANCE), NULL);
    }
    return 0;
    case WM_COMMAND:
      switch (wParam_)
      {
        case IDC_1ST_BUTTON:
          sendEditToTextControl(hEdit, hWndText, hfDefault);
          break;
        case IDC_2ND_BUTTON:
          sendEditToTextControl(hEditSecond, hWndTextSecond, FontCustom);
          break;
        case IDC_BUTTON_CLEAR:
          SendMessage (hEdit, WM_SETTEXT, 0, 0);
          SendMessage (hEditSecond, WM_SETTEXT, 0, 0);
          SendMessage (hWndText, WM_SETTEXT, 0, 0);
          SendMessage (hWndTextSecond, WM_SETTEXT, 0, 0);
          break;
      }
      break;
    case WM_SIZE:
      cxLength = LOWORD(lParam_);
      cyHeight = HIWORD(lParam_);
      InvalidateRect(hwnd_, &rect, TRUE);
      MoveWindow(hEdit, 5, 20, cxLength/2, cyHeight/2, TRUE);
      MoveWindow(hEditSecond, cxLength/2+10, 20, cxLength/2-20, cyHeight/2, TRUE);
      MoveWindow(hWndButton, 5, cyHeight/2+20,  100, 20, TRUE);
      MoveWindow(hWndButton2, cxLength/2+10, cyHeight/2+20, 100, 20, TRUE );
      MoveWindow(hWndButtonClear, cxLength/2-30, cyHeight-50, 60, 30, TRUE);
      MoveWindow(hWndText, 5, cyHeight/2+50, cxLength/2, cyHeight/2 -100, TRUE );
      MoveWindow(hWndTextSecond, cxLength/2+10, cyHeight/2+50, cxLength/2-20,
                 cyHeight/2-100, TRUE );
      return 0;
    case WM_CTLCOLOREDIT:
      {
      if (IDC_SECOND_EDIT == GetDlgCtrlID((HWND)lParam_)) {
        hdc = (HDC) wParam_;
        hBrushColor = CreateSolidBrush(clrGreenish);
        SetTextColor((HDC)wParam_, clrRedish);
        SetBkMode(hdc, TRANSPARENT);
        return (LRESULT)hBrushColor;
        }
      }
      return 0;
    case WM_CTLCOLORSTATIC:
    {
      if (IDC_TEXT_2ND == GetDlgCtrlID((HWND)lParam_))
      {
        hdc = (HDC) wParam_;
        hBrushColor = CreateSolidBrush(clrGreenish);
        SetTextColor((HDC)wParam_, clrRedish);
        SetBkMode(hdc, TRANSPARENT);
        return (LRESULT) hBrushColor;
      }
      break;
    }
    return 0;
    case WM_DRAWITEM:
    {
      LPDRAWITEMSTRUCT item;
      item = (LPDRAWITEMSTRUCT)lParam_;
      SelectObject(item->hDC, CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0,
                                         DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                         CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                         DEFAULT_PITCH, "Arial Black"));
      FillRect(item->hDC, &item->rcItem, WHITE_BRUSH);
      SelectObject(item->hDC, WHITE_BRUSH);
      SetTextColor(item->hDC, clrGreenish);
      SelectObject(item->hDC, CreatePen(PS_SOLID, 2, clrGreenish));
      if ((item->itemState & ODS_SELECTED)==FALSE)
      {
        SetTextColor(item->hDC, 0);
        SelectObject(item->hDC, CreateSolidBrush(clrGreenish));
        SelectObject(item->hDC, CreatePen(PS_SOLID, 1, clrGreenish));
      }
      SetBkMode(item->hDC, TRANSPARENT);
      RoundRect(item->hDC, item->rcItem.left, item->rcItem.top, item->rcItem.right,
                item->rcItem.bottom, 10, 10);
      int len = GetWindowTextLength(item->hwndItem);
      LPSTR lpBuff = new char[len+1];
      GetWindowText(item->hwndItem, lpBuff, len+1);
      DrawText(item->hDC, lpBuff, len, &item->rcItem, DT_CENTER);
    }
    return 0;
    case WM_PAINT:
    {
      FontCustom = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, FALSE,
                              0, 0, 0, 0, "Arial");
      FontClear = CreateFont(50, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, FALSE,
                              0, 0, 0, 0, "Tahoma");
      HDC hdc = BeginPaint(hwnd_, &ps);
      GetClientRect(hwnd_, &rect);
      SelectObject(hdc, GetStockObject(WPARAM(FontClear)));
      SetTextColor(hdc, clrRedish);
      DrawText(hdc, TEXT ("Hello, I am 1st Laboratory Work! "), -1, &rect,
               DT_SINGLELINE|DT_CENTER|DT_VCENTER+296);
      EndPaint(hwnd_, &ps);
    }
    return 0;
    case WM_SYSCOMMAND:
      switch (wParam_)
      {
        case SC_CLOSE:
          MessageBoxW(NULL, L"Not this way! Try other buttons",
                      (LPWSTR)L"ERROR", MB_ICONSTOP);
          return 0;
        case SC_MINIMIZE:
          ShowWindow(hwnd_, SW_MAXIMIZE);
          return 0;
        case SC_MAXIMIZE:
          closeMessageBox = MessageBoxW(NULL,
                                 L"This button actually closes the window."
                                 "Do you, really, want to close it ?",
                                 (LPWSTR)L"CLOSE", MB_YESNO);
          switch (closeMessageBox)
          {
            case IDYES:
              SendMessage(hwnd_, WM_DESTROY, 0, 0);
              break;
            case IDNO:
              break;
          }
          return 0;
        default:
          DefWindowProc (hwnd_, message_, wParam_, lParam_);
      }
      return 0;
    case WM_GETMINMAXINFO:
      MINMAXINFO FAR *lpMinMaxInfo;
      lpMinMaxInfo = (MINMAXINFO FAR *) lParam_;
      lpMinMaxInfo->ptMinTrackSize.x = 500;
      lpMinMaxInfo->ptMinTrackSize.y = 300;
      return 0;
    case WM_DESTROY:
      DeleteObject(FontCustom);
      DeleteObject(FontClear);
      PostQuitMessage(0);   /* send a WM_QUIT to the message queue */
      return 0;
    default:                  /* for messages that we don't deal with */
      return DefWindowProc (hwnd_, message_, wParam_, lParam_);
  }
  return 0;
}
//--------------------------------------------------------------------------------
void sendEditToTextControl(HWND hEdit_, HWND hWndText_, HGDIOBJ hFont_)
{
  LPWSTR buffer[256];
  SendMessage(hEdit_, WM_GETTEXT, sizeof(buffer)/sizeof(buffer[0]),
              reinterpret_cast<LPARAM>(buffer));
  SendMessage (hWndText_, WM_SETFONT, (WPARAM)hFont_, MAKELPARAM(TRUE, 0));
  SetWindowText (hWndText_, (LPCSTR) buffer);
}

