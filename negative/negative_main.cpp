// George Kavalieros (3120048)
// George Karalis (3120058)
// The application's entry point

//#include "ui/window.h"
#include "command_line.h"

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
//	//wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
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






