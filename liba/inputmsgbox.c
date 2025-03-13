#include <windows.h>
#include <string.h>

// Rename static variable to avoid conflicts
static char inputMsgBoxMessage[256];

LRESULT CALLBACK InputBoxProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndEdit;
    switch (uMsg) {
        case WM_CREATE:
            hwndEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    10, 10, 260, 20, hwnd, (HMENU)1, NULL, NULL);
            CreateWindow("BUTTON", "OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         280, 10, 50, 20, hwnd, (HMENU)2, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == 2) {
                GetWindowText(hwndEdit, inputMsgBoxMessage, 256);
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

const char* CreateInputMsgBox(const char* title) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASS wc = {0};
    wc.lpfnWndProc = InputBoxProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "InputMsgBoxClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, "InputMsgBoxClass", title, WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
                               NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return inputMsgBoxMessage;
}
