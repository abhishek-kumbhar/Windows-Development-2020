
# include <windows.h>
# include <Mmsystem.h>
# include <stdio.h>
# include <sapi.h>
# include "Source.h"
# define MYTIMER 1000
# define TIME 2500 


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int flag = -2;

ISpVoice* pVoice = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

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
		TEXT("India Pledge demo  - Abhishek Kumbhar"),
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

static TCHAR word[100];
static TCHAR* wptr = NULL;
static int index = 0;
static int wIndex = 0;
static int cnt = -2;



static char pledge[13][50] = {
	{"India is my country ."},
	{"All Indians are my brothers and sisters ."},
	{"I love my country ."},
	{"I am proud of its rich and varied heritage ."},
	{"I shall always strive to be worthy of it ."},
	{"I shall give my parents, ."},
	{"teachers and all elders, respect ."},
	{"and treat everyone with courtesy ."},
	{"To my country and my people, ."},
	{"I pledge my devotion ."},
	{"In their well being ."},
	{"and prosperity alone, lies my happiness ."},
	{"JAY HIND ."}
};





static int i = -2;
static int row = 0;
FILE* fPtr = NULL;
static TCHAR ch[10];
static int l, r;
static HFONT hFont;
static int iter = 0;
static TCHAR* curWord = NULL;
static int yInc = 100;

static SIZE strSize;
static int xStart, yStart;



void getWord(int cnt) {

	while (pledge[cnt][iter] != '.') {
		word[wIndex++] = pledge[cnt][iter++];
	}
	word[wIndex] = '\0';
	wIndex = 0;
	iter = 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	static HINSTANCE hInstance;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	TCHAR final[200] = L"<pitch middle = '10'/><rate speed='2'>";
	

		
	switch (iMsg) {
	

	case WM_CREATE :

		fopen_s(&fPtr, "abc.txt", "w");
		hInstance = GetModuleHandle(NULL);

		hFont = CreateFont(50, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_RASTER_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Impact"));

		break;

	case WM_TIMER:
		KillTimer(hWnd, MYTIMER);
		
		//MessageBox(hWnd, TEXT("black"), TEXT(" inpaint"), MB_OK);

		fprintf(fPtr, "%S  ", word);
		fprintf(fPtr, "%d\n", cnt);

		InvalidateRect(hWnd, NULL, FALSE);


		SetTimer(hWnd, MYTIMER, TIME, NULL);
		break;

	case WM_KEYDOWN :

		SetTimer(hWnd, MYTIMER, TIME, NULL);
		break;


	case WM_PAINT : 

		GetClientRect(hWnd, &rc);
		hdc = BeginPaint(hWnd, &ps);

		getWord(cnt++);

		GetTextExtentPoint32(hdc, word, wcslen(word), &strSize);

		xStart = (rc.right / 2) - strSize.cx;

		fprintf(fPtr, "\nxstart = %d rc.right = %d  rc.left = %d str.cx = %d----->\n", xStart, rc.right, rc.left, strSize.cx);

		yStart += 50;

        SelectObject(hdc, hFont);
		SetBkColor(hdc, RGB(0, 0, 0));

		if (cnt < 5) {
			SetTextColor(hdc, RGB(255, 153, 51));
		}
		else if (cnt < 9) {
			SetTextColor(hdc, RGB(255, 255, 255));
		}
		else {
			SetTextColor(hdc, RGB(19, 136, 8));
		}
	


		
		wsprintf(ch, TEXT("%S"), word);

		TextOut(hdc, xStart, yStart, word, wcslen(word));



		wcscat_s(final, word);
		hr = pVoice->Speak(final, 0, NULL);
		pVoice->Release();
		
		


		EndPaint(hWnd, &ps);

		break;

	case WM_DESTROY :

		DeleteObject(hFont);
		
		pVoice = NULL;
		::CoUninitialize();
		
		fclose(fPtr);
		PostQuitMessage(0);
		break;

	}

	return (DefWindowProc (hWnd, iMsg, wParam, lParam));
}





