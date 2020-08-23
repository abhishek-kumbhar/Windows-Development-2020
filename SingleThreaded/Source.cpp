

# include <windows.h>

# define MYTIMER 1000
# define TIME USER_TIMER_MINIMUM 

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL gbDone = FALSE;
RECT gRect;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");


	wndClass.cbSize = sizeof(wndClass);
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wndClass);


	hwnd = CreateWindow(szAppName,
		TEXT("Single Thread - Abhishek Kumbhar"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1500,
		800,
		NULL,
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	HDC hdc;
	HBRUSH hbrush;
	RECT rc;
	TCHAR str[255];
	static long i;

	hdc = GetDC(hWnd);


	switch (iMsg) {

	case WM_CREATE:
		GetClientRect(hWnd, &gRect);
		SetTimer(hWnd, MYTIMER, TIME, NULL);
		break;

	case WM_SIZE:
		GetClientRect(hWnd, &gRect);
		break;
	

	case WM_TIMER:
		KillTimer(hWnd, MYTIMER);
		InvalidateRect(hWnd, NULL, FALSE);
		SetTimer(hWnd, MYTIMER, TIME, NULL);
		break;


	case WM_PAINT:

		wsprintf(str, TEXT("Thread 1 : Increasing Order : %lu"), i);
		TextOut(hdc, 240, 140, str, wcslen(str));
		wsprintf(str, TEXT("Thread 2 : Decreasing Order : %lu"), 4194304 - i);
		TextOut(hdc, 240, 180, str, wcslen(str));
		i++;

		//----------------------------------------------------------------------------------------


			rc.left = gRect.right / 2 + (rand() % gRect.right / 2);
			rc.right = gRect.right / 2 + (rand() % gRect.right / 2);
			rc.top = (gRect.bottom / 2) + rand() % gRect.bottom / 2;
			rc.bottom = (gRect.bottom / 2) + rand() % gRect.bottom / 2;

			hbrush = CreateSolidBrush(RGB(0, 0, rand() % 256));
			SelectObject(hdc, hbrush);
			Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
			DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));


			//----------------------------------------------------------------------------------------


			rc.left = gRect.left + (rand() % gRect.right / 2);
			rc.right = gRect.left + (rand() % gRect.right / 2);
			rc.top = (gRect.bottom / 2) + rand() % gRect.bottom / 2;
			rc.bottom = (gRect.bottom / 2) + rand() % gRect.bottom / 2;

			hbrush = CreateSolidBrush(RGB(0, rand() % 256, 0));
			SelectObject(hdc, hbrush);
			RoundRect(hdc, rc.left, rc.top, rc.right, rc.bottom, rand() % 20, rand() % 20);
			DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));

			//----------------------------------------------------------------------------------------


			rc.left = gRect.right / 2 + (rand() % gRect.right / 2);
			rc.right = gRect.right / 2 + (rand() % gRect.right / 2);
			rc.top = rand() % gRect.bottom / 2;
			rc.bottom = rand() % gRect.bottom / 2;

			hbrush = CreateSolidBrush(RGB(rand() % 200, 0, 0));
			FillRect(hdc, &rc, hbrush);
			DeleteObject(hbrush);



		ReleaseDC(hWnd, hdc);


		break;

	case WM_KEYDOWN:
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	}

	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}




DWORD WINAPI ThreadProcOne(LPVOID param) {

	HDC hdc;
	long i;
	TCHAR str[255];

	hdc = GetDC((HWND)param);
	for (i = 0; i < 4194304; i++) {
		wsprintf(str, TEXT("Thread 1 : Increasing Order : %lu"), i);
		TextOut(hdc, 20, 10, str, wcslen(str));
		wsprintf(str, TEXT("Thread 2 : Decreasing Order : %lu"), 4194304 - i);
		TextOut(hdc, 20, 40, str, wcslen(str));
	}

	ReleaseDC((HWND)param, hdc);
	return 0;
}


DWORD WINAPI ThreadProcTwo(LPVOID param) {

	HDC hdc;
	HBRUSH hbrush;
	RECT rc;

	hdc = GetDC((HWND)param);

	while (gbDone == FALSE) {
		rc.left = gRect.right / 2 + (rand() % gRect.right / 2);
		rc.right = gRect.right / 2 + (rand() % gRect.right / 2);
		rc.top = rand() % gRect.bottom / 2;
		rc.bottom = rand() % gRect.bottom / 2;

		hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		FillRect(hdc, &rc, hbrush);
		DeleteObject(hbrush);
	}

	ReleaseDC((HWND)param, hdc);

	return 0;
}


DWORD WINAPI ThreadProcThree(LPVOID param) {

	HDC hdc;
	HBRUSH hbrush;
	RECT rc;

	hdc = GetDC((HWND)param);

	while (gbDone == FALSE) {
		rc.left = gRect.right / 2 + (rand() % gRect.right / 2);
		rc.right = gRect.right / 2 + (rand() % gRect.right / 2);
		rc.top = (gRect.bottom / 2) + rand() % gRect.bottom / 2;
		rc.bottom = (gRect.bottom / 2) + rand() % gRect.bottom / 2;

		hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, hbrush);
		Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
		DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));

	}

	ReleaseDC((HWND)param, hdc);

	return 0;
}



DWORD WINAPI ThreadProcFour(LPVOID param) {

	HDC hdc;
	HBRUSH hbrush;
	RECT rc;

	hdc = GetDC((HWND)param);

	while (gbDone == FALSE) {
		rc.left = gRect.left + (rand() % gRect.right / 2);
		rc.right = gRect.left + (rand() % gRect.right / 2);
		rc.top = (gRect.bottom / 2) + rand() % gRect.bottom / 2;
		rc.bottom = (gRect.bottom / 2) + rand() % gRect.bottom / 2;

		hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, hbrush);
		RoundRect(hdc, rc.left, rc.top, rc.right, rc.bottom, rand() % 20, rand() % 20);
		DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));

	}

	ReleaseDC((HWND)param, hdc);

	return 0;
}





