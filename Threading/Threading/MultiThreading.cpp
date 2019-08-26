
#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MultiThreading");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//UnRegisterClassEx(&wndclass);
	RegisterClassEx(&wndclass);
	//RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("MultiThreading"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	PAINTSTRUCT ps;
	HDC hdc;
	//TCHAR str[255] = TEXT("MultiThreading");
	
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;
	TCHAR str[255] = TEXT("MultiThreading Application Running");

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:/*
		GetClientRect(hwnd, &rect);
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, RGB(0, 255, 0));

		SetBkColor(hdc, RGB(0, 0, 0));

		DrawText(hdc, str, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		break;*/
	case WM_CREATE:
		hThreadOne = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProcOne,(LPVOID)hwnd,0,NULL);

		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd,str,TEXT("Message"), MB_OK );
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID Param)
{
	HDC hDC;
	long int i;
	TCHAR str[255];
	hDC = GetDC((HWND)Param);
	SetBkColor(hDC, RGB(0, 0, 0));
	SetTextColor(hDC, RGB(0, 255, 0));

	for ( i = 0; i < 4294967295; i++)
	{
		wsprintf(str, TEXT("Thread One Incresing Order: %ld"), i);
		TextOut(hDC,5,5,str,lstrlen(str));
	}

	ReleaseDC((HWND)Param, hDC);
	return 0;

}

DWORD WINAPI ThreadProcTwo(LPVOID Param)
{
	HDC hDC;
	long int j;
	TCHAR str[255];
	hDC = GetDC((HWND)Param);
	SetBkColor(hDC, RGB(0, 0, 0));
	SetTextColor(hDC, RGB(0, 255, 0));

	for (j = 429496729;  j > 0; j--)
	{
		wsprintf(str, TEXT("Thread Two Decresing Order: %ld"), j);
		TextOut(hDC,5,50,str,lstrlen(str));
	}

	ReleaseDC((HWND)Param, hDC);
	return 0;

}