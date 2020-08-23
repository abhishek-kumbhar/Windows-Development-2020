

#include<windows.h>
#include<stdio.h>
#include<math.h>

#define MYTIMER 1000
#define MYTIMER2 1001
#define MYTIMER3 1002
#define MYTIMER4 1003

#define TIME 35
#define TIME2 100
#define TIME3 100
#define TIME4 100

#define TWOPI (2 * 3.14159)
#define NUM 1000

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK MyTimerProc(HWND, UINT, UINT_PTR, DWORD);
void CALLBACK MyTimerProc2(HWND, UINT, UINT_PTR, DWORD);
void CALLBACK MyTimerProc3(HWND, UINT, UINT_PTR, DWORD);
void CALLBACK MyTimerProc4(HWND, UINT, UINT_PTR, DWORD);




RECT gRect, gSteps[3], gPole;
HDC hdc;
int xFact, yFact;
int poleWidth;
FILE* fp;


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("MyApp");
	
	wndclass.cbSize = sizeof (WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("India Flag 15 August Demo - Abhishek Kumbhar"),
		WS_OVERLAPPEDWINDOW,
		200,
		100,
		1400,
		900,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);
	
	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);

}

void MakeSteps() {
	gSteps[0].left = 7 * xFact; gSteps[0].top = 19 * yFact; gSteps[0].right = 13 * xFact; gSteps[0].bottom = 20 * yFact;
	gSteps[1].left = 8 * xFact; gSteps[1].top = 18 * yFact; gSteps[1].right = 12 * xFact; gSteps[1].bottom = 19 * yFact;
	gSteps[2].left = 9 * xFact; gSteps[2].top = 17 * yFact; gSteps[2].right = 11 * xFact; gSteps[2].bottom = 18 * yFact;

}

void MakePole() {
	gPole.left = 9 * xFact + (0.75 * xFact); 
	gPole.top = 1 * yFact;
	gPole.right = 10 * xFact + (0.25 * xFact);
	gPole.bottom = 17 * yFact;
	poleWidth = gPole.right - gPole.left;
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;

	switch (iMsg) {

	case WM_CREATE : 
		SetTimer(hwnd, MYTIMER, TIME, MyTimerProc);
		fp = fopen("file.txt", "w");
		break;

	case WM_SIZE :
		GetClientRect(hwnd, &gRect);
		xFact = gRect.right / 20;
		yFact = gRect.bottom / 20;
		MakeSteps();
		MakePole();

		break;

	case WM_PAINT :
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &gRect);
		EndPaint(hwnd, &ps);
		break;

	case WM_TIMER :
		break;

	case WM_DESTROY :
		fclose(fp);
		PostQuitMessage(0);
		break;
	
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

RECT rectDx1, rectDx2, rectDx3;
RECT rectPole, rectPoleBack;
int stepTop = 1;



int timerTwoEnd = 0;
int poleLeft, poleRight;

void CALLBACK MyTimerProc2(HWND hwnd, UINT iMsg, UINT_PTR timerEvent, DWORD ms) {
	
	KillTimer(hwnd, MYTIMER2);
	static HBRUSH hBrush;
	static int x = 1;
	hdc = GetDC(hwnd);

	if (x) {
		x = 0;
		rectPole.left = gRect.left;
		rectPole.right = rectPole.left + poleWidth;
		rectPole.top = gPole.top;
		rectPole.bottom = gPole.bottom;
	}

	if (rectPole.right <= gPole.left) {
		rectPoleBack.left = rectPole.left;
		rectPoleBack.top = rectPole.top;
		rectPoleBack.right = rectPole.right;
		rectPoleBack.bottom = rectPole.bottom;
		
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, hBrush);
		FillRect(hdc, &rectPoleBack, hBrush);
	
		rectPole.left = rectPole.right;
		rectPole.right = rectPole.right + poleWidth;

		hBrush = CreateSolidBrush(RGB(98, 98, 98));
		SelectObject(hdc, hBrush);
		FillRect(hdc, &rectPole, hBrush);
	}
	else {

		timerTwoEnd = 1;

		rectPoleBack.left = rectPole.left;
		rectPoleBack.top = rectPole.top;
		rectPoleBack.right = rectPole.right;
		rectPoleBack.bottom = rectPole.bottom;

		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, hBrush);
		FillRect(hdc, &rectPoleBack, hBrush);
		
		rectPole.left = rectPole.right - (poleWidth / 2);
		rectPole.right = rectPole.right + (poleWidth / 2) ;
		
		poleRight = rectPole.right;
		poleLeft = rectPole.left;

		hBrush = CreateSolidBrush(RGB(98, 98, 98));
		SelectObject(hdc, hBrush);
		FillRect(hdc, &rectPole, hBrush);
	}

	if (timerTwoEnd) {
		KillTimer(hwnd, MYTIMER2);
		ReleaseDC(hwnd, hdc);
		SetTimer(hwnd, MYTIMER3, TIME3, MyTimerProc3);
	}
	else {
		SetTimer(hwnd, MYTIMER2, TIME2, MyTimerProc2);
	}
}



