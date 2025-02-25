package main

import (
    "fyne.io/fyne/v2/app"
    "fyne.io/fyne/v2/container"
    "fyne.io/fyne/v2/widget"
)

func main() {
    // Create a new application
    a := app.New()

    // Create a new window
    w := a.NewWindow("Hello, World!")

    // Create a new label with "Hello, World!" text
    label := widget.NewLabel("Hello, World!")

    // Set the content of the window to the label
    w.SetContent(container.NewCenter(label))

    // Set the window size
    w.Resize(fyne.NewSize(300, 200))

    // Show and run the application
    w.ShowAndRun()
}
