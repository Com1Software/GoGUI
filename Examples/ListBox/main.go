package main

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/listbox.c"
*/
import "C"
import (
	"fmt"
	"unsafe"
)

func main() {
	title := C.CString("Listbox Window")
	defer C.free(unsafe.Pointer(title))

	// Prepare the list of items using a for loop
	items := []string{}
	for i := 1; i <= 14; i++ {
		items = append(items, fmt.Sprintf("Item %d", i))
	}
	items = append(items, "Test 2")

	// Convert the list of items to C strings
	cItems := make([]*C.char, len(items))
	for i, item := range items {
		cItems[i] = C.CString(item)
		defer C.free(unsafe.Pointer(cItems[i]))
	}
	cItems = append(cItems, nil) // Null-terminate the list

	// Pass the list of items to the C function
	result := C.CreateListBoxWindow(title, &cItems[0])
	fmt.Printf("Selected Item: %s\n", C.GoString(result))
}
