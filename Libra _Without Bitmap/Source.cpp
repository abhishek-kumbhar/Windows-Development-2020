

#include <windows.h>
#include <stdio.h>
#include <time.h> 

#define MYTIMER 1000
#define TIME  400


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK DrawDotsTimerProc(HWND, UINT, UINT_PTR, DWORD);

void MakeStar(RECT*, POINT*);
void MakeLibra(RECT*, POINT*);
void ChangeStarBoxesDimentions(RECT*, int, int, int, int, char);
void MakeStarBoxes(RECT*);
void BuildStars(RECT*, POINT[][10]);
void DrawLibra(HDC);
void DrawDots(HDC);


RECT gRect;
FILE *gfPtr;
POINT libra[8], pArray[8][10];
HWND ghwnd;
HDC hdc;
int tFlag = 1;


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
		TEXT("Libra _Abhishek Kumbhar"),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		800,
		800,
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



void MakeStar(RECT *r, POINT *p) {

	static int xFact, yFact;

	fprintf(gfPtr, "\nIn MakeStar : left = %d, top = %d, right = %d, bottom = %d, ", r->left, r->top, r->right, r->bottom);

	xFact = (r->right - r->left) / 8;
	yFact = (r->bottom - r->top) / 8;

	fprintf(gfPtr, "xFact = %d, yFact = %d\n\n", xFact, yFact);

	if (xFact > yFact) {
		int diff = xFact - yFact;
		r->left = r->left + (diff / 2);
		r->right = r->right - (diff / 2);
		xFact = yFact;
	}
	else {
		int diff = yFact - xFact;
		r->top = r->top + (diff / 2);
		r->bottom = r->bottom - (diff / 2);
		yFact = xFact;
	}


	(*(p + 0)).x = r->left + xFact / 4;
	(*(p + 0)).y = r->top + (2.5 * yFact);
	(*(p + 1)).x = r->left + (3 * xFact);
	(*(p + 1)).y = r->top + (2.5 * yFact);
	(*(p + 2)).x = r->left + (4 * xFact);
	(*(p + 2)).y = r->top;
	(*(p + 3)).x = r->left + (4 * xFact) + 0.75 * xFact;
	(*(p + 3)).y = r->top + (2.5 * yFact);
	(*(p + 4)).x = r->left + (7 * xFact) + 0.5 * xFact;
	(*(p + 4)).y = r->top + (2.5 * yFact);
	(*(p + 5)).x = r->left + (5 * xFact) + 0.25 * xFact;
	(*(p + 5)).y = r->top + (4 * yFact);
	(*(p + 6)).x = r->left + (6 * xFact) + 0.25 * xFact;
	(*(p + 6)).y = r->top + (7 * yFact);
	(*(p + 7)).x = r->left + (4 * xFact) - xFact / 4;
	(*(p + 7)).y = r->top + (5 * yFact) + 0.10 * yFact; 
	(*(p + 8)).x = r->left + xFact + (xFact / 4);
	(*(p + 8)).y = r->top + (7 * yFact);
	(*(p + 9)).x = r->left + (2 * xFact) + 0.25 * xFact;
	(*(p + 9)).y = r->top + (4 * yFact);
	
}

void MakeLibra(RECT *r, POINT *p) {
	
	static int xFact, yFact;

	xFact = (r->right - r->left) / 5;
	yFact = (r->bottom - r->top) / 5;


	if (xFact > yFact) {
		int diff = xFact - yFact;
		r->left = r->left + (diff / 2);
		r->right = r->right - (diff / 2);
		xFact = yFact;
	}
	else {
		int diff = yFact - xFact;
		r->top = r->top + (diff / 2);
		r->bottom = r->bottom - (diff / 2);
		yFact = xFact;
	}

	(*(p + 0)).x = r->left;
	(*(p + 0)).y = r->top + (1 * yFact);
	(*(p + 1)).x = r->left + (xFact / 4);
	(*(p + 1)).y = r->top + (1.5 * yFact);
	(*(p + 2)).x = r->left + (1.5 * xFact);
	(*(p + 2)).y = r->top + (1 * yFact);
	(*(p + 3)).x = r->left + (2.5 * xFact);
	(*(p + 3)).y = r->top;
	(*(p + 4)).x = r->left + (4 * xFact) + (xFact / 4);
	(*(p + 4)).y = r->top + (1 * yFact);
	(*(p + 5)).x = r->left + (3 * xFact) + (xFact / 2);
	(*(p + 5)).y = r->top + (3 * yFact) + (yFact / 4);
	(*(p + 6)).x = r->left + (1 * xFact) + (0.2 * xFact);
	(*(p + 6)).y = r->top + (4 * yFact) + (0.1 * yFact);
	(*(p + 7)).x = r->left + (1 * xFact);
	(*(p + 7)).y = r->top + (4 * yFact) + 0.7 * yFact;

}


