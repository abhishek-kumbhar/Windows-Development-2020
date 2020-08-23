

#include<windows.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<Mmsystem.h>		//Winmm.lib


#define MYTIMER 1000
#define MYTIMER2 1001
#define MYTIMER3 1002
#define MYTIMER4 1003
#define MYTIMER5 1004
#define MYTIMER6 1005

#define TIME 35				// 35
#define TIME2 100			// 100
#define TIME3 100			// 100
#define TIME4 100
#define TIME5 100
#define TIME6 100


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void CALLBACK MyTimerProc(HWND, UINT, UINT_PTR, DWORD);
void CALLBACK MyTimerProc2(HWND, UINT, UINT_PTR, DWORD);
void CALLBACK MyTimerProc3(HWND, UINT, UINT_PTR, DWORD);
void CALLBACK MyTimerProc4(HWND, UINT, UINT_PTR, DWORD);
void CALLBACK MyTimerProc5(HWND, UINT, UINT_PTR, DWORD);
void CALLBACK MyTimerProc6(HWND, UINT, UINT_PTR, DWORD);

BOOL AshokaChakraDrawn(HWND, int);


// org   RGB(255, 153, 51)
// white RGB(255, 255, 255)
// green RGB(19, 136, 8)
// blue  RGB(0, 0, 128)


RECT gRect, gSteps[3], gPole;
HDC hdc;
int xFact, yFact;
int poleWidth;
FILE* fp;

POINT chakraPoints[24];
RECT chakraRect;

// Omkar's Variables
RECT inviRect;
static POINT* ptsOne = NULL;
static POINT* ptsTwo = NULL;
static float scale;
static float waveLength;
int flagStartX;
int flagEndX;
int drawFlag;

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

