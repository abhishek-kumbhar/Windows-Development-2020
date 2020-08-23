

#include <windows.h>
#define MYTIMER 1000
#define TIME 2000


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
		TEXT("WM_TIMER Demo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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

int iPaintFlag;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HBRUSH hBrush[8];
	HDC hDc;
	RECT rC;
	PAINTSTRUCT pS;


	switch (iMsg) {
	case WM_CREATE :
		hBrush[0] = CreateSolidBrush(RGB(255, 0, 0));
		hBrush[1] = CreateSolidBrush(RGB(0, 255, 0));
		hBrush[2] = CreateSolidBrush(RGB(0, 0, 255));
		hBrush[3] = CreateSolidBrush(RGB(255, 255, 0));
		hBrush[4] = CreateSolidBrush(RGB(0, 255, 255));
		hBrush[5] = CreateSolidBrush(RGB(255, 0, 255));
		hBrush[6] = CreateSolidBrush(RGB(255, 255, 255));
		hBrush[7] = CreateSolidBrush(RGB(0, 0, 0));
		
		SetTimer(hwnd, MYTIMER, TIME, NULL);
		
		break;


	case WM_LBUTTONDOWN :
		
		
		break;

	case WM_TIMER :

		KillTimer(hwnd, MYTIMER);

		if (iPaintFlag > 7)
			iPaintFlag = -1;

		iPaintFlag++;

		InvalidateRect(hwnd, NULL, TRUE);


		SetTimer(hwnd, MYTIMER, TIME, NULL);
		break;

	case WM_PAINT :
		GetClientRect(hwnd, &rC);

		hDc = BeginPaint(hwnd, &pS);

		SelectObject(hDc, hBrush[iPaintFlag]);

		FillRect(hDc, &rC, hBrush[iPaintFlag]);
		
		EndPaint(hwnd, &pS);
		
		break;
		

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}



