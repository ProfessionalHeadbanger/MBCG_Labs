#include <Windows.h>

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure);
LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASS mainWindow = createWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", windowProcedure);

	if (!RegisterClassW(&mainWindow))
		return -1;

	CreateWindow(L"MainWndClass", L"MainWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 500, NULL, NULL, NULL, NULL);

	MSG message = { 0 };
	while (GetMessage(&message, NULL, NULL, NULL)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure)
{
	WNDCLASS wc = { 0 };

	wc.hCursor = cursor;
	wc.hIcon = icon;
	wc.hInstance = hInstance;
	wc.lpszClassName = windowName;
	wc.hbrBackground = bgColor;
	wc.lpfnWndProc = windowProcedure;

	return wc;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc = NULL;

	static POINT point;
	int shift = 30;
	const static int sideLenght = 100;
	static RECT rcClient;
	GetWindowRect(hWnd, &rcClient);
	static RECT square;
	static int clr = 0;

	switch (msg)
	{
	case WM_CREATE:
		point.x = 200;
		point.y = 200;
		square.left = point.x;
		square.top = point.y;
		square.right = point.x + sideLenght;
		square.bottom = point.y + sideLenght;
		break;
	case WM_LBUTTONDOWN:
		if (point.x >= shift)
		{
			point.x -= shift;
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_RBUTTONDOWN:
		point.x += shift;
		InvalidateRect(NULL, &rcClient, true);
		break;
	case WM_KEYDOWN:
		if (wp == 0x43)
		{
			clr = (clr + 1) % 5;
			InvalidateRect(NULL, &rcClient, true);
			UpdateWindow(hWnd);
		}
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		square.left = point.x;
		square.top = point.y;
		square.right = point.x + sideLenght;
		square.bottom = point.y + sideLenght;
		FillRect(hdc, &square, (HBRUSH)clr);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
