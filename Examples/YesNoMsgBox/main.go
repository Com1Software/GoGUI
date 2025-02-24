package main

/*
#include <stdio.h>
#include <stdlib.h>
#include "../../lib/yesnomsgbox.c"
*/
import "C"
import (
	"fmt"
	"unsafe"
)

func main() {
	name := C.CString("Call from the Go Program..")
	title := C.CString("Message Box Test")
	defer C.free(unsafe.Pointer(name))
	defer C.free(unsafe.Pointer(title))

	result := C.MsgBox(name, title)
	fmt.Println(C.GoString(result))
}