void MakeAshokaChakra() {
	static int xF = (chakraRect.right - chakraRect.left) / 10;
	static int yF = (chakraRect.bottom - chakraRect.top) / 10;

	fprintf(fp, "\n\n\nin fun\ncLeft = %d\ncTop = %d\ncRight = %d\ncBottom = %d\n\n", chakraRect.left, chakraRect.top, chakraRect.right, chakraRect.bottom);


	chakraPoints[0].x =   5 * xF + chakraRect.left;					chakraPoints[0].y = 0        + chakraRect.top;
	chakraPoints[1].x = 6.4 * xF + chakraRect.left;					chakraPoints[1].y = 0.3 * yF + chakraRect.top;
	chakraPoints[2].x = 7.7 * xF + chakraRect.left;					chakraPoints[2].y = 0.7 * yF + chakraRect.top;
	chakraPoints[3].x = 8.6 * xF + chakraRect.left;					chakraPoints[3].y = 1.5 * yF + chakraRect.top;
	chakraPoints[4].x = 9.4 * xF + chakraRect.left;					chakraPoints[4].y = 2.5 * yF + chakraRect.top;
	chakraPoints[5].x = 9.9 * xF + chakraRect.left;					chakraPoints[5].y = 3.8 * yF + chakraRect.top;
	chakraPoints[6].x = 10 *  xF + chakraRect.left;					chakraPoints[6].y =   5 * yF + chakraRect.top;

	chakraPoints[7].x  = 9.9 * xF + chakraRect.left;				chakraPoints[7].y = 6.3 * yF + chakraRect.top;
	chakraPoints[8].x  = 9.4 * xF + chakraRect.left;				chakraPoints[8].y = 7.5 * yF + chakraRect.top;
	chakraPoints[9].x  = 8.6 * xF + chakraRect.left;				chakraPoints[9].y = 8.5 * yF + chakraRect.top;
	chakraPoints[10].x = 7.5 * xF + chakraRect.left;				chakraPoints[10].y = 9.3 * yF + chakraRect.top;
	chakraPoints[11].x = 6.4 * xF + chakraRect.left;				chakraPoints[11].y = 9.8 * yF + chakraRect.top;
	chakraPoints[12].x =   5 * xF + chakraRect.left;				chakraPoints[12].y = 10 * yF + chakraRect.top;

	chakraPoints[13].x = 3.7 * xF + chakraRect.left;				chakraPoints[13].y = 9.8 * yF + chakraRect.top;
	chakraPoints[14].x = 2.5 * xF + chakraRect.left;				chakraPoints[14].y = 9.4 * yF + chakraRect.top;
	chakraPoints[15].x = 1.5 * xF + chakraRect.left;				chakraPoints[15].y = 8.5 * yF + chakraRect.top;
	chakraPoints[16].x = 0.6 * xF + chakraRect.left;				chakraPoints[16].y = 7.5 * yF + chakraRect.top;
	chakraPoints[17].x = 0.1 * xF + chakraRect.left;				chakraPoints[17].y = 6.2 * yF + chakraRect.top;
	chakraPoints[18].x = 0        + chakraRect.left;				chakraPoints[18].y =   5 * yF + chakraRect.top;

	chakraPoints[19].x = 0.2 * xF + chakraRect.left;				chakraPoints[19].y = 3.6 * yF + chakraRect.top;
	chakraPoints[20].x = 0.6 * xF + chakraRect.left;				chakraPoints[20].y = 2.5 * yF + chakraRect.top;
	chakraPoints[21].x = 1.5 * xF + chakraRect.left;				chakraPoints[21].y = 1.5 * yF + chakraRect.top;
	chakraPoints[22].x = 2.5 * xF + chakraRect.left;				chakraPoints[22].y = 0.7 * yF + chakraRect.top;
	chakraPoints[23].x = 3.7 * xF + chakraRect.left;				chakraPoints[23].y = 0.2 * yF + chakraRect.top;

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HBRUSH hBrush;
	HPEN hPen;

	switch (iMsg) {

	case WM_CREATE : 

		SetTimer(hwnd, MYTIMER, TIME, MyTimerProc);


		fp = fopen("file.txt", "w");

		// Omkars Code
		scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
		waveLength = -0.01 + scale * (0.01 - (-0.01));      /* [min, max] */

 
		ptsOne = (POINT*)malloc(sizeof(POINT) * (flagEndX - flagStartX));
		ptsTwo = (POINT*)malloc(sizeof(POINT) * (flagEndX - flagStartX));


		break;

	case WM_SIZE :
		GetClientRect(hwnd, &gRect);
		xFact = gRect.right / 20;
		yFact = gRect.bottom / 20;
		MakeSteps();
		MakePole();
		//MakeAshokaChakra();		// call @ downSide

		break;

	case WM_PAINT :
		GetClientRect(hwnd, &gRect);
		
		hdc = BeginPaint(hwnd, &ps);
		

		if (drawFlag == 1) {

			hPen = (HPEN)GetStockObject(NULL_PEN);
			SelectObject(hdc, hPen);

			hBrush = CreateSolidBrush(RGB(255, 153, 51));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &inviRect, hBrush);

			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);

			Polygon(hdc, ptsOne, (flagEndX - flagStartX));

			hBrush = CreateSolidBrush(RGB(19, 136, 8));
			SelectObject(hdc, hBrush);

			Polygon(hdc, ptsTwo, (flagEndX - flagStartX));
			
			AshokaChakraDrawn(hwnd, FALSE);
		}


		EndPaint(hwnd, &ps);
		break;

	case WM_TIMER :
		break;

	case WM_DESTROY :
		fclose(fp);
		if (ptsOne) {
			free(ptsOne);
			ptsOne = NULL;
		}

		if (ptsTwo) {
			free(ptsTwo);
			ptsTwo = NULL;
		}

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


