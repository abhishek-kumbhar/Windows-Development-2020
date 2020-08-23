

# include <windows.h>
# include <stdio.h>
# include "Source.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("MyWindow");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("India-Flag_Abhishek Kumbhar"),
		WS_OVERLAPPEDWINDOW,
		450,
		250,
		1000,
		600,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);

}

FILE* fPtr;



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	static HBITMAP hbitmap;
	static BITMAP bitmap;
	RECT rc, rc1, rc2, rc3;
	static HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	static HINSTANCE hInstance;
	static int x, y, w, h, r;

	switch (iMsg) {
	
	case WM_CREATE :
		hInstance = GetModuleHandle(NULL);
		hbitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
		hdcMem = CreateCompatibleDC(NULL);
		fopen_s(&fPtr, "Co-ordinates.txt", "w");
		break;

	case WM_PAINT :

		GetClientRect(hWnd, &rc);
		hdc = BeginPaint(hWnd, &ps);

		rc1.left = rc.left; rc1.right = rc.right; rc1.top = rc.top; rc1.bottom = rc.bottom / 3 * 1;
		fprintf(fPtr, "left : %d\ntop : %d\nright : %d\nbottom : %d\n\n\n", rc1.left, rc1.top, rc1.right, rc1.bottom);

		rc2.left = rc.left; rc2.right = rc.right;  rc2.top = rc.bottom / 3 * 1; rc2.bottom = rc.bottom / 3 * 2;
		fprintf(fPtr, "left : %d\ntop : %d\nright : %d\nbottom : %d\n\n\n", rc2.left, rc2.top, rc2.right, rc2.bottom);

		rc3.left = rc.left; rc3.right = rc.right;  rc3.top = rc.bottom / 3 * 2; rc3.bottom = rc.bottom;
		fprintf(fPtr, "left : %d\ntop : %d\nright : %d\nbottom : %d\n\n\n", rc3.left, rc3.top, rc3.right, rc3.bottom);
		
		FillRect(hdc, &rc1, CreateSolidBrush(RGB(255, 153, 51)));
		FillRect(hdc, &rc2, CreateSolidBrush(RGB(255, 255, 255)));
		FillRect(hdc, &rc3, CreateSolidBrush(RGB(19, 136, 8)));



		SelectObject(hdcMem, hbitmap);
		GetObject(hbitmap, sizeof(BITMAP), &bitmap);

		x = (rc.bottom / 3 * 2) + 50;
		y = rc.bottom / 3;
		w = rc.bottom / 3;
		h = rc.bottom / 3;

		StretchBlt(hdc, x, y, w, h, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		fprintf(fPtr, "x : %d  w : %d  h : %d   Bitmap --> width : %d   height : %d  \n\n\n", x, y, w, h, bitmap.bmWidth, bitmap.bmHeight);





		
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY :
		DeleteObject(hbitmap);
		DeleteObject(hdcMem);
		fclose(fPtr);
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}



