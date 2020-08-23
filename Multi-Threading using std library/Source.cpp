# include <windows.h>
# include <process.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void __cdecl ThreadProcOne(void*);
void __cdecl ThreadProcTwo(void*);


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
		TEXT("Multi-Threading using STANDARD LIBRARY FUNCTION"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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

	unsigned long ulThreadOne = 0;
	unsigned long ulThreadTwo = 0;		// can use unsigned long also


	switch (iMsg) {
		
	case WM_CREATE :
		ulThreadOne = _beginthread(ThreadProcOne, 0, (void*)hwnd);
		ulThreadTwo = _beginthread(ThreadProcTwo, 0, (void*)hwnd);
		break;

	case WM_DESTROY :
		PostQuitMessage(0);
		break;
	}
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}

void __cdecl ThreadProcOne(void* param) {
	
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
	_endthread();

}


void __cdecl ThreadProcTwo(void* param) {
	
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
	_endthread();

}







