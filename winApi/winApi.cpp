// winApi.cpp : Определяет точку входа для приложения.
//
#include <conio.h>
#include "framework.h"
#include "winApi.h"
#include <commdlg.h>

#define IDC_COMBOBOX 2001
#define IDC_STATIC 2002
#define IDC_CHECKBOX 2003
#define IDC_HOTKEY 2004
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   CreateWindowEx(0,
       TEXT("Static") ,TEXT("TEXT"),
       WS_CHILD | WS_VISIBLE,
       10, 10, 200, 20,
       hWnd, (HMENU)IDC_STATIC, hInstance, NULL);

       

   CreateWindowEx(0,
       TEXT("Button"), TEXT("Check"),
       BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
       230, 10, 100, 25,
       hWnd, (HMENU)IDC_CHECKBOX, hInstance, NULL);


   HWND ComboBox= CreateWindow(L"COMBOBOX", 
NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_HASSTRINGS, 
       340, 10, 150, 250, 
       hWnd, NULL, NULL, NULL);
       
   SendMessage(ComboBox, CB_ADDSTRING, 0, (LPARAM)L"Item1");
   SendMessage(ComboBox, CB_ADDSTRING, 0, (LPARAM)L"Item2");
   SendMessage(ComboBox, CB_ADDSTRING, 0, (LPARAM)L"Item3");


   HWND hotKey = CreateWindowEx(0,
      HOTKEY_CLASS,NULL,
       BS_CENTER|WS_CHILD|WS_VISIBLE,
       500,10,100,25,
       hWnd,(HMENU)IDC_HOTKEY,hInstance,NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

  
   return TRUE;
}


//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
BOOL showMsg = FALSE;
FINDREPLACE fr;
TCHAR szFindWhat[80] = TEXT("");
TCHAR szReplaceWith[80] = TEXT("");

BOOL bt1, bt2;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT* lpRect = (RECT*)lParam;
    switch (message)
    {
    case WM_CREATE: {
        SetTimer(hWnd, 1, 10000, NULL);
       
    }
   break;
    case WM_COMMAND:
        {
        CHOOSECOLOR cc;
        static COLORREF acrCustClr[16];

        ZeroMemory(&cc, sizeof(cc));
        cc.lStructSize = sizeof(cc);
        cc.hwndOwner = hWnd;
        cc.lpCustColors = acrCustClr;
        cc.rgbResult = RGB(255, 0, 0);
        cc.Flags = CC_FULLOPEN | CC_RGBINIT;
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
          
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            case IDC_COMBO1:
             if (ChooseColor(&cc)) {
                 MessageBox(hWnd, L"Selected Color", L"Color Chooser", MB_OK);
             }
            else {
                 MessageBox(hWnd, L"Color Selection Failed", L"Color Chooser", MB_OK | MB_ICONERROR);
               }
                break;

            case IDD_REPLACE:

                ZeroMemory(&fr, sizeof(fr));
                fr.lStructSize = sizeof(fr);
                fr.hwndOwner = hWnd;
                fr.wFindWhatLen = sizeof(szFindWhat);
                fr.wReplaceWithLen = sizeof(szReplaceWith);
                fr.Flags = FR_DOWN;
                fr.lpstrFindWhat = szFindWhat;
                fr.lpstrReplaceWith = szReplaceWith;
                if (ReplaceText(&fr) != FALSE) {

                }

                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        //TIMER
    case WM_TIMER: {
        if (wParam == 1 && !showMsg) {
            MessageBox(hWnd, L"Сработал таймер после 10 сек, после запуска", L"Информация", MB_OK | MB_ICONINFORMATION);
            showMsg = TRUE;
            KillTimer(hWnd, 1);
        }
        break;
    }
    
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_CHAR: {
        MessageBox(hWnd, L"Вы нажали на клавишу", L"Информация", MB_OK);
        break;
    }
    case WM_KEYUP: {
        MessageBox(hWnd, L"включен CAPSLOCK", L"Информация", MB_OK);
        break;
    }
    case WM_MOUSEWHEEL: {
        MessageBox(hWnd, L"Вы прокрутили колесо мышки", L"Информация", MB_OK);
        break;
    }
    case WM_MOVING: {
        MessageBox(hWnd, L"Вы передвигаете окно", L"Информация", MB_OK);
        break;
    }
    case WM_RBUTTONDBLCLK: {
        MessageBox(hWnd, L"вы дважды кликнули правой кнопкой мыши", L"Информация", MB_OK);
        break;
    }
    case WM_RBUTTONDOWN: {
        if(!bt1)
        {
            MessageBox(hWnd, L"Щелкнула правая кнопка мыши", L"Информация", MB_OK);
            bt1 = TRUE;
        }
        break;
    }
    case WM_RBUTTONUP: {
        if (!bt2)
        {
            MessageBox(hWnd, L"Правая кнопка мыши отпущена", L"Информация", MB_OK);
            bt2 = TRUE;
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
