package main

/*
#include <stdio.h>
#include <stdlib.h>
#include "../../lib/window.c"
*/
import "C"
import (
	"fmt"
	"unsafe"
)

func main() {
	title := C.CString("My First Window")
	defer C.free(unsafe.Pointer(title))
	selectedItem := C.CreateMyWindow(title)
	fmt.Printf("Selected Menu Item: %s\n", C.GoString(selectedItem))
}
