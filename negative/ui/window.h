#ifndef WINDOW_H
#define WINDOW_H

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <string>

#include "../negative.h"

namespace ui {
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}

#endif // !WINDOW_H

