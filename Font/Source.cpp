# include <windows.h>
# include <Mmsystem.h>
# include <stdio.h>
//# include "Source.h"
# define MYTIMER 1000
# define TIME 3000

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX	wndClass;
	HWND hWnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Demo");

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
		TEXT("AMC Bitmap Demo"),
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


static TCHAR str[] = TEXT("विजय");
static int i = -2;
FILE* fPtr = NULL;
static TCHAR ch[10];
static int l, r;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {

	case WM_CREATE : 
		fopen_s(&fPtr, "abc.txt", "w");
		
		break;

	case WM_LBUTTONDOWN:
		SetTimer(hWnd, MYTIMER, TIME, NULL);
		//PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
    {
        RECT rect;
        HFONT hFont;
        hdc = BeginPaint(hWnd, &ps);

        hFont = CreateFont(250, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_RASTER_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Mangal Bold"));
        SelectObject(hdc, hFont);
	    SetRect(&rect, l, 100, r, 200);
		SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(255, 0, 0));
		wsprintf(ch, TEXT("%c"), str[i]);
        DrawText(hdc, ch, -1, &rect, DT_NOCLIP | DT_CENTER);

        DeleteObject(hFont);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
		fclose(fPtr);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}