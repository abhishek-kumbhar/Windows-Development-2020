
# include <windows.h>
# include "Source.h"


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX	wndClass;
	HWND hWnd;
	MSG msg;
	TCHAR szAppName[] = TEXT ("Demo");
	
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(szAppName,
		TEXT("Bitmap Demo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, 
		NULL, 
		hInstance,
		NULL
		);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	static HBITMAP hbitmap;
	static BITMAP bitmap;
	static HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rc;
	static HINSTANCE hInstance;
	
	switch (iMsg) {
	
	case WM_CREATE :
		hInstance = GetModuleHandle(NULL);
		hbitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
		hdcMem = CreateCompatibleDC(NULL);
		break;
	
	case WM_PAINT : 
		GetClientRect(hWnd, &rc);
		hdc = BeginPaint(hWnd, &ps);
		
		SelectObject(hdcMem, hbitmap);
		GetObject(hbitmap, sizeof(BITMAP), &bitmap);

		StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		EndPaint(hWnd, &ps);

		break;

	case WM_DESTROY : 
		DeleteObject(hbitmap);
		DeleteObject(hdcMem);
		PostQuitMessage(0);
		break;

	}

	return (DefWindowProc (hWnd, iMsg, wParam, lParam));
}





