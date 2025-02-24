#include <windows.h>
#include <string.h>

char selectedMenuItem[256] = "";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1: // Open
            strcpy(selectedMenuItem, "Open");
            PostQuitMessage(0);
            return 0;
        case 2: // Save
            strcpy(selectedMenuItem, "Save");
            PostQuitMessage(0);
            return 0;
        case 3: // Exit
            strcpy(selectedMenuItem, "Exit");
            PostQuitMessage(0);
            return 0;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

HMENU CreateMyMenu() {
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    AppendMenu(hFileMenu, MF_STRING, 1, "Open");
    AppendMenu(hFileMenu, MF_STRING, 2, "Save");
    AppendMenu(hFileMenu, MF_STRING, 3, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");

    return hMenu;
}

const char* CreateMyWindow(const char* title) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    const char CLASS_NAME[] = "My Window Class";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                           // Optional window styles.
        CLASS_NAME,                  // Window class
        title,                       // Window text
        WS_OVERLAPPEDWINDOW,         // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,  // Size and position
        NULL,                        // Parent window    
        NULL,                        // Menu
        hInstance,                   // Instance handle
        NULL                         // Additional application data
    );

    if (hwnd == NULL) {
        return NULL;
    }

    SetMenu(hwnd, CreateMyMenu());
    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return selectedMenuItem;
}
