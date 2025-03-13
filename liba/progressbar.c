#include <windows.h>
#include <commctrl.h>

#define ID_PROGRESS_BAR 1

HWND hwndProgress;
int progressValue = 0;

// Rename the window procedure to avoid conflicts
LRESULT CALLBACK ProgressBarProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        InitCommonControls();
        hwndProgress = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE,
                                      10, 10, 280, 20, hwnd, (HMENU)ID_PROGRESS_BAR, GetModuleHandle(NULL), NULL);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void UpdateProgressBar(int value) {
    progressValue = value;
    if (hwndProgress) {
        SendMessage(hwndProgress, PBM_SETPOS, progressValue, 0);
    }
}

int ShowProgressBar(HINSTANCE hInstance) {
    const wchar_t CLASS_NAME[] = L"ProgressBarWindowClass";
    WNDCLASSW wc = { };
    wc.lpfnWndProc = ProgressBarProc; // Use the renamed procedure
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"Progress Bar Example", WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT, 300, 100, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 1;
}
