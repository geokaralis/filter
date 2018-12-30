// George Kavalieros (3120048)
// George Karalis (3120058)
// The application's entry point

//#include "ui/window.h"
#include "command_line.h"
#include "resource.h"

int main(int argc, char** argv) {
	CommandLine::Init(argc, argv);
}

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
//	const wchar_t CLASS_NAME[] = L"Negative";
//
//	WNDCLASS wc = { };
//
//	wc.style = 1;
//	wc.lpfnWndProc = ui::WindowProc;
//	wc.hInstance = hInstance;
//	wc.lpszClassName = CLASS_NAME;
//	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
//
//	RegisterClass(&wc);
//
//	// Create the window
//	HWND hwnd = CreateWindowEx(
//		0,
//		CLASS_NAME,
//		L"Negative",
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//		NULL,
//		NULL,
//		hInstance,
//		NULL
//	);
//
//	if (hwnd == NULL) {
//		return 0;
//	}
//
//	ShowWindow(hwnd, nCmdShow);
//	UpdateWindow(hwnd);
//
//	MSG msg = { };
//
//	while (GetMessage(&msg, NULL, 0, 0)) {
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	return 0;
//}





//
//void AddMenus(HWND hwnd) {
//
//	HMENU hMenubar;
//	HMENU hMenu;
//
//	hMenubar = CreateMenu();
//	hMenu = CreateMenu();
//
//	AppendMenuW(hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
//	AppendMenuW(hMenu, MF_STRING, IDM_FILE_OPEN, L"&Open");
//	AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
//	AppendMenuW(hMenu, MF_STRING, IDM_FILE_QUIT, L"&Quit");
//
//	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File");
//
//	HMENU hMenu2 = CreateMenu();
//
//	AppendMenuW(hMenu2, MF_STRING, IDM_FILE_NEW, L"&Negative");
//
//	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu2, L"&Edit");
//	SetMenu(hwnd, hMenubar);
//}
