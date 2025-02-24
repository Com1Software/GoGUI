package main

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/inputmsgbox.c"
*/
import "C"
import (
	"fmt"
	"unsafe"
)

func main() {
	title := C.CString("Input Message Box")
	defer C.free(unsafe.Pointer(title))

	// Call the C function to create the input window and get the user input
	result := C.CreateInputWindow(title)
	fmt.Printf("User Input: %s\n", C.GoString(result))
}
