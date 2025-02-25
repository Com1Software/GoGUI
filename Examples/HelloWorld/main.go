package main

import (
    "os"

    "github.com/mattn/go-gtk/gtk"
)

func main() {
    // Initialize GTK
    gtk.Init(&os.Args)

    // Create a new window
    window := gtk.NewWindow(gtk.WINDOW_TOPLEVEL)
    window.SetTitle("Hello, World!")
    window.Connect("destroy", gtk.MainQuit)

    // Create a new label
    label := gtk.NewLabel("Hello, World!")

    // Add the label to the window
    window.Add(label)

    // Set the window size
    window.SetSizeRequest(300, 200)

    // Show all widgets in the window
    window.ShowAll()

    // Start the GTK main loop
    gtk.Main()
}
