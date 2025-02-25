package main

import (
    "github.com/andlabs/ui"
)

func main() {
    err := ui.Main(func() {
        window := ui.NewWindow("Greeting", 200, 100, false)
        msg := ui.NewLabel("Hello, World!")
        window.SetChild(msg)
        window.OnClosing(func(*ui.Window) bool {
            ui.Quit()
            return true
        })
        window.Show()
    })
    if err != nil {
        panic(err)
    }
}
