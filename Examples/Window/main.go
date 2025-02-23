package main

/*
#include <stdio.h>
#include <stdlib.h>
#include "../../lib/window.c"
*/
import "C"
import "unsafe"

func main() {
	title := C.CString("My First Window")
	defer C.free(unsafe.Pointer(title))
	C.CreateMyWindow(title)
}
