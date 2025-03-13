#include <windows.h>
#include <string.h>

static char selected[256];

// Rename the procedure to avoid conflicts
LRESULT CALLBACK ListBoxProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndList;
    switch (uMsg) {
        case WM_CREATE:
            hwndList = CreateWindow(TEXT("LISTBOX"), TEXT(""),
                                    WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL | LBS_DISABLENOSCROLL,
                                    10, 10, 260, 100,
                                    hwnd, (HMENU)1, NULL, NULL);
            // Add items to the listbox
            char** items = (char**)((CREATESTRUCT*)lParam)->lpCreateParams;
            for (int i = 0; items[i] != NULL; i++) {
                SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)items[i]);
            }
            CreateWindow(TEXT("BUTTON"), TEXT("OK"),
                         WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         280, 10, 50, 20,
                         hwnd, (HMENU)2, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == 2) { // OK button pressed
                int index = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
                if (index != LB_ERR) {
                    SendMessage(hwndList, LB_GETTEXT, index, (LPARAM)selected);
                }
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

const char* CreateListBoxWindow(const char* title, char** items) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASS wc = {0};
    wc.lpfnWndProc = ListBoxProc; // Use the renamed procedure
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("ListBoxApp");

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, TEXT("ListBoxApp"), title,
                               WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
                               NULL, NULL, hInstance, items);

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return selected;
}
