package main

/*
#ifdef _WIN32
#include <windows.h>
void MsgBox(const char* name, const char* title) {
    MessageBox(NULL, name, title, MB_OK);
}
#else
#include <stdio.h>
#include <stdlib.h>
void MsgBox(const char* name, const char* title) {
    printf("%s: %s\n", title, name);
}
#endif
*/
import "C"
import (
    "unsafe"
    "fmt"
)

func main() {
    name := C.CString("Hello, World!")
    title := C.CString("Greeting")
    defer C.free(unsafe.Pointer(name))
    defer C.free(unsafe.Pointer(title))

    fmt.Println("Calling MsgBox function...")
    // Call the C function to display the message box
    C.MsgBox(name, title)
    fmt.Println("MsgBox function called.")
}
