// msgbox.c
#include <windows.h>
#include <stdio.h>

void MsgBox(const char* name, const char* title) {
    MessageBox(NULL, name, title, MB_OK);
  }