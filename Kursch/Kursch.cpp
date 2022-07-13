// Kursch.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Kursch.h"
#include <string>
#include <iostream>

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
    LoadStringW(hInstance, IDC_KURSCH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KURSCH));


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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KURSCH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KURSCH);
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

//Алгоритм шифрования текста 

std::string Shifr(std::string const &text, std::string const &key)
{
	std::string shifr;
	shifr.reserve(text.size());

	for (size_t i = 0; i < text.size(); i++)
		shifr.push_back(text[i] ^ key[i % key.size()]);
	
	return shifr;
}

std::string GetDlgItemText(HWND hwnd, int itemId) 
{
	std::string text;

	HWND item = GetDlgItem(hwnd, itemId);
	text.resize(GetWindowTextLengthA(item));
	GetWindowTextA(item, (LPSTR)text.data(), text.size() + 1);

	return text;
}

void SetDlgItemText(HWND hwnd, int itemId, std::string const &text) 
{
	SetDlgItemTextA(hwnd, itemId, text.c_str());
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	HANDLE hFile1;
	BOOL delFile;
	BOOL copyFile;

	//	PCWSTR path = L"C:\\Users\\anton\\source\\repos\\LanNomer6\\WinApi.txt";
	switch (message)
	{
	case WM_CREATE:
	{
		HWND edit_key = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 470, 400, 300, 30, hWnd, reinterpret_cast<HMENU>(111), nullptr, nullptr);
		HWND button_key = CreateWindow(L"BUTTON", L"Введите ключ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 125, 400, 300, 30, hWnd, reinterpret_cast<HMENU>(222), nullptr, nullptr);

		HWND edit1 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 125, 40, 300, 100, hWnd, reinterpret_cast<HMENU>(1), nullptr, nullptr);
		HWND button1 = CreateWindow(L"BUTTON", L"Шифровать текст", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 125, 155, 300, 30, hWnd, reinterpret_cast<HMENU>(2), nullptr, nullptr);
		HWND edit2 = CreateWindow(L"EDIT", NULL , WS_BORDER | ES_MULTILINE | WS_CHILD | WS_VISIBLE, 470, 40, 300, 100, hWnd, reinterpret_cast<HMENU>(3), nullptr, nullptr);
		HWND button2 = CreateWindow(L"BUTTON", L"Сохранить шифрованый файл", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 470, 155, 300, 30, hWnd, reinterpret_cast<HMENU>(4), nullptr, NULL);

		HWND edit3 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 125, 250, 300, 100, hWnd, reinterpret_cast<HMENU>(5), nullptr, nullptr);
		HWND button3 = CreateWindow(L"BUTTON", L"Расшифровать текст", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 125, 355, 300, 30, hWnd, reinterpret_cast<HMENU>(6), nullptr, nullptr);
		HWND edit4 = CreateWindow(L"EDIT", NULL, WS_BORDER | ES_MULTILINE | WS_CHILD | WS_VISIBLE, 470, 250, 300, 100, hWnd, reinterpret_cast<HMENU>(7), nullptr, nullptr);
		HWND button4 = CreateWindow(L"BUTTON", L"Сохранить дешифрованый файл", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 470, 355, 300, 30, hWnd, reinterpret_cast<HMENU>(8), nullptr, NULL);
	
		HWND edit5 = CreateWindow(L"EDIT", NULL, WS_BORDER | ES_MULTILINE | WS_CHILD | WS_VISIBLE, 470, 450, 500, 30, hWnd, reinterpret_cast<HMENU>(9), nullptr, nullptr);
		HWND button5 = CreateWindow(L"BUTTON", L"Расшифровать файл", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 125, 450, 300, 30, hWnd, reinterpret_cast<HMENU>(10), nullptr, NULL);

		HWND edit6 = CreateWindow(L"EDIT", NULL, WS_BORDER | ES_MULTILINE | WS_CHILD | WS_VISIBLE, 470, 490, 500, 30, hWnd, reinterpret_cast<HMENU>(11), nullptr, nullptr);
		HWND button6 = CreateWindow(L"BUTTON", L"Зашифровать файл", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 125, 490, 300, 30, hWnd, reinterpret_cast<HMENU>(12), nullptr, NULL);
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case 2: // Зашифровать текст
		{
			std::string text = GetDlgItemText(hWnd, 1);
			std::string key = GetDlgItemText(hWnd, 111);
			SetDlgItemText(hWnd, 3, Shifr(text, key));
		
			UpdateWindow(hWnd);
			break;
		}		
		case 4:  // Сохранить зашифрованный текст
		{
			std::string text = GetDlgItemText(hWnd, 3);

			hFile1 = CreateFile(L"D:\\SHIFR.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW,
 			FILE_ATTRIBUTE_NORMAL, NULL);
			
			DWORD bytesWritten;
			WriteFile(
				hFile1,           // Handle to the file
				text.data(),			  // Buffer to write
				text.size(),			  // Buffer size
				&bytesWritten,    // Bytes written
				nullptr);         // Overlapped

			CloseHandle(hFile1);

			MessageBox(hWnd, L"Шифр сохранен!", L"", 0);
			break;
		}
		case 6:  //  Расшифровать текст
		{
			std::string text = GetDlgItemText(hWnd, 5);
			std::string key = GetDlgItemText(hWnd, 111);
			SetDlgItemText(hWnd, 7, Shifr(text, key));

			UpdateWindow(hWnd);
			break;
		}
		case 8:  //  Сохранить расшифрованый текст
		{
			std::string text = GetDlgItemText(hWnd, 7);

			hFile1 = CreateFile(L"C:\\DE_SHIFR.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW,FILE_ATTRIBUTE_NORMAL, NULL);

			DWORD bytesWritten;
			WriteFile( hFile1, text.data(), text.size(), &bytesWritten, nullptr);    
			CloseHandle(hFile1);

			MessageBox(hWnd, L"Расшифровка сохранена!", L"", 0);
			break;
		}
		case 10:  //  Расшифровать файл
		{
			std::string fileName = GetDlgItemText(hWnd, 9);
			
			hFile1 = CreateFileA(fileName.c_str(), GENERIC_READ , 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hFile1 != INVALID_HANDLE_VALUE) {
				std::string text;
				std::string key = GetDlgItemText(hWnd, 111);

				text.resize(GetFileSize(hFile1, NULL));
				ReadFile(hFile1, (LPVOID)text.data(), text.size(), NULL , NULL);
				
				CloseHandle(hFile1);

				SetDlgItemText(hWnd, 5, text);
				
				SetDlgItemText(hWnd, 7, Shifr(text, key));
				UpdateWindow(hWnd);
			}
			else
			{
				MessageBox(hWnd, L"Не удалось открыь файл!", L"", 0);
			}
			break;
		}
		case 12: // Зашифровать файл
		{
			std::string fileName = GetDlgItemText(hWnd, 11);

			hFile1 = CreateFileA(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hFile1 != INVALID_HANDLE_VALUE) {
				std::string text;
				std::string key = GetDlgItemText(hWnd, 111);

				text.resize(GetFileSize(hFile1, NULL));
				ReadFile(hFile1, (LPVOID)text.data(), text.size(), NULL, NULL);

				CloseHandle(hFile1);

				SetDlgItemText(hWnd, 1, text);

				SetDlgItemText(hWnd, 3, Shifr(text, key));
				UpdateWindow(hWnd);
			}
			else
			{
				MessageBox(hWnd, L"Не удалось открыь файл!", L"", 0);
			}
			break;
		}
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc;
			hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc, 225, 15, L"Введите текст :", 15);
			TextOut(hdc, 600, 15, L"Шифр :", 6);

			TextOut(hdc, 170, 225, L"Введите шифрованый текст :", 27);
			TextOut(hdc, 570, 225, L"Расшифровка : ", 13);
		}
	break;
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
	