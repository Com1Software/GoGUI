package main

/*
#ifdef _WIN32
#include <windows.h>
void MsgBox(const char* name, const char* title) {
    MessageBox(NULL, name, title, MB_OK);
}
#else
#include <stdlib.h>
#include <stdio.h>
void MsgBox(const char* name, const char* title) {
    printf("%s: %s\n", title, name);
}
#endif
*/
import "C"
import (
    "unsafe"
)

func main() {
    name := C.CString("Hello, World!")
    title := C.CString("Greeting")
    defer C.free(unsafe.Pointer(name))
    defer C.free(unsafe.Pointer(title))

    // Call the C function to display the message box
    C.MsgBox(name, title)
}
