package main

/*
#cgo LDFLAGS: -lcomctl32
#include <windows.h>
#include <stdlib.h>
#include "../../lib/progressbar.c"

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
	"time"
)

func main() {
	go func() {
		C.runProgressBar()
	}()

	for i := 0; i <= 100; i++ {
		C.cUpdateProgressBar(C.int(i))
		time.Sleep(100 * time.Millisecond)
		fmt.Printf("Progress: %d%%\n", i)
	}
}
