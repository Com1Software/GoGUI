package main

/*
#include <stdio.h>
#include <stdlib.h>
#include "../../liba/window.c"
#include "../../liba/inputmsgbox.c"
#include "../../liba/inputmemomsgbox.c"
#include "../../liba/listbox.c"
#include "../../liba/msgbox.c"
*/
import "C"
import (
	"fmt"
	"os"
	"unsafe"
)

func main() {
	title := C.CString("Main Window")
	defer C.free(unsafe.Pointer(title))

	// Display the main window with a menu
	selectedMenu := C.CreateMyWindow(title)

	switch C.GoString(selectedMenu) {
	case "1": // Single Line Input
		inputTitle := C.CString("Single Line Input")
		defer C.free(unsafe.Pointer(inputTitle))
		result := C.CreateInputMsgBox(inputTitle)
		fmt.Printf("User Input (Single Line): %s\n", C.GoString(result))
	case "2": // Multi-Line Input
		memoTitle := C.CString("Multi-Line Input")
		defer C.free(unsafe.Pointer(memoTitle))
		result := C.CreateInputMemoBox(memoTitle)
		fmt.Printf("User Input (Multi-Line): %s\n", C.GoString(result))
	case "3": // Listbox
		listTitle := C.CString("Listbox Window")
		defer C.free(unsafe.Pointer(listTitle))

		// Prepare the list of items
		items := []string{"Option 1", "Option 2", "Option 3", "Option 4"}
		cItems := make([]*C.char, len(items))
		for i, item := range items {
			cItems[i] = C.CString(item)
			defer C.free(unsafe.Pointer(cItems[i]))
		}
		cItems = append(cItems, nil) // Null-terminate the list

		result := C.CreateListBoxWindow(listTitle, &cItems[0])
		fmt.Printf("Selected Item: %s\n", C.GoString(result))
	case "4": // Message Box
		msgBoxTitle := C.CString("Message Box Test")
		message := C.CString("Hello from the Message Box!")
		defer C.free(unsafe.Pointer(msgBoxTitle))
		defer C.free(unsafe.Pointer(message))
		C.MsgBox(message, msgBoxTitle)
	case "5": // Exit
		fmt.Println("Exiting program.")
		os.Exit(0)
	default:
		fmt.Println("Unknown menu option.")
	}
}
