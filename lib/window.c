#include <windows.h>
#include <string.h>

char selectedMenuItem[256] = "";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND: {
        MENUITEMINFO mii;
        char menuText[256];
        
        HMENU hMenu = GetMenu(hwnd);
        mii.cbSize = sizeof(MENUITEMINFO);
        mii.fMask = MIIM_STRING;
        mii.dwTypeData = menuText;
        mii.cch = sizeof(menuText) / sizeof(menuText[0]);

        if (GetMenuItemInfo(hMenu, LOWORD(wParam), FALSE, &mii)) {
            strcpy_s(selectedMenuItem, sizeof(selectedMenuItem), menuText);
        } else {
            strcpy_s(selectedMenuItem, sizeof(selectedMenuItem), "Unknown");
        }

        PostQuitMessage(0);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

HMENU CreateMyMenu(int itemCount, const char** items) {
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    
    for (int i = 0; i < itemCount; i++) {
        AppendMenu(hFileMenu, MF_STRING, i + 1, items[i]);
    }

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");

    return hMenu;
}

const char* CreateMyWindow(const char* title, int itemCount, const char** items) {
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

    SetMenu(hwnd, CreateMyMenu(itemCount, items));
    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return selectedMenuItem;
}
