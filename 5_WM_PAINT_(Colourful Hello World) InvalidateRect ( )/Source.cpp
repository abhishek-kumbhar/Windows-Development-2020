
# include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


char iPaintFlag;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndClass;
	HWND hWnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Demo");

	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);


	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(
		szAppName,
		TEXT("WM_CHAR Colorful Hello World in WM_PAINT"),
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

	HDC hDc;
	RECT rC;
	PAINTSTRUCT pS;
	TCHAR str[] = TEXT("Hello World !!!");

	switch (iMsg) {
		case WM_CREATE:
			iPaintFlag = 'w';
			break;

		case WM_CHAR :
			switch (wParam) {

				case 'R':
				case 'r': 
					iPaintFlag = 'r';
					InvalidateRect(hWnd, NULL, TRUE);
					break;

				case 'G':
				case 'g':
					iPaintFlag = 'g';
					InvalidateRect(hWnd, NULL, TRUE);
					break;

				case 'B':
				case 'b':
					iPaintFlag = 'b';
					InvalidateRect(hWnd, NULL, TRUE);
					break;
			}

			break;

		case WM_LBUTTONDOWN :
			iPaintFlag = 'w';
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case WM_RBUTTONDOWN:
			iPaintFlag = 'o';
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case WM_PAINT:
			GetClientRect(hWnd, &rC);
			hDc = BeginPaint(hWnd, &pS);
			SetBkColor(hDc, RGB(0, 0, 0));
			
			if (iPaintFlag == 'r') {
				SetTextColor(hDc, RGB(255, 0, 0));
			} else if (iPaintFlag == 'g') {
				SetTextColor(hDc, RGB(0, 255, 0));
			} else if (iPaintFlag == 'b') {
				SetTextColor(hDc, RGB(0, 0, 255));
			} else if (iPaintFlag == 'w') {
				SetTextColor(hDc, RGB(255, 255, 255));
			} else if (iPaintFlag == 'o') {
				SetTextColor(hDc, RGB(255, 128, 0));
			}
			
			DrawText(hDc, str, -1, &rC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &pS);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}