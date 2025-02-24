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
	title := C.CString("My First Test ")
	defer C.free(unsafe.Pointer(title))

	// Define menu items
	menuItems := []string{"Option1", "Option2", "Option3", "Exit"}
	cMenuItems := make([]*C.char, len(menuItems))
	for i, item := range menuItems {
		cMenuItems[i] = C.CString(item)
		defer C.free(unsafe.Pointer(cMenuItems[i]))
	}

	selectedItem := C.CreateMyWindow(title, C.int(len(menuItems)), (**C.char)(unsafe.Pointer(&cMenuItems[0])))
	fmt.Printf("Selected Menu Item: %s\n", C.GoString(selectedItem))
}
