package main

/*
#cgo LDFLAGS: -lcomctl32
#include <stdio.h>
#include <stdlib.h>
#include "../../liba/window.c"
#include "../../liba/inputmsgbox.c"
#include "../../liba/inputmemomsgbox.c"
#include "../../liba/listbox.c"
#include "../../liba/progressbar.c"
#include "../../liba/msgbox.c"
#include "../../liba/yesnomsgbox.c"

extern void UpdateProgressBar(int value);

static int runProgressBar() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    return ShowProgressBar(hInstance);
}

void cUpdateProgressBar(int value) {
    UpdateProgressBar(value);
}
*/
import "C"
import (
	"fmt"
	"os"
	"time"
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
	case "4": // Simple Message Box
		msgBoxTitle := C.CString("Message Box Test")
		message := C.CString("Hello from the Message Box!")
		defer C.free(unsafe.Pointer(msgBoxTitle))
		defer C.free(unsafe.Pointer(message))
		C.SimpleMsgBox(message, msgBoxTitle)
	case "5": // Progress Bar
		go func() {
			C.runProgressBar()
		}()
		for i := 0; i <= 100; i++ {
			C.cUpdateProgressBar(C.int(i))
			time.Sleep(100 * time.Millisecond)
			fmt.Printf("Progress: %d%%\n", i)
		}
	case "6": // Yes/No Message Box
		yesNoTitle := C.CString("Yes/No Message Box")
		yesNoMessage := C.CString("Do you like this application?")
		defer C.free(unsafe.Pointer(yesNoTitle))
		defer C.free(unsafe.Pointer(yesNoMessage))

		result := C.MsgBox(yesNoMessage, yesNoTitle)
		fmt.Printf("User Selected: %s\n", C.GoString(result))
	case "7": // Exit
		fmt.Println("Exiting program.")
		os.Exit(0)
	default:
		fmt.Println("Unknown menu option.")
	}
}