void CALLBACK MyTimerProc(HWND hwnd, UINT iMsg, UINT_PTR timerEvent, DWORD ms) {

	KillTimer(hwnd, MYTIMER);

	static HBRUSH hBrush;
	hdc = GetDC(hwnd);

	static int x = 1;
	static int sOneStepComplete = 0, sTwoStepComplete = 0, sThreeStepComplete = 0;

	if (x) {

		Sleep(100);
		PlaySound(TEXT("sound1.wav"), NULL, SND_FILENAME | SND_ASYNC);


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
			hBrush = CreateSolidBrush(RGB(95, 0, 95));
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
			hBrush = CreateSolidBrush(RGB(95, 0, 135));
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
			hBrush = CreateSolidBrush(RGB(95, 0, 175));
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
		rectPole.right = rectPole.right + (poleWidth / 2);

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


RECT rectFlagDx1, rectFlagDx2, rectFlagDx3;
int flagEnd;
int flagLenInc;

int chakraMid, chakraWidth;

POINT midPoint;
int flagDivider;

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

		flagEndX = flagEnd;
		flagStartX = poleRight;

		ptsOne = (POINT*)malloc(sizeof(POINT) * (flagEndX - flagStartX));
		ptsTwo = (POINT*)malloc(sizeof(POINT) * (flagEndX - flagStartX));
		
		
		flagDivider = (flagEndX - flagStartX) / 10;

		
		SetTimer(hwnd, MYTIMER6, TIME6, MyTimerProc6);
		
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

		inviRect.left = rectFlagDx1.left;
		inviRect.top = gPole.top;
		inviRect.right = rectFlagDx3.right;
		inviRect.bottom = rectFlagDx3.bottom;
		drawFlag = 1;
		

		//chakraRect.left = rectFlagDx2.left;
		chakraRect.top = rectFlagDx2.top;
		//chakraRect.right = rectFlagDx2.right;
		chakraRect.bottom = rectFlagDx2.bottom;
		
		fprintf(fp, "\n\ndx1.l = %d\tdx1.t = %d\tdx1.r = %d\tdx1.b = %d\n", rectFlagDx1.left, rectFlagDx1.top, rectFlagDx1.right, rectFlagDx1.bottom);
		fprintf(fp, "dx2.l = %d\tdx2.t = %d\tdx2.r = %d\tdx2.b = %d\n", rectFlagDx2.left, rectFlagDx2.top, rectFlagDx2.right, rectFlagDx2.bottom);
		fprintf(fp, "dx3.l = %d\tdx3.t = %d\tdx3.r = %d\tdx3.b = %d\n", rectFlagDx3.left, rectFlagDx3.top, rectFlagDx3.right, rectFlagDx3.bottom);

		fprintf(fp, "\ncLeft = %d\ncTop = %d\ncRight = %d\ncBottom = %d\n\n", chakraRect.left, chakraRect.top, chakraRect.right, chakraRect.bottom);


		chakraMid = (rectFlagDx2.right + rectFlagDx2.left) / 2;
		chakraWidth = (rectFlagDx2.bottom - rectFlagDx2.top);
	
		chakraRect.left = chakraMid - (chakraWidth / 2);
		chakraRect.right = chakraMid + (chakraWidth / 2);;
		
		midPoint.x = (chakraRect.right + chakraRect.left) / 2;
		midPoint.y = (chakraRect.bottom + chakraRect.top) / 2;

		fprintf(fp, "mid = %d\nwidth = %d\ncLeft = %d\ncTop = %d\ncRight = %d\ncBottom = %d\nmp.X = %d\nmp.Y = %d\n", chakraMid, chakraWidth,
			chakraRect.left, chakraRect.top, chakraRect.right, chakraRect.bottom, midPoint.x, midPoint.y);

	

		SetTimer(hwnd, MYTIMER4, TIME4, MyTimerProc4);
	}
	else {
		SetTimer(hwnd, MYTIMER3, TIME3, MyTimerProc3);
	}
	
	
}


RECT rectDots;

void CALLBACK MyTimerProc6(HWND hwnd, UINT iMsg, UINT_PTR timerEvent, DWORD ms) {
	KillTimer(hwnd, MYTIMER6);
	static HBRUSH hBrush;
	hdc = GetDC(hwnd);
	static int sOneDotComplete = 0, sTwoDotComplete = 0, sThreeDotComplete = 0;
	static int x = 1;
	static int right = flagDivider;		//temp variable


	// org   RGB(255, 153, 51)
// white RGB(255, 255, 255)
// green RGB(19, 136, 8)
	if (!sOneDotComplete) {
		if (rectDots.right <= gRect.right) {
			rectDots.left = gRect.left;
			rectDots.top = gRect.top;
			rectDots.right = right;
			rectDots.bottom = gRect.bottom / 3 * 1;
			
			for (int i = 0; i < 100; i++) {
				SetPixel(hdc, rand() % rectDots.right, rand() % rectDots.bottom, RGB(255, 153, 51));
			}
		}
		else {
			sOneDotComplete = 1;
			right = flagDivider;			//right = 0;
			rectDots.right = right;
		}
	}
	else if (!sTwoDotComplete) {
		if (rectDots.right <= gRect.right) {
			rectDots.left = gRect.left;
			rectDots.top = gRect.bottom / 3 * 1;
			rectDots.right = right;
			rectDots.bottom = gRect.bottom / 3 * 2;

			for (int i = 0; i < 100; i++) {
				SetPixel(hdc, rand() % rectDots.right, (rand() % (rectDots.bottom - rectDots.top)) + rectDots.top, RGB(255, 255, 255));
			}
		}
		else {
			sTwoDotComplete = 1;
			right = flagDivider;
			rectDots.right = right;
			
		}
	}
	else if (!sThreeDotComplete) {
		if (rectDots.right <= gRect.right) {
			rectDots.left = gRect.left;
			rectDots.top = gRect.bottom / 3 * 2;
			rectDots.right = right;
			rectDots.bottom = gRect.bottom;

			for (int i = 0; i < 100; i++) {
				SetPixel(hdc, rand() % rectDots.right, (rand() % (rectDots.bottom - rectDots.top)) + rectDots.top, RGB(19, 136, 8));
			}
		}
		else {
			sThreeDotComplete = 1;
		}
	}
	
	right += flagDivider / 1.2;

	if (sOneDotComplete && sTwoDotComplete && sThreeDotComplete) {
		KillTimer(hwnd, MYTIMER6);
		ReleaseDC(hwnd, hdc);
	}
	else {
		SetTimer(hwnd, MYTIMER6, TIME6, MyTimerProc6);
	}


}

