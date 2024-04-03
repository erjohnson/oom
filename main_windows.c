// Short example of opening a window on Windows
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdalign.h>
#include <string.h>
#include <assert.h>

#pragma warning(push, 0)

#define UNICODE
#define NOMINMAX
#define COBJMACROS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <intrin.h>

#pragma warning(pop)

#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")
// #pragma comment(lib, "gdi32")
// #pragma comment(lib, "winmm")

#define APP_TITLE L"oom"

#ifdef _DEBUG
#define Assert(Cond) do { if (!(Cond)) __debugbreak(); } while (0)
#else
#define Assert(Cond) (void)(Cond)
#endif
#define HR(hr) do { HRESULT _hr = (hr); Assert(SUCCEEDED(_hr)); } while (0)

#define Unused(expr) (void)(expr)

// Tell Nvidia/AMD drivers to use the most powerful GPU instead of an integrated GPU. Requires Direct3D or OpenGL.
extern "C" {
    __declspec(dllexport) DWORD NvOptimusEnablement                  = 0x00000001;
    __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
}

// globals
static HWND gWindow;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT result = 0;
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		if (wparam == VK_ESCAPE)
		{
			DestroyWindow(hwnd);
		}
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default: result = DefWindowProcW(hwnd, msg, wparam, lparam);
	}
	return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Unused(hPrevInstance);
	Unused(lpCmdLine);
	Unused(nShowCmd);

	{
		WNDCLASSEXW window_class   = {0};
		window_class.cbSize        = sizeof(WNDCLASSEXW);
		window_class.style         = CS_HREDRAW | CS_VREDRAW;
		window_class.lpfnWndProc   = &WndProc;
		window_class.hInstance     = hInstance;
		window_class.hIcon         = LoadIconW(0, IDI_APPLICATION);
		window_class.hCursor       = LoadCursorW(0, IDC_ARROW);
		window_class.lpszClassName = L"MyWindowClass";
		window_class.hIconSm       = LoadIconW(0, IDI_APPLICATION);

		ATOM atom = RegisterClassExW(&window_class);
		Assert(atom);

		RECT init_rect = {0, 0, 1024, 768};
		AdjustWindowRectEx(&init_rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
		LONG init_width  = init_rect.right - init_rect.left;
		LONG init_height = init_rect.bottom - init_rect.top;

		gWindow = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, window_class.lpszClassName, APP_TITLE,
		                          WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, init_width,
		                          init_height, 0, 0, window_class.hInstance, 0);

		if (!gWindow)
		{
			MessageBoxA(0, "CreateWindowEx failed", "Fatal Error", MB_OK);
			return GetLastError();
		}
	}

	bool isRunning = true;
	while (isRunning)
	{
		MSG message = {0};
		while (PeekMessageW(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				isRunning = false;
			}
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}

		Sleep(1);
	}

	return 0;
}
