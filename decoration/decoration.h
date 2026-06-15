#ifndef MENU_CONSOLE_H
#define MENU_CONSOLE_H

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

inline void setColor(int color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color);
}

int menuConsole(
    const char *title,
    const char *items[],
    int soLuong);

#endif