BOOL AshokaChakraDrawn(HWND hwnd, BOOL flag) {
	static HBRUSH hBrush;
	hdc = GetDC(hwnd);
	static int x = 1;
	static HPEN hPen;

	if (x) {
		x = 0;
		MakeAshokaChakra();
	}

	hPen = CreatePen(PS_SOLID, 6, RGB(0, 0, 128));
	SelectObject(hdc, hPen);
	Ellipse(hdc, chakraRect.left, chakraRect.top, chakraRect.right, chakraRect.bottom);

	hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 128));
	for (int i = 0; i < 24; i++) {
		MoveToEx(hdc, midPoint.x, midPoint.y, NULL);
		SelectObject(hdc, hPen);
		LineTo(hdc, chakraPoints[i].x, chakraPoints[i].y);
		
		if (flag) {
			Sleep(300);
		}
	}
	return TRUE;
}


void CALLBACK MyTimerProc4(HWND hwnd, UINT iMsg, UINT_PTR timerEvent, DWORD ms) {
	KillTimer(hwnd, MYTIMER4);

	BOOL isDrawn;

	isDrawn = AshokaChakraDrawn(hwnd, TRUE);

	if (isDrawn) {
		Sleep(200);
		PlaySound(TEXT("sound2.wav"), NULL, SND_FILENAME | SND_ASYNC);

		SetTimer(hwnd, MYTIMER5, TIME5, MyTimerProc5);
	}
}


void CALLBACK MyTimerProc5(HWND hwnd, UINT iMsg, UINT_PTR timerEvent, DWORD ms) {
	static float inc = 0.005;
	KillTimer(hwnd, MYTIMER5);

	for (int i = 0; i < (flagEndX - flagStartX - 3); i++) {
		ptsOne[i].x = flagStartX + i;
		ptsOne[i].y = rectFlagDx1.bottom + sin(i * waveLength + inc) * 15;
		inc += 0.001;
	}

	ptsOne[(flagEndX - flagStartX - 3)].x = rectFlagDx3.right; // x8
	ptsOne[(flagEndX - flagStartX - 3)].y = rectFlagDx3.bottom;	   // y8

	ptsOne[(flagEndX - flagStartX - 2)].x = rectFlagDx3.left;					// x7
	ptsOne[(flagEndX - flagStartX - 2)].y = rectFlagDx3.bottom;	// y7

	ptsOne[(flagEndX - flagStartX - 1)].x = ptsOne[0].x;		// x3
	ptsOne[(flagEndX - flagStartX - 1)].y = ptsOne[0].y;		// y3

	for (int i = 0; i < (flagEndX - flagStartX - 3); i++) {
		ptsTwo[i].x = ptsOne[i].x;
		ptsTwo[i].y = ptsOne[i].y + 100;

	}
	ptsTwo[(flagEndX - flagStartX - 3)].x = rectFlagDx3.right; // x8
	ptsTwo[(flagEndX - flagStartX - 3)].y = rectFlagDx3.bottom;     // y8

	ptsTwo[(flagEndX - flagStartX - 2)].x = rectFlagDx3.left;			// x7
	ptsTwo[(flagEndX - flagStartX - 2)].y = rectFlagDx3.bottom;  // y7

	ptsTwo[(flagEndX - flagStartX - 1)].x = ptsTwo[0].x;
	ptsTwo[(flagEndX - flagStartX - 1)].y = ptsTwo[0].y;

	InvalidateRect(hwnd, &inviRect, TRUE);
	SetTimer(hwnd, MYTIMER5, TIME5, MyTimerProc5);

}



