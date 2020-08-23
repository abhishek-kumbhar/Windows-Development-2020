

# include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
DWORD WINAPI ThreadProcThree(LPVOID);
DWORD WINAPI ThreadProcFour(LPVOID);

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
		TEXT("MultiThreadinng Four - Abhishek Kumbhar"),
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


	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	static HANDLE hThreadOne = NULL;
	static HANDLE hThreadTwo = NULL;
	static HANDLE hThreadThree = NULL;
	static HANDLE hThreadFour = NULL;


	switch (iMsg) {

	case WM_CREATE:
		GetClientRect(hWnd, &gRect);
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hWnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hWnd, 0, NULL);
		hThreadThree = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcThree, (LPVOID)hWnd, 0, NULL);
		hThreadFour = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcFour, (LPVOID)hWnd, 0, NULL);

		break;

	case WM_SIZE:
		GetClientRect(hWnd, &gRect);
		break;

	case WM_PAINT : 
		break;


	case WM_KEYDOWN:
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_DESTROY:
		if (hThreadOne) {
			CloseHandle(hThreadOne);
			hThreadOne = NULL;
		}

		if (hThreadTwo) {
			CloseHandle(hThreadTwo);
			hThreadTwo = NULL;
		}

		if (hThreadThree) {
			CloseHandle(hThreadThree);
			hThreadThree = NULL;
		}

		if (hThreadFour) {
			CloseHandle(hThreadFour);
			hThreadFour = NULL;
		}

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
		rc.left = gRect.right / 2   + (rand() % gRect.right / 2);
				  // start from 2nd quad + add shapes with right end as sizeof half of screen

		rc.top = gRect.top          +  rand() % gRect.bottom / 2;
				  // start from top of the screen + add shapes with sizeof half bottom of screen


		rc.right = gRect.right / 2  + (rand() % gRect.right / 2);
				    // start from 2nd quad + add shapes with sizeof half bottom of screen


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
		
		rc.left = gRect.right / 2 + rand() % gRect.right / 2;
		rc.top = gRect.bottom / 2 + rand() % gRect.bottom / 2;

		rc.right = gRect.right / 2 + (rand() % gRect.right / 2);
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
		rc.top = (gRect.bottom / 2) + rand() % gRect.bottom / 2;
		

		rc.right = gRect.left + (rand() % gRect.right / 2);
		rc.bottom = (gRect.bottom / 2) + rand() % gRect.bottom / 2;

		hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, hbrush);
		RoundRect(hdc, rc.left, rc.top, rc.right, rc.bottom, rand() % 20, rand() % 20);
		DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));

	}

	ReleaseDC((HWND)param, hdc);
	
	return 0;
}





