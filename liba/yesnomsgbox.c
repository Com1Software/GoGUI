#include <windows.h>

const char* MsgBox(const char* name, const char* title) {
    int result = MessageBox(NULL, name, title, MB_YESNO);
    if (result == IDYES) {
        return "Yes";
    } else {
        return "No";
    }
}
