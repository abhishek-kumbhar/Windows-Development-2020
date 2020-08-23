

# include <windows.h>
# include <stdio.h>

# define MYTIMER 1000
# define TIME 100


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
		TEXT("Rectangle Blink Demo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		900,
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

int iPaintFlag;

int i, j, k;


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HBRUSH hBrush[8];
	HDC hDc;
	RECT rC, rC1, rC2, rC3;
	PAINTSTRUCT pS;
	static FILE* fPtr = NULL;
	static long factor;



	switch (iMsg) {
	case WM_CREATE:
		fopen_s(&fPtr, "co-odinates.txt", "w");
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

	case WM_TIMER:
		KillTimer(hwnd, MYTIMER);
		if (i > 3)
			i = 0;
		if (j > 4)
			j = 1;
		if (k > 5)
			k = 2;

		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, MYTIMER, TIME, NULL);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rC);

		factor = rC.right / 3;
		rC1.left = rC.left; rC1.top = rC.top; rC1.right = rC.right / 2; rC1.bottom = rC.bottom;

		rC2.left = factor; rC2.top = 0; rC2.right = 2 * factor; rC2.bottom = rC.bottom;
		rC3.left = 2 * factor; rC3.top = 0; rC3.right = 3 * factor; rC3.bottom = rC.bottom;
		
		hDc = BeginPaint(hwnd, &pS);
		






		SelectObject(hDc, hBrush[i]);
		FillRect(hDc, &rC1, hBrush[i]);
		i += 3;

		SelectObject(hDc, hBrush[j]);
		FillRect(hDc, &rC2, hBrush[j]);
		j += 3;

		SelectObject(hDc, hBrush[k]);
		FillRect(hDc, &rC3, hBrush[k]);
		k += 3;

		EndPaint(hwnd, &pS);
		break;

	case WM_LBUTTONDOWN :
		GetClientRect(hwnd, &rC);
		fprintf(fPtr, "left : %ld\ntop : %ld\nright : %ld\nbottom : %ld\n", rC.left, rC.top, rC.right, rC.bottom);


	case WM_DESTROY:
		fclose(fPtr);
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}



