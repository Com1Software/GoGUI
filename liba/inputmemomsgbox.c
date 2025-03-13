#include <windows.h>
#include <string.h>

// Rename static variable to avoid conflicts
static char inputMemoBoxMessage[1024];

LRESULT CALLBACK MemoBoxProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndEdit;
    switch (uMsg) {
        case WM_CREATE:
            hwndEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                                    10, 10, 360, 140, hwnd, (HMENU)1, NULL, NULL);
            CreateWindow("BUTTON", "OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         280, 160, 50, 20, hwnd, (HMENU)2, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == 2) {
                GetWindowText(hwndEdit, inputMemoBoxMessage, 1024);
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

const char* CreateInputMemoBox(const char* title) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASS wc = {0};
    wc.lpfnWndProc = MemoBoxProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "InputMemoBoxClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, "InputMemoBoxClass", title, WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 400, 230,
                               NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return inputMemoBoxMessage;
}
