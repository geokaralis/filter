#include "window.h"
#include "../resource.h"

LRESULT CALLBACK ui::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Image *image = new Image();
	Color *color = new Color();

	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT: {
		std::string filename = "Image03.ppm";
		

		int width;

		RECT rect;
		if (GetWindowRect(hwnd, &rect))
		{
			width = rect.right - rect.left;
			int height = rect.bottom - rect.top;
		}

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		if (image->load(filename, "ppm")) {
			std::vector<Color> color = image->getRawDataPtr();
			color = negative::ApplyNegativeFilter(color, image->getWidth(), image->getHeight());

			COLORREF *arr = (COLORREF*)calloc(image->getWidth() * image->getHeight(), sizeof(COLORREF));
			// Need to convert image to b g r from rgb
			for (int i = 0; i < image->getWidth() * image->getHeight(); i++) {
				arr[i] = RGB(color[i].b * 255, color[i].g * 255, color[i].r * 255);
			}
			// Creating temp bitmap
			HBITMAP map = CreateBitmap(
				image->getWidth(), // width
				image->getHeight(), // height
				1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
				4*8, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
				(void*)arr); // pointer to array
			// Temp HDC to copy picture
			HDC src = CreateCompatibleDC(hdc); // hdc - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);
			SelectObject(src, map); // Inserting picture into our temp HDC
			// Copy image from temp HDC to window
			BitBlt(
				hdc, // Destination
				0,  // x and
				0,  // y - upper-left corner of place, where we'd like to copy
				image->getWidth(), // width of the region
				image->getHeight(), // height
				src, // source
				0,   // x and
				0,   // y of upper left corner  of part of the source, from where we'd like to copy
				SRCCOPY); // Defined DWORD to juct copy pixels. Watch more on msdn;

		

			DeleteDC(src); // Deleting temp HDC

			EndPaint(hwnd, &ps);
		}	
	}
	return 0;
	case WM_CLOSE:
		/*if (MessageBox(hwnd, L"Really quit?", L"Negative", MB_OKCANCEL) == IDOK) {
			DestroyWindow(hwnd);
		}*/
		// Else: User canceled. Do nothing.
		//return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_FILE_OPEN:
			//negative::ApplyNegativeFilter(color, image->getWidth(), image->getHeight());
			//DoFileOpen();
			break;
		default:
			break;
		}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}
