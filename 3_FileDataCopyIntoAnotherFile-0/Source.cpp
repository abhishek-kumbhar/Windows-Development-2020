

# include <windows.h>
# include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Demo");

	wndclass.cbSize = sizeof(WNDCLASSEX);
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
		TEXT("File Handling Very Simple Demo"),
		WS_OVERLAPPEDWINDOW,
		400,
		300,
		1000,
		700,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);

}


FILE * gfPtr = NULL, * gfPtr2 = NULL;
static int retValMsgBoxArr[10];
static char buffer[100];

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static TCHAR str[255];
	char ch;
	int i = 0;
	switch (iMsg) {
		case WM_CREATE :
			fopen_s(&gfPtr, "fileOne.txt", "r");
			fopen_s(&gfPtr2, "fileTwo.txt", "w");
			if (gfPtr && gfPtr2) {
				//wsprintf(str, TEXT("Address of gfPtr = %p"), gfPtr);
				//MessageBox(hwnd, str, TEXT(" "), MB_OK);
				MessageBox(hwnd, TEXT("File is Opened Succesfully..."), TEXT("Message"), MB_OK | MB_ICONINFORMATION);
			}
			
			break;

		case WM_LBUTTONDOWN : 
			retValMsgBoxArr[0] = MessageBox(hwnd, TEXT("Do you want to read data from text file ?"), TEXT("Message"), MB_YESNO | MB_ICONINFORMATION);
			
			if (retValMsgBoxArr[0] == 6) {
				ch = fgetc(gfPtr);
				while (ch != EOF) {
					str[i++] = ch;
					ch = fgetc(gfPtr);
				}
				str[i] = '\0';
				fclose(gfPtr);
				MessageBox(hwnd, TEXT("Data read Succesfully..."), TEXT(" "), MB_OK);
			} else if (retValMsgBoxArr[0] == 2) {
				MessageBox(hwnd, TEXT("Cancel Button pressed"), TEXT(" "), MB_OK);
			}
			break;

		case WM_RBUTTONDOWN :
			retValMsgBoxArr[1] = MessageBox(hwnd, TEXT("Do you want to write data into another text file ?"), TEXT("Message"), MB_YESNO | MB_ICONINFORMATION);
			i = 0;
			if (retValMsgBoxArr[1] == 6) {
				while (str [i] != '\0') {
					fputc(str[i], gfPtr2);
					i++;
				}
				fclose(gfPtr2);
				MessageBox(hwnd, TEXT("Data written Succesfully..."), TEXT(" "), MB_OK);
			}

			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}



