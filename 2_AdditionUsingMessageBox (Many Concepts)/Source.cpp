
# include <windows.h>
# include <WindowsX.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndClass;
	MSG msg;
	HWND hWnd;
	TCHAR szAppName[] = TEXT("Demo");
	
	wndClass.cbSize = sizeof (wndClass);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	wndClass.hIconSm = LoadIcon(NULL, IDI_WARNING);
	wndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	
	RegisterClassEx(&wndClass);

	MessageBox(NULL, TEXT("MessageBox Before CreateWindow ( )"), TEXT(" "), MB_OK);

	hWnd = CreateWindow(szAppName,
		TEXT("Addition In GUI using wsprintf & MessageBox"),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		400,
		400,
		NULL,
		NULL, 
		hInstance,
		NULL
		);

	MessageBox(hWnd, TEXT("MessageBox After CreateWindow ( )"), TEXT(" "),MB_OK);


	ShowWindow(hWnd, iCmdShow);
	MessageBox(hWnd, TEXT("MessageBox After ShowWindow ( )"), TEXT(" "), MB_OK);

	UpdateWindow(hWnd);
	MessageBox(hWnd, TEXT("MessageBox After UpdateWindow ( )"), TEXT(" "), MB_OK);


	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}	

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static int a = 90, b = 9, c;
	static TCHAR str[255];
	static int x, y, w, h;
	static char ch;

	switch (iMsg) {

		case WM_CREATE : 
			//wsprintf(str, TEXT("wParam : %d   lParam : %ld"), wParam, lParam);
			//MessageBox(hWnd, str, TEXT("wParam and lParam of WM_CREATE message"), MB_OK);
			
			x = ((LPCREATESTRUCT)lParam)->x;
			y = ((LPCREATESTRUCT)lParam)->y;
			w = ((LPCREATESTRUCT)lParam)->cx;
			h = ((LPCREATESTRUCT)lParam)->cy;
			 
			c = a + b;
			
			break;

		case WM_LBUTTONDOWN :
			
			//wsprintf(str, TEXT("wParam : %d   lParam : %ld"), wParam, lParam);
			//MessageBox(hWnd, str, TEXT("wParam and lParam of WM_LBUTTONDOWN message"), MB_OK);


			//wsprintf(str, TEXT("Which Mouse Button Pressed : %c   %d"), wParam, wParam);
			wsprintf(str, TEXT("Co-Ordinates of Mouse (x, y) : %d    %d"), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			MessageBox(hWnd, str, TEXT("Co-Ordinates"), MB_OK);

			
			// for WM_KEYDOWN event
			wsprintfW(str, TEXT("Key pressed in WM_KEYDOWN : %c"), ch);
			MessageBox(hWnd, str, TEXT("WM_KEYDOWN events Output"), MB_OK);
			//


			break;

		case WM_RBUTTONDOWN :

			wsprintf(str, TEXT("x = %d  y = %d  w = %d  h = %d  "), x, y, w, h);
			MessageBox(hWnd, str, TEXT("From lParam of WM_CREATE..."), MB_OK);

			wsprintf(str, TEXT("The SUM of %d and %d is %d"), a, b, c);
			MessageBox(hWnd, str, TEXT("Addition"), MB_OK);
			break;

		case WM_KEYDOWN :
			
			// for WM_LBUTTONDOWN checking
			ch = wParam;
			//

			wsprintf(str, TEXT("Key Pressed = %c"), wParam);
			MessageBox(hWnd, str, TEXT("Key Found"), MB_OK);
			break;

		case WM_DESTROY:

			wsprintf(str, TEXT("wParam : %d   lParam : %ld"), wParam, lParam);
			MessageBox(hWnd, str, TEXT("wParam and lParam of WM_DESTROY message"), MB_OK);	// 0 0


			PostQuitMessage(0);
			break;
	}
	return (DefWindowProc(hWnd, iMsg, wParam, lParam));

}
