# include <windows.h>
# include <stdio.h>



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
DWORD WINAPI ThreadProcThree(LPVOID);
DWORD WINAPI ThreadProcFour(LPVOID);


RECT gRect;



		




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR	lpszCmdLine, int iCmdShow) {

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("Multi-Threading EMOJI"),
		WS_OVERLAPPEDWINDOW,
		200,
		200,
		700,
		700,
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

	HDC hdc, hdc1;
	RECT rc, rc1, rc2, rc3, rc4;
	
	static FILE* fp = NULL;
	static int l, t, r;
	static int xFact, yFact;


	static HBRUSH hbrush[6] = { CreateSolidBrush(RGB(255, 0, 0)), CreateSolidBrush(RGB(0, 255, 0)), CreateSolidBrush(RGB(0, 0, 255)),
								CreateSolidBrush(RGB(255, 255, 0)), CreateSolidBrush(RGB(255, 255, 255)), CreateSolidBrush(RGB(0, 0, 0)) };



	static HANDLE hThreadOne = NULL;
	static HANDLE hThreadTwo = NULL;
	static HANDLE hThreadThree = NULL;
	static HANDLE hThreadFour = NULL;

	PAINTSTRUCT ps;


	switch (iMsg) {
		
	case WM_CREATE :
		fopen_s(&fp, "co-ordinates.txt", "w");
		GetClientRect(hwnd, &gRect);
		
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		//hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;


	case WM_SIZE :
		GetClientRect(hwnd, &gRect);
		break;

	case WM_PAINT :

		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &gRect);

		// divided four quadrants
		rc1.left = gRect.left,        rc1.top = gRect.top,          rc1.right = gRect.right / 2,   rc1.bottom = gRect.bottom / 2;
		rc2.left = gRect.right / 2,   rc2.top = gRect.top,          rc2.right = gRect.right,       rc2.bottom = gRect.bottom / 2;

		rc3.left = gRect.left,        rc3.top = gRect.bottom / 2;   rc3.right = gRect.right / 2,   rc3.bottom = gRect.bottom;
		rc4.left = gRect.right / 2,   rc4.top = gRect.bottom / 2,   rc4.right = gRect.right,       rc4.bottom = gRect.bottom;
		
		//hdc = GetDC(hwnd);

		xFact = (gRect.right / 2) / 5;
		yFact = (gRect.bottom / 2) / 5;

		
		fprintf(fp, "\n\ngRect.left = %d, gRect.top = %d, gRect.right = %d, gRect.bottom = %d\n\n", gRect.left, gRect.top, gRect.right, gRect.bottom);
		fprintf(fp, "rc1.left = %d, rc1.top = %d, rc1.right = %d, rc1.bottom = %d\n", rc1.left, rc1.top, rc1.right, rc1.bottom);
		fprintf(fp, "rc2.left = %d, rc2.top = %d, rc2.right = %d, rc2.bottom = %d\n", rc2.left, rc2.top, rc2.right, rc2.bottom);
		fprintf(fp, "rc3.left = %d, rc3.top = %d, rc3.right = %d, rc3.bottom = %d\n", rc3.left, rc3.top, rc3.right, rc3.bottom);
		fprintf(fp, "rc4.left = %d, rc4.top = %d, rc4.right = %d, rc4.bottom = %d\n", rc4.left, rc4.top, rc4.right, rc4.bottom);

	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

		/*

		SelectObject(hdc, hbrush[0]);
		Ellipse(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);		// Outer Red Circle
		
		// 1st eye
		SelectObject(hdc, hbrush[4]);
		Ellipse(hdc, rc1.left + 1 * xFact, rc1.top + 1 * yFact, rc1.right - 3 * xFact, rc1.bottom - 3 * yFact + 40);  // Blue outer eye
		SelectObject(hdc, hbrush[5]);
		Ellipse(hdc, rc1.left + 1 * xFact + 30, rc1.top + 1 * yFact + 20, rc1.right - 3 * xFact, rc1.bottom - 3 * yFact + 20); // inner eye


		// 2nd eye
		SelectObject(hdc, hbrush[4]);
		Ellipse(hdc, rc1.left + 3 * xFact, rc1.top + 1 * yFact, rc1.right - 1 * xFact, rc1.bottom - 3 * yFact + 40);
		SelectObject(hdc, hbrush[5]);
		Ellipse(hdc, rc1.left + 3 * xFact + 30, rc1.top + 1 * yFact + 20, rc1.right - 1 * xFact, rc1.bottom - 3 * yFact + 20); // inner eye


		
		l = rc1.left + 1 * xFact, t = rc1.top + 3 * yFact, r = rc1.right - 1 * xFact;
		Arc(hdc, rc1.left + 1 * xFact, rc1.top + 3 * yFact, rc1.right - 1 * xFact, rc1.bottom - 1 * yFact, l, t, r, t);
		
		l = ((rc1.bottom - (1 * yFact)) - (rc1.top + (3 * yFact))) / 2;
		MoveToEx(hdc, rc1.left + 1 * xFact, rc1.top + 3 * yFact + l, NULL);
		LineTo(hdc, rc1.right - 1 * xFact, rc1.top + 3 * yFact + l);
		


		*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		
		SelectObject(hdc, hbrush[1]);
		Ellipse(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);		// Outer Green Circle

		// 1 st eye
		SelectObject(hdc, hbrush[4]);
		Ellipse(hdc, rc2.left + 1 * xFact, rc2.top + 1 * yFact, rc2.right - 3 * xFact, rc2.bottom - 3 * yFact + 40);  // Blue outer eye
		SelectObject(hdc, hbrush[5]);
		Ellipse(hdc, rc2.left + 1 * xFact, rc2.top + 1 * yFact + 20, rc2.right - 3 * xFact - 30, rc2.bottom - 3 * yFact + 20); // inner eye

		
		// 2nd eye
		SelectObject(hdc, hbrush[4]);
		Ellipse(hdc, rc2.left + 3 * xFact, rc2.top + 1 * yFact, rc2.right - 1 * xFact, rc2.bottom - 3 * yFact + 40);
		SelectObject(hdc, hbrush[5]);
		Ellipse(hdc, rc2.left + 3 * xFact, rc2.top + 1 * yFact + 20, rc2.right - 1 * xFact - 30, rc2.bottom - 3 * yFact + 20); // inner eye

		
		RoundRect(hdc, rc2.left + 1 * xFact, rc2.top + 3 * yFact, rc2.right - 1 * xFact, rc2.bottom - 1 * yFact, 60, 60);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		SelectObject(hdc, hbrush[2]);
		Ellipse(hdc, rc3.left, rc3.top, rc3.right, rc3.bottom);		// Outer Blue Circle


		// 1st eye
		SelectObject(hdc, hbrush[4]);
		Rectangle(hdc, rc3.left + 1 * xFact, rc3.top + 1 * yFact, rc3.right - 3 * xFact, rc3.bottom - 3 * yFact + 20);
		SelectObject(hdc, hbrush[5]);
		Rectangle(hdc, rc3.left + 1 * xFact + 20, rc3.top + 1 * yFact + 20, rc3.right - 3 * xFact - 10, rc3.bottom - 3 * yFact);


		// 2nd eye
		SelectObject(hdc, hbrush[4]);
		Rectangle(hdc, rc3.left + 3 * xFact, rc3.top + 1 * yFact, rc3.right - 1 * xFact, rc3.bottom - 3 * yFact + 20);
		SelectObject(hdc, hbrush[5]);
		Rectangle(hdc, rc3.left + 3 * xFact + 10, rc3.top + 1 * yFact + 20, rc3.right - 1 * xFact - 20, rc3.bottom - 3 * yFact);

		Ellipse(hdc, rc3.left + 1 * xFact, rc3.top + 3 * yFact, rc3.right - 1 * xFact, rc3.bottom - 1 * yFact);



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		SelectObject(hdc, hbrush[3]);
		Ellipse(hdc, rc4.left, rc4.top, rc4.right, rc4.bottom);		// Outer Yellow Circle
	

		// 1 st eye
		SelectObject(hdc, hbrush[4]);
		Ellipse(hdc, rc4.left + 1 * xFact,      rc4.top + 1 * yFact,      rc4.right - 3 * xFact + 35, rc4.bottom - 3 * yFact + 35);  // Blue outer eye
		SelectObject(hdc, hbrush[5]);
		Ellipse(hdc, rc4.left + 1 * xFact + 35, rc4.top + 1 * yFact + 35, rc4.right - 3 * xFact + 0,  rc4.bottom - 3 * yFact + 0); // inner eye


		// 2nd eye
		SelectObject(hdc, hbrush[4]);
		Ellipse(hdc, rc4.left + 3 * xFact - 30,  rc4.top + 1 * yFact,        rc4.right - 1 * xFact + 5,  rc4.bottom - 3 * yFact + 35);  // Blue outer eye
		SelectObject(hdc, hbrush[5]);
		Ellipse(hdc, rc4.left + 3 * xFact + 5,   rc4.top + 1 * yFact + 35,   rc4.right - 1 * xFact - 30, rc4.bottom - 3 * yFact); // inner eye

		Rectangle(hdc, rc4.left + 1 * xFact, rc4.top + 3 * yFact, rc4.right - 1 * xFact, rc4.bottom - 1 * yFact);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY :

		fclose(fp);

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
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}


DWORD WINAPI ThreadProcOne(LPVOID param) {
	
	HDC hdc;
	RECT rc1;
	HBRUSH hbrush[3];
	
	int xFact, yFact;
	int l, t, r;
	PAINTSTRUCT ps;

	hdc = GetDC((HWND)param);


	hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
	hbrush[1] = CreateSolidBrush(RGB(255, 255, 255));
	hbrush[2] = CreateSolidBrush(RGB(0, 0, 0));


	while (TRUE) {

		GetClientRect((HWND)param, &gRect);

		rc1.left = gRect.left, rc1.top = gRect.top, rc1.right = gRect.right / 2, rc1.bottom = gRect.bottom / 2;
		xFact = (gRect.right / 2) / 5;
		yFact = (gRect.bottom / 2) / 5;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		SelectObject(hdc, hbrush[0]);
		Ellipse(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);		// Outer Red Circle

		// 1st eye
		SelectObject(hdc, hbrush[1]);
		Ellipse(hdc, rc1.left + 1 * xFact, rc1.top + 1 * yFact, rc1.right - 3 * xFact, rc1.bottom - 3 * yFact + 40);  // Blue outer eye
		SelectObject(hdc, hbrush[2]);
		Ellipse(hdc, rc1.left + 1 * xFact + 30, rc1.top + 1 * yFact + 20, rc1.right - 3 * xFact, rc1.bottom - 3 * yFact + 20); // inner eye


		// 2nd eye
		SelectObject(hdc, hbrush[1]);
		Ellipse(hdc, rc1.left + 3 * xFact, rc1.top + 1 * yFact, rc1.right - 1 * xFact, rc1.bottom - 3 * yFact + 40);
		SelectObject(hdc, hbrush[2]);
		Ellipse(hdc, rc1.left + 3 * xFact + 30, rc1.top + 1 * yFact + 20, rc1.right - 1 * xFact, rc1.bottom - 3 * yFact + 20); // inner eye


		l = rc1.left + 1 * xFact, t = rc1.top + 3 * yFact, r = rc1.right - 1 * xFact;
		Arc(hdc, rc1.left + 1 * xFact, rc1.top + 3 * yFact, rc1.right - 1 * xFact, rc1.bottom - 1 * yFact, l, t, r, t);

		l = ((rc1.bottom - (1 * yFact)) - (rc1.top + (3 * yFact))) / 2;
		MoveToEx(hdc, rc1.left + 1 * xFact, rc1.top + 3 * yFact + l, NULL);
		LineTo(hdc, rc1.right - 1 * xFact, rc1.top + 3 * yFact + l);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
		
	}

	DeleteObject(hbrush[0]);
	DeleteObject(hbrush[1]);
	DeleteObject(hbrush[2]);

	ReleaseDC((HWND)param, hdc);
	return 0;
}


DWORD WINAPI ThreadProcTwo(LPVOID param) {
	
	return 0;
}


DWORD WINAPI ThreadProcThree(LPVOID param) {

	return 0;
}


DWORD WINAPI ThreadProcFour(LPVOID param) {

	return 0;
}









