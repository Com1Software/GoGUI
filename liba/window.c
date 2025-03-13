#include <windows.h>
#include <string.h>

char selectedMenuItem[256] = "";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND: {
        int menuId = LOWORD(wParam);
        sprintf_s(selectedMenuItem, sizeof(selectedMenuItem), "%d", menuId); // Menu ID as string
        PostQuitMessage(0);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

HMENU CreateMyMenu() {
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();

    AppendMenu(hFileMenu, MF_STRING, 1, "Single Line Input");
    AppendMenu(hFileMenu, MF_STRING, 2, "Multi-Line Input");
    AppendMenu(hFileMenu, MF_STRING, 3, "Listbox");
    AppendMenu(hFileMenu, MF_STRING, 4, "Message Box");
    AppendMenu(hFileMenu, MF_STRING, 5, "Exit");

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
        0, CLASS_NAME, title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
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
