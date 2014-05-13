#if defined(UNICODE) && !defined(_UNICODE)
  #define _UNICODE
  #elif defined(_UNICODE) && !defined(UNICODE)
  #define UNICODE
#endif

#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <iostream>
#include <algorithm>
#include "resource.h"

HINSTANCE hInst;
HWND hListBox;
HWND hScrBarSizeHorz;
HWND hScrBarSizeVert;
HWND hScrBarClr;
HWND hEdit;
HWND hButtonAdd;
HWND hButtonRnd;
HWND hButtonChoose;
HWND hTextBox;
static int minX = 500;
static int minY = 300;
static HBRUSH hBrush;
TCHAR sz_class_name[] = _T("WindowClass");
HFONT someFont;

LRESULT CALLBACK windowProcedure (HWND hwnd_, UINT message_, WPARAM wParam_, LPARAM lParam_);
BOOL CALLBACK dialogProc (HWND hdlg_, UINT message_, WPARAM wParam, LPARAM lParam);
void GetWindowPos(HWND, int *, int *);

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
  WindowClass.hInstance = hInst;
  WindowClass.lpszClassName = sz_class_name;  /* This function is called by windows */
  //WindowClass.style = CS_DBLCLKS;               /* Catch double-clicks */
  WindowClass.cbSize = sizeof (WNDCLASSEX);
  /* Use default icon and mouse-pointer */
  WindowClass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  WindowClass.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
  WindowClass.hCursor = LoadCursor (NULL, IDC_ARROW);
  WindowClass.lpszMenuName = MAKEINTRESOURCE(MENU_MAIN);
  WindowClass.cbClsExtra = 0;              /* No extra bytes after the window class */
  WindowClass.cbWndExtra = 0;             /* structure or the window instance */
  WindowClass.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(255, 255, 255));
  if (!RegisterClassEx (&WindowClass))
    return 0;
  hwnd = CreateWindowEx (0, /* Extended possibilites for variation */
                         sz_class_name,         /* Classname */
                         _T("Laboratory Work Nr. 2"), /* Title Text */
                         WS_OVERLAPPEDWINDOW, /* default window */
                         0,       /* Windows decides the position */
                         0,     /* where the window ends up on the screen */
                         minX,                 /* The programs width */
                         minY,                 /* and height in pixels */
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
  static HMENU hMenu;
  static RECT rect;
  static int x, y;
  static int cxClient, cyClient;
  static int cxChar, cyChar;
  static int cxIcon, cyIcon;
  static int width, height;
  static int color;
  static int widthMax = GetSystemMetrics(SM_CXSCREEN);
  static int heightMax = GetSystemMetrics(SM_CYSCREEN);

  HDC hdc;
  SCROLLINFO scrollSize;
  TEXTMETRIC textMetric;
  PAINTSTRUCT ps;
  HINSTANCE hInstance;

  switch(message_)
  {
    case WM_CREATE:
      hEdit = CreateWindowExW(NULL, L"Edit", NULL,
                              WS_CHILD|WS_VISIBLE|ES_LEFT,
                              0, 0, 0, 0, hwnd_, (HMENU)ID_CTRL_EDIT,
                              (HINSTANCE)GetWindowLong(hwnd_, GWL_HINSTANCE),
                              NULL);
      SetDlgItemText(hwnd_, ID_CTRL_EDIT, "");
      hListBox = CreateWindowExW(WS_EX_CLIENTEDGE, L"LISTBOX",
                                NULL, WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_AUTOVSCROLL,
                                0, 0, 0, 0, hwnd_, (HMENU)ID_LIST_BOX, hInstance, NULL);
      SendMessage (hListBox, LB_ADDSTRING, 0, (LPARAM) "Vincit qui se vincit");
      SendMessage (hListBox, LB_ADDSTRING, 0, (LPARAM) "Omnia mea mecum porto");
      SendMessage (hListBox, LB_ADDSTRING, 0, (LPARAM) "Labor omnia vincit improbus");
      SendMessage (hListBox, LB_ADDSTRING, 0, (LPARAM) "Non est vivere set valere vita");
      SendMessage (hListBox, LB_ADDSTRING, 0, (LPARAM)"Nosce te impsum");

      hScrBarSizeHorz = CreateWindow(TEXT("scrollbar"), NULL,
                                     WS_CHILD|WS_VISIBLE|WS_TABSTOP|SBS_HORZ,
                                     0, 0, 0, 0, hwnd_, (HMENU)ID_SCROLL_HORZ,
                                     hInstance, NULL);
      SetScrollRange(hScrBarSizeHorz, SB_CTL, 0, 100, TRUE);

      hScrBarSizeVert = CreateWindow(TEXT("scrollbar"), NULL,
                                     WS_CHILD|WS_VISIBLE|WS_TABSTOP|SBS_VERT,
                                     0, 0, 0, 0, hwnd_, (HMENU)ID_SCROLL_VERT,
                                     hInstance, NULL);
      SetScrollRange(hScrBarSizeVert, SB_CTL, 0, 100, TRUE);

      hScrBarClr = CreateWindow(TEXT("scrollbar"), NULL,
                                WS_CHILD|WS_VISIBLE|WS_TABSTOP|SBS_VERT,
                                0, 0, 0, 0, hwnd_, (HMENU)ID_SCROLL_CLR,
                                hInstance, NULL);
      SetScrollRange(hScrBarClr, SB_CTL, 0, 255, TRUE);
      hButtonAdd = CreateWindow("button", "Add",
                                WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
                                0, 0, 0, 0, hwnd_, (HMENU)ID_BTN_ADD,
                                hInstance, NULL);
      SendMessage (hButtonAdd, BM_SETSTATE, 1, 0);
      SendMessage(hButtonAdd, WM_SETFONT, (WPARAM)someFont, TRUE);
      hButtonRnd = CreateWindowEx(NULL,"button", "Random",
                                WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
                                0, 0, 0, 0, hwnd_, (HMENU)ID_BTN_RND,
                                hInstance, NULL);

      hButtonChoose = CreateWindow("button", "Choose",
                                WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
                                0, 0, 0, 0, hwnd_, (HMENU)ID_BTN_RND,
                                hInstance, NULL);
      hTextBox = CreateWindowEx(NULL, TEXT("Static"), NULL, WS_CHILD|WS_VISIBLE|SS_LEFT, cxClient, cyClient,
                                GetSystemMetrics(SM_CXSCREEN), cyClient, hwnd_, (HMENU) ID_TEXT,
                                (HINSTANCE)GetWindowLong(hwnd_, GWL_HINSTANCE), NULL);
      hMenu = CreateMenu();
      hInstance = ((LPCREATESTRUCT)lParam_)->hInstance;
 //     FillListBox(HWND hwndList_);
      return 0;
    case WM_CTLCOLORSTATIC:
      hBrush = CreateSolidBrush (RGB(color, 255, 255));
      return (LRESULT) hBrush;
    case WM_PAINT:
      hdc = BeginPaint(hwnd_, &ps);
      someFont = CreateFont(14, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, FALSE,
                            0, 0, 0, 0, "Calibri");
      GetClientRect(hwnd_, &rect);
      //InvalidateRect(hwnd_, &rect, TRUE);
      EndPaint(hwnd_, &ps);
      return 0;
    case WM_COMMAND:
      int countListItem;
      int *bufferList;
      HWND hList;
      int index;
      switch (LOWORD(wParam_))
      {
        case IDD_HELP_ABOUT:
          DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_MAIN), hwnd_, dialogProc);
          return 0;
        case IDM_NEW_TRIAL:
          return 0;
        case IDM_CLEAR:
          return 0;
        case IDM_APP_EXIT:
          SendMessage(hwnd_, WM_CLOSE, 0, 0);
          return 0;
        case ID_BTN_ADD:
          LPWSTR buffer[256];
          SendMessage(hEdit, WM_GETTEXT, sizeof(buffer)/sizeof(buffer[0]),
                      reinterpret_cast<LPARAM>(buffer));
          SendMessage (hListBox, LB_INSERTSTRING, 0, (LPARAM) buffer);
          //SetWindowText (hListBox, (LPCSTR) buffer);
          return 0;
        case ID_BTN_RND:
          hList = GetDlgItem(hwnd_, ID_LIST_BOX);
          countListItem = SendMessage(hListBox, LB_GETSELCOUNT, 0, 0);
          GlobalAlloc(GPTR, (sizeof(int))*countListItem);
          SendMessage(hList, LB_GETSELITEMS, (WPARAM)countListItem, (LPARAM)bufferList);
          index = rand()*countListItem;
          SendMessage(hTextBox, WM_SETFONT, (WPARAM)someFont, index);
          SetWindowText (hTextBox, (LPCSTR) bufferList[index]);
          GlobalFree(bufferList);
          return 0;
        case ID_BTN_CHOICE:
          return 0;
      }
      hMenu = GetMenu(hwnd_);
      return 0;
    case WM_SIZE:
      cxClient = LOWORD(lParam_);
      cyClient = HIWORD(lParam_);
      cxChar = textMetric.tmAveCharWidth;
      cyChar = textMetric.tmHeight;
      scrollSize.cbSize = sizeof(scrollSize);
      scrollSize.fMask = SIF_RANGE|SIF_POS;
      scrollSize.nMin  = 0;
      scrollSize.nMax  = (minY-70)/cyChar;
      scrollSize.nPage = cyClient/cyChar;
      SetScrollInfo(hwnd_, SB_CTL, &scrollSize, TRUE);

      scrollSize.cbSize = sizeof(scrollSize);
      scrollSize.fMask = SIF_RANGE|SIF_POS;
      scrollSize.nMin = 0;
      scrollSize.nMax = minX/cxChar;
      scrollSize.nPage = cxClient/cxChar;
      SetScrollInfo(hwnd_, SB_CTL, &scrollSize, TRUE);


      MoveWindow(hEdit, 30, 30, cxClient/2-30, 20, TRUE);
      MoveWindow(hListBox, 30, 60, cxClient/2-30, cyClient*4/5, TRUE);
      MoveWindow(hScrBarClr, cxClient-25, 5, 20, cyClient-30, TRUE);
      MoveWindow(hScrBarSizeVert, 5, 5, 20, 180, TRUE);
      MoveWindow(hScrBarSizeHorz, 30, 5, 200, 20, TRUE);
      MoveWindow(hButtonAdd, cxClient/2+5, 60, 60, 40, TRUE);
      MoveWindow(hButtonRnd, cxClient/2+5, cyClient*4/5-30, 60, 40, TRUE);
      MoveWindow(hButtonChoose, cxClient/2+5, cyClient*4/5+10, 60, 40, TRUE);
      MoveWindow(hTextBox, cxClient/2+5, 100, cxClient/2-40, cyClient*4/5-130, TRUE);

      GetWindowRect(hwnd_, &rect);
      width = rect.right - rect.left;
      height = rect.bottom - rect.top;

      SetScrollPos(hScrBarSizeVert, SB_CTL, (height*100/heightMax), TRUE);
      SetScrollPos(hScrBarSizeHorz, SB_CTL, (width*100/widthMax), TRUE);

      return 0;
    case WM_VSCROLL:
      if ((HWND)lParam_==hScrBarClr)
      {
        switch (LOWORD(wParam_))
        {
          case SB_PAGEDOWN:
            color += 15;
            break;
          case SB_LINEDOWN:
            color = std::min(255, color+1);
            break;
          case SB_PAGEUP:
            color -= 15;
            break;
          case SB_LINEUP:
            color = std::max(0, color-1);
            break;
          case SB_TOP:
            color = 0;
            break;
          case SB_BOTTOM:
            color = 255;
            break;
          case SB_THUMBPOSITION:
          case SB_THUMBTRACK:
            color = HIWORD(wParam_);
            break;
          default:
            break;
        }
        SetScrollPos(hScrBarClr, SB_CTL, color, TRUE);
        InvalidateRect(hTextBox, &rect, TRUE);
      }
      if ((HWND)lParam_==hScrBarSizeVert)
      {
        scrollSize.cbSize = sizeof(scrollSize);
        scrollSize.fMask = SIF_ALL;
        GetScrollInfo(hScrBarSizeVert, SB_CTL, &scrollSize);
        switch (LOWORD(wParam_))
        {
          case SB_PAGEDOWN:
            scrollSize.nPos += 10;
            break;
          case SB_LINEDOWN:
            scrollSize.nPos += 1;
            break;
          case SB_PAGEUP:
            scrollSize.nPos -= 10;
            break;
          case SB_LINEUP:
            scrollSize.nPos -= 1;
            break;
          case SB_TOP:
            scrollSize.nPos = scrollSize.nMin;
            break;
          case SB_BOTTOM:
            scrollSize.nPos = scrollSize.nMax;
            break;
          case SB_THUMBPOSITION:
          case SB_THUMBTRACK:
            scrollSize.nPos=scrollSize.nTrackPos;
            break;
          default:
            break;
        }
        scrollSize.fMask = SIF_POS;
        SetScrollInfo(hScrBarSizeVert, SB_CTL, &scrollSize, TRUE);
        GetScrollInfo(hScrBarSizeVert, SB_CTL, &scrollSize);
        MoveWindow(hwnd_, rect.left, rect.top, width, (scrollSize.nPos*heightMax/100), TRUE);
      }
      return 0;
    case WM_HSCROLL:
      if ((HWND)lParam_==hScrBarSizeHorz)
      {
        scrollSize.cbSize=sizeof(scrollSize);
        scrollSize.fMask = SIF_ALL;
        GetScrollInfo(hScrBarSizeHorz, SB_CTL, &scrollSize);
        switch (LOWORD(wParam_))
        {
          case SB_PAGELEFT:
            scrollSize.nPos -= 10;
            break;
          case SB_LINELEFT:
            scrollSize.nPos -= 1;
            break;
          case SB_PAGERIGHT:
            scrollSize.nPos += 10;
            break;
          case SB_LINERIGHT:
            scrollSize.nPos += 1;
            break;
          case SB_LEFT:
            scrollSize.nPos = scrollSize.nMin;
            break;
          case SB_RIGHT:
            scrollSize.nPos = scrollSize.nMax;
            break;
          case SB_THUMBPOSITION:
          case SB_THUMBTRACK:
            scrollSize.nPos = HIWORD(wParam_);
            break;
          default:
            break;
        }
        SetScrollInfo(hScrBarSizeHorz, SB_CTL, &scrollSize, TRUE);
        GetScrollInfo(hScrBarSizeHorz, SB_CTL, &scrollSize);
        MoveWindow(hwnd_, rect.left, rect.top, (scrollSize.nPos*widthMax/100), height, TRUE);
      }
      return 0;
    case WM_KEYDOWN:
     // case
     //   break;
     // case
     //   break;
      return 0;
    /*  case WM_GETMINMAXINFO:
        MINMAXINFO FAR *lpMinMaxInfo;
        lpMinMaxInfo = (MINMAXINFO FAR *) lParam_;
        lpMinMaxInfo->ptMinTrackSize.x = 500;
        lpMinMaxInfo->ptMinTrackSize.y = 300;
        return 0;*/
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      return DefWindowProc (hwnd_, message_, wParam_, lParam_);
  }
  return 0;
}

BOOL CALLBACK dialogProc(HWND hDlg_, UINT message_, WPARAM wParam, LPARAM lParam)
{
  switch (message_)
  {
    case WM_INITDIALOG:
      return TRUE;
    case WM_COMMAND:
      switch (LOWORD(wParam))
      {
        case ID_OK:
        case ID_CANCEL:
          EndDialog(hDlg_, 0);
          return TRUE;
      }
      return 0;
    default:
      return FALSE;
  }
  return TRUE;
}

