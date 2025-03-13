#include <windows.h>

// Rename the function to avoid conflicts
void SimpleMsgBox(const char* name, const char* title) {
    MessageBox(NULL, name, title, MB_OK);
}
