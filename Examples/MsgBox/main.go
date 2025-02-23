// main.go
package main

/*
#include <stdio.h>
#include <stdlib.h>
#include "../../lib/msgbox.c"
*/
import "C"
import "unsafe"

func main() {
	name := C.CString("Call from the Go Program..")
	title := C.CString("Message Box Test")
	defer C.free(unsafe.Pointer(name))
	defer C.free(unsafe.Pointer(title))
	C.MsgBox(name, title)
}