void CALLBACK MyTimerProc(HWND hwnd, UINT iMsg, UINT_PTR timerEvent, DWORD ms) {

	KillTimer(hwnd, MYTIMER);
	static HBRUSH hBrush;
	hdc = GetDC(hwnd);

	static int x = 1;
	static int sOneStepComplete = 0, sTwoStepComplete = 0, sThreeStepComplete = 0;

	if (x) {
		x = 0;

		rectDx1.left = gSteps[0].left;
		rectDx1.top = gSteps[0].bottom;
		rectDx1.right = gSteps[0].right;
		rectDx1.bottom = gSteps[0].bottom;

		rectDx2.left = gSteps[1].left;
		rectDx2.top = gSteps[1].bottom;
		rectDx2.right = gSteps[1].right;
		rectDx2.bottom = gSteps[1].bottom;

		rectDx3.left = gSteps[2].left;
		rectDx3.top = gSteps[2].bottom;
		rectDx3.right = gSteps[2].right;
		rectDx3.bottom = gSteps[2].bottom;

		//MessageBox(hwnd, TEXT(" "), TEXT(" "), MB_OK);
	}

	if (!sOneStepComplete) {
		if (rectDx1.top >= gSteps[0].top) {
			rectDx1.top = gSteps[0].bottom - stepTop;
			hBrush = CreateSolidBrush(RGB(19, 136, 8));
			//hBrush = CreateSolidBrush(RGB(98, 98, 98));

			SelectObject(hdc, hBrush);
			RoundRect(hdc, rectDx1.left, rectDx1.top, rectDx1.right, rectDx1.bottom, 45, 45);
			//FillRect(hdc, &rectDx1, hBrush);
		}
		else {
			stepTop = 1;
			sOneStepComplete = 1;
		}

	}
	else if (!sTwoStepComplete) {
		if (rectDx2.top >= gSteps[1].top) {
			rectDx2.top = gSteps[1].bottom - stepTop;
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			//hBrush = CreateSolidBrush(RGB(98, 98, 98));

			SelectObject(hdc, hBrush);
			RoundRect(hdc, rectDx2.left, rectDx2.top, rectDx2.right, rectDx2.bottom, 45, 45);
			//FillRect(hdc, &rectDx2, hBrush);
		}
		else {
			stepTop = 1;
			sTwoStepComplete = 1;
		}
	}
	else if (!sThreeStepComplete) {
		if (rectDx3.top >= gSteps[2].top) {
			rectDx3.top = gSteps[2].bottom - stepTop;
			hBrush = CreateSolidBrush(RGB(255, 153, 51));
			//hBrush = CreateSolidBrush(RGB(98, 98, 98));

			SelectObject(hdc, hBrush);
			RoundRect(hdc, rectDx3.left, rectDx3.top, rectDx3.right, rectDx3.bottom, 45, 45);
			//FillRect(hdc, &rectDx3, hBrush);
		}
		else {
			sThreeStepComplete = 1;
		}
	}

	stepTop += 1;

	if (sOneStepComplete && sTwoStepComplete && sThreeStepComplete) {
		KillTimer(hwnd, MYTIMER);
		ReleaseDC(hwnd, hdc);
		SetTimer(hwnd, MYTIMER2, TIME2, MyTimerProc2);
	}
	else {
		SetTimer(hwnd, MYTIMER, TIME, MyTimerProc);
	}
}


