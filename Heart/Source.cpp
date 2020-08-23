#include<windows.h>
#include<stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	wndclass.hInstance = hInstance;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.lpszClassName = szAppName;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Heart"), WS_OVERLAPPEDWINDOW, 0, 0, 800, 800, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}

RECT gRect, gRectCopy;
HDC hdc;
FILE* fp;
HPEN hPen, hPen2;
RECT rc;

void change() {
	rc.left = 100;
	rc.top = 100;
	rc.right = 500;
	rc.bottom = 500;

	/*
	rc.left = gRect.left + 100;
	rc.top = gRect.top + 100;
	rc.right = gRect.right - 100;
	rc.bottom = gRect.bottom - 100;
	*/
}


void paint(HWND hwnd) {
	hdc = GetDC(hwnd);
	SelectObject(hdc, hPen);

	change();

	
	MoveToEx(hdc, rc.left, rc.top, NULL);
	LineTo(hdc, rc.right, rc.top);
	LineTo(hdc, rc.right, rc.bottom);
	LineTo(hdc, rc.left, rc.bottom);
	LineTo(hdc, rc.left, rc.top);
	

	
	MoveToEx(hdc, rc.left, rc.bottom / 2, NULL);
	LineTo(hdc, rc.right / 2, rc.top);
	LineTo(hdc, rc.right, rc.bottom / 2);
	LineTo(hdc, rc.right / 2, rc.bottom);
	LineTo(hdc, rc.left, rc.bottom / 2);
	


	ReleaseDC(hwnd, hdc);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	PAINTSTRUCT ps;
	
	static int i = 0;
	
	switch (iMsg) {
	case WM_CREATE :
		fp = fopen("a.txt", "w");
		hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		hPen2 = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
		break;

	case WM_SIZE :
		GetClientRect(hwnd, &gRect);
		break;

	case WM_RBUTTONDOWN :
		paint(hwnd);
		break;

	case WM_PAINT :
		
		
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, hPen);


		


		//MoveToEx(hdc, gRect.left, gRect.top, NULL);

		//LineTo(hdc, gRect.right, gRect.top);
		//LineTo(hdc, gRect.right, gRect.bottom);
		//LineTo(hdc, gRect.left, gRect.bottom);
		//LineTo(hdc, gRect.left, gRect.top);

		fprintf(fp, "left = %d, top = %d, right = %d, bottom = %d\n\n", gRect.left, gRect.top, gRect.right, gRect.bottom);
		

		SelectObject(hdc, hPen2);

	
		///MoveToEx(hdc, gRect.right / 2, gRect.top, NULL);
		

		///MoveToEx(hdc, gRect.right, gRect.bottom / 2, NULL);
		

		///MoveToEx(hdc, gRect.right / 2, gRect.bottom, NULL);
		


		fprintf(fp, "\ngRect.left      = %3d, gRect.bottom / 2 = %3d\n", gRect.left, gRect.bottom / 2);
		fprintf(fp, "gRect.right / 2 = %3d, gRect.top        = %3d\n", gRect.right / 2, gRect.top);
		fprintf(fp, "gRect.right     = %3d, gRect.bottom / 2 = %3d\n", gRect.right, gRect.bottom / 2);
		fprintf(fp, "gRect.right / 2 = %3d, gRect.bottom     = %3d\n", gRect.right / 2, gRect.bottom);
		fprintf(fp, "gRect.left      = %3d, gRect.bottom / 2 = %3d\n\n", gRect.left, gRect.bottom / 2);


		//fprintf(fp, "dist (a, b) = %d, %d\n", (gRect.left - gRect.right / 2), (gRect.bottom / 2 - gRect.top));

		fprintf(fp, "dist (a, b) = %d, %d\n", (gRect.right / 2 - gRect.left), (gRect.bottom / 2 - gRect.top));
		fprintf(fp, "dist (a, b) = %d, %d\n", (gRect.right - gRect.right / 2), (gRect.bottom / 2 - gRect.top));
		fprintf(fp, "dist (a, b) = %d, %d\n", (gRect.right - gRect.right / 2), (gRect.bottom - gRect.bottom / 2));
		fprintf(fp, "dist (a, b) = %d, %d\n", (gRect.right / 2 - gRect.left), (gRect.bottom - gRect.bottom / 2));



		//Arc(hdc, gRect.left, gRect.top, gRect.right, gRect.bottom, gRect.right, gRect.bottom / 2, gRect.left, gRect.bottom / 2);

		//Ellipse(hdc, gRect.left, gRect.top, gRect.right / 2, gRect.bottom / 2);


		EndPaint(hwnd, &ps);


		
		break;
	case WM_DESTROY :
		fclose(fp);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}




