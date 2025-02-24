#include <windows.h>
#include <string.h>

static char message[256];

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndEdit;
    switch (uMsg) {
        case WM_CREATE:
            hwndEdit = CreateWindow(TEXT("EDIT"), TEXT(""),
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    10, 10, 260, 20,
                                    hwnd, (HMENU)1, NULL, NULL);
            CreateWindow(TEXT("BUTTON"), TEXT("OK"),
                         WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         280, 10, 50, 20,
                         hwnd, (HMENU)2, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == 2) {
                GetWindowText(hwndEdit, message, 256);
                PostQuitMessage(0);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

const char* CreateInputWindow(const char* title) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("InputBoxApp");

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, TEXT("InputBoxApp"), title,
                               WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
                               NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return message;
}