RECT rectFlagDx1, rectFlagDx2, rectFlagDx3;
int flagEnd;
int flagLenInc;

void CALLBACK MyTimerProc3(HWND hwnd, UINT iMsg, UINT_PTR timerEvent, DWORD ms) {
	KillTimer(hwnd, MYTIMER3);
	static HBRUSH hBrush;
	hdc = GetDC(hwnd);
	static int sOneFlagComplete = 0, sTwoFlagComplete = 0, sThreeFlagComplete = 0;
	static int x = 1;

	if (x) {
		x = 0;
		//MessageBox(hwnd, TEXT(" "), TEXT(" "), MB_OK);
		flagEnd = poleRight + (5 * xFact);

		rectFlagDx1.left = poleRight;
		rectFlagDx1.top = gPole.top;
		rectFlagDx1.right = rectFlagDx1.left;
		rectFlagDx1.bottom = gPole.top + (2 * yFact);

		rectFlagDx2.left = poleRight;
		rectFlagDx2.top = rectFlagDx1.bottom;
		rectFlagDx2.right = rectFlagDx2.left;
		rectFlagDx2.bottom = gPole.top + (4 * yFact);

		rectFlagDx3.left = poleRight;
		rectFlagDx3.top = rectFlagDx2.bottom;
		rectFlagDx3.right = rectFlagDx3.left;
		rectFlagDx3.bottom = gPole.top + (6 * yFact);



	}

	if (!sOneFlagComplete) {
		if (rectFlagDx1.right <= flagEnd) {
			//MessageBox(hwnd, TEXT(" "), TEXT(" "), MB_OK);
			rectFlagDx1.right = rectFlagDx1.left + flagLenInc;
			hBrush = CreateSolidBrush(RGB(255, 153, 51));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rectFlagDx1, hBrush);
		}
		else {
			flagLenInc = 0;
			sOneFlagComplete = 1;
		}
	}
	else if (!sTwoFlagComplete) {
		if (rectFlagDx2.right <= flagEnd) {
			//MessageBox(hwnd, TEXT(" "), TEXT(" "), MB_OK);
			rectFlagDx2.right = rectFlagDx2.left + flagLenInc;
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rectFlagDx2, hBrush);
		}
		else {
			flagLenInc = 0;
			sTwoFlagComplete = 1;
		}
	}
	else if (!sThreeFlagComplete){
		if (rectFlagDx3.right <= flagEnd) {
			//MessageBox(hwnd, TEXT(" "), TEXT(" "), MB_OK);
			rectFlagDx3.right = rectFlagDx3.left + flagLenInc;
			hBrush = CreateSolidBrush(RGB(19, 136, 8));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rectFlagDx3, hBrush);
		}
		else {
			sThreeFlagComplete = 1;
		}
	}

	flagLenInc += 10;

	if (sOneFlagComplete && sTwoFlagComplete && sThreeFlagComplete) {
		KillTimer(hwnd, MYTIMER3);
		ReleaseDC(hwnd, hdc);
		SetTimer(hwnd, MYTIMER4, TIME4, MyTimerProc4);
	}
	else {
		SetTimer(hwnd, MYTIMER3, TIME3, MyTimerProc3);
	}
	
	
}


void CALLBACK MyTimerProc4(HWND hwnd, UINT iMsg, UINT_PTR timerEvent, DWORD ms) {
	KillTimer(hwnd, MYTIMER3);
	static HBRUSH hBrush;
	hdc = GetDC(hwnd);
	POINT apt[NUM];
	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(135, 0, 255));
	SelectObject(hdc, hPen);

	for (int i = 0; i < NUM; i++)
	{
		apt[i].x = i * poleLeft / NUM;
		apt[i].y = (int)((gPole.top + (10 * yFact)) / 2 * (1 - sin(TWOPI * i / NUM)));
	}
	Polyline(hdc, apt, NUM);
	ReleaseDC(hwnd, hdc);
}