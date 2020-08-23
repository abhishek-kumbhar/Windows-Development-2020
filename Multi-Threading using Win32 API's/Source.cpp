# include <windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My App");

	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("Multi-Threading using Win32 API's"),
		WS_OVERLAPPEDWINDOW,
		200,
		200,
		400,
		400,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);


}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	// local variables

	static HANDLE hThreadOne = NULL;
	static HANDLE hThreadTwo = NULL;

	switch (iMsg) {
		
	case WM_CREATE :
		
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;

	case WM_DESTROY :
		if (hThreadOne) {
			CloseHandle(hThreadOne);
			hThreadOne = NULL;
		}
		if (hThreadTwo) {
			CloseHandle(hThreadTwo);
			hThreadTwo = NULL;
		}
		PostQuitMessage(0);
		break;
	}
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}

DWORD WINAPI ThreadProcOne(LPVOID param) {
	
	// local variables
	HDC hdc;
	int i;
	TCHAR str[255];

	// code
	hdc = GetDC((HWND)param);
	for (i = 0; i < 65536; i++) {
		wsprintf(str, TEXT("Thread 1 (Increasing Order) : %d"), i);
		TextOut(hdc, 5, 20, str, wcslen(str));
	}
	
	ReleaseDC((HWND)param, hdc);

	return 0;
}


DWORD WINAPI ThreadProcTwo(LPVOID param) {
	
	// local variables
	HDC hdc;
	int i;
	TCHAR str[255];

	// code
	hdc = GetDC((HWND)param);
	for (i = 65536; i >= 0; i--) {
		wsprintf(str, TEXT("Thread 2 (Decreasing Order) : %d"), i);
		TextOut(hdc, 5, 40, str, wcslen(str));
	}

	ReleaseDC((HWND)param, hdc);
	
	return 0;

}







