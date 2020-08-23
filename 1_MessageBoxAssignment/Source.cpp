
# include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("App");

	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("This is MessegeBox Demo"),
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
	
	switch (iMsg) {
		case WM_CREATE :
			MessageBox(hWnd, TEXT("WM_CREATE ARRIVED"), TEXT("1st case (WM_CREATE)"), MB_OKCANCEL | MB_ICONINFORMATION);
			break;
		case WM_KEYDOWN:
			MessageBox(hWnd, TEXT("WM_KEYDOWN ARRIVED"), TEXT("2nd case (WM_KEYDOWN)"),MB_OK);
			break;
		case WM_LBUTTONDOWN:
			MessageBox(hWnd, TEXT("WM_LBUTTONDOWN ARRIVED"), TEXT("3rd case (WM_LBUTTONDOWN)"), MB_SYSTEMMODAL);
			break;
		case WM_RBUTTONDOWN:
			MessageBox(hWnd, TEXT("WM_RBUTTONDOWN ARRIVED"), TEXT("4th case (WM_RBUTTONDOWN)"), MB_TASKMODAL);
			break;
		case WM_DESTROY:
			MessageBox(hWnd, TEXT("WM_DESTROY ARRIVED"), TEXT("5th case (WM_DESTROY)"), MB_OK);
			PostQuitMessage(0);
			break;
	}
	return (DefWindowProc(hWnd, iMsg, wParam, lParam));

}