void ChangeStarBoxesDimentions(RECT *libraStarSingleBox, int l, int t, int r, int b, char ch) {
	if (ch == '+') {
		libraStarSingleBox->left = libraStarSingleBox->left - l;
		libraStarSingleBox->top = libraStarSingleBox->top - t;
		libraStarSingleBox->right = libraStarSingleBox->right + r;
		libraStarSingleBox->bottom = libraStarSingleBox->bottom + b;

	}
	else {
		libraStarSingleBox->left = libraStarSingleBox->left + l;
		libraStarSingleBox->top = libraStarSingleBox->top + t;
		libraStarSingleBox->right = libraStarSingleBox->right - r;
		libraStarSingleBox->bottom = libraStarSingleBox->bottom - b;
	
	}
	
}



void MakeStarBoxes(RECT libraStarBoxes[]) {

	for (int i = 0; i < 8; i++) {
		libraStarBoxes[i].left = libra[i].x - 20;
		libraStarBoxes[i].top = libra[i].y - 20;
		libraStarBoxes[i].right = libra[i].x + 20;
		libraStarBoxes[i].bottom = libra[i].y + 20;
	}

	ChangeStarBoxesDimentions(&libraStarBoxes[0], 7, 7, 7, 7, '-');
	ChangeStarBoxesDimentions(&libraStarBoxes[7], 7, 7, 7, 7, '-');
	ChangeStarBoxesDimentions(&libraStarBoxes[3], 10, 10, 10, 10, '+');

}

void BuildStars(RECT libraStarBoxes [], POINT pArray[][10]) {
	for (int i = 0; i < 8; i++) {
		MakeStar(&libraStarBoxes[i], pArray[i]);
	}

}


void DrawLibra(HDC hdc) {

	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0,255,0));
	SelectObject(hdc, hPen);

	MoveToEx(hdc, libra[0].x, libra[0].y, NULL);
	for (int i = 1; i < 8; i++) {
		LineTo(hdc, libra[i].x, libra[i].y);
	}
	MoveToEx(hdc, libra[3].x, libra[3].y, NULL);
	LineTo(hdc, libra[5].x, libra[5].y);

	DeleteObject(SelectObject(hdc, GetStockObject(DC_PEN)));

}

void DrawStars(HDC hdc) {
	
	SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
	SetPolyFillMode(hdc, ALTERNATE);
		
	for (int i = 0; i < 8; i++) {
		Polygon(hdc, pArray[i], 10);
	}
}

void DrawDots(HDC hdc) {
	srand(time(0));
	static int flag = 1;
	if (flag) {
		for (int i = 0; i < 5000; i++) {
			SetPixel(hdc, rand() % (gRect.right), rand() % (gRect.bottom), RGB(rand() % 255, rand() % 255, rand() % 255));
		}
		flag = 0;
	}
	else {
		for (int i = 0; i < 3000; i++) {
			SetPixel(hdc, rand() % (gRect.right), rand() % (gRect.bottom), RGB(255, 255, 255));
		}
		flag = 1;
	}
}





LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	ghwnd = hwnd;	
	PAINTSTRUCT ps;
	static RECT rs, rs1;
	static RECT libraStarBoxes[8];
	

	switch (iMsg) {

	case WM_CREATE :
		ghwnd = hwnd;
		GetClientRect(hwnd, &gRect);
		fopen_s(&gfPtr, "Co-Ordinates.txt", "w");

		SetTimer(hwnd, MYTIMER, TIME, NULL);
		
		break;	

	case WM_LBUTTONDOWN :
		if (tFlag == 1) {
			tFlag = 0;
		}
		else {
			tFlag = 1;
		}
		break;

	case WM_TIMER:
		KillTimer(hwnd, MYTIMER);
		InvalidateRect(hwnd, &rs1, TRUE);
		if (tFlag == 1) {
			SetTimer(hwnd, MYTIMER, TIME, NULL);
		}
		else {
			SetTimer(hwnd, MYTIMER, USER_TIMER_MINIMUM, NULL);
		}
		
		break;

	case WM_SIZE :
		
		GetClientRect(hwnd, &gRect);

		fprintf(gfPtr, "In WM_SIZE : left = %d, top = %d, right = %d, bottom = %d\n\n\n", gRect.left, gRect.top, gRect.right, gRect.bottom);
		rs1.left =  gRect.left;
		rs1.top = gRect.top;
		rs1.right = gRect.right;
		rs1.bottom = gRect.bottom;
	
		rs.left = gRect.left + 450;
		rs.top = gRect.top + 100;
		rs.right = gRect.right;
		rs.bottom = gRect.bottom;
		
		MakeLibra(&rs, libra);
		MakeStarBoxes(libraStarBoxes);
		BuildStars(libraStarBoxes, pArray);

		break;

	case WM_PAINT :

		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &gRect);
		
		DrawLibra(hdc);
		DrawStars(hdc);
		DrawDots(hdc);
		

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY :
		
		fclose(gfPtr);
		PostQuitMessage(0);
		break;
	
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}


