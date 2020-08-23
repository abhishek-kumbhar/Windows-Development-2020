
# include <windows.h>
# include <Mmsystem.h>
# include <stdio.h>
# include "Source.h"
# define MYTIMER 1000
# define TIME 8000


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int flag = -2;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX	wndClass;
	HWND hWnd;
	MSG msg;
	TCHAR szAppName[] = TEXT ("Demo");
	
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(szAppName,
		TEXT("AMC Bitmap Demo  - Abhishek Kumbhar"),
		WS_OVERLAPPEDWINDOW|WS_MAXIMIZE,
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


static TCHAR str[] = TEXT("ASTROMEDICOMP");
static int i = -2;
FILE* fPtr = NULL;
static TCHAR ch[10];
static int l, r;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HBITMAP hbitmap;
	BITMAP bitmap;
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rc, rect;
	static HINSTANCE hInstance;
		
	switch (iMsg) {
	
	case WM_CREATE :
		fopen_s(&fPtr, "abc.txt", "w");
		hInstance = GetModuleHandle(NULL);
		break;

	case WM_LBUTTONDOWN:
		SetTimer(hWnd, MYTIMER, TIME, NULL);
		//PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		//Winmm.lib
		fprintf(fPtr, "%c\n", str[i]);
		i++;
		break;
	
	case WM_TIMER :
		KillTimer(hWnd, MYTIMER);
		i++;
		if (!(str[i] == '\0')) {
			l += 173;
			r += 100;
			InvalidateRect(hWnd, NULL, FALSE);
			SetTimer(hWnd, MYTIMER, TIME, NULL);
		}
		break;

	case WM_PAINT : 
	    
		HFONT hFont;

		GetClientRect(hWnd, &rc);
		hdc = BeginPaint(hWnd, &ps);
		
		hbitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
		hdcMem = CreateCompatibleDC(NULL);
		SelectObject(hdcMem, hbitmap);
		GetObject(hbitmap, sizeof(BITMAP), &bitmap);
		StretchBlt(hdc, 0, 330, rc.right, rc.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);




		hFont = CreateFont(250, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_RASTER_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
        SelectObject(hdc, hFont);
	    SetRect(&rect, l, 100, r, 200);
		SetBkColor(hdc, RGB(0, 0, 0));

		if (flag < 5) {
			flag = flag + 1;
			SetTextColor(hdc, RGB(255, 153, 51));
		}
		else if (flag < 9) {
			flag = flag + 1;
			SetTextColor(hdc, RGB(255, 255, 255));
		}
		else {
			flag = flag + 1;
			SetTextColor(hdc, RGB(19, 136, 8));
		}
		

        
		wsprintf(ch, TEXT("%c"), str[i]);
        DrawText(hdc, ch, -1, &rect, DT_NOCLIP | DT_CENTER);
		



		DeleteObject(hFont);

		DeleteObject(hbitmap);
		DeleteObject(hdcMem);

		EndPaint(hWnd, &ps);

		break;

	case WM_DESTROY :
		fclose(fPtr);
		PostQuitMessage(0);
		break;

	}

	return (DefWindowProc (hWnd, iMsg, wParam, lParam));
}





