#include "decoration.h"

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstring>

using namespace std;

//==============================
// DI CHUYEN CON TRO
//==============================

void gotoXY(int x, int y)
{
    COORD c;

    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        c);
}

//==============================
// MAU CHU
//==============================

void setColor(int color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color);
}

//==============================
// XOA MAN HINH
//==============================

void clearScreen()
{
    system("cls");
}

//==============================
// VE KHUNG CO BAN
//==============================

void veKhung(
    int x,
    int y,
    int width,
    int height)
{

    // goc tren trai

    gotoXY(x, y);
    cout << (char)218;

    // canh tren

    for (int i = 0; i < width - 2; i++)
        cout << (char)196;

    // goc tren phai

    cout << (char)191;

    // 2 canh doc

    for (int i = 1; i < height - 1; i++)
    {
        gotoXY(x, y + i);
        cout << (char)179;

        gotoXY(x + width - 1, y + i);
        cout << (char)179;
    }

    // day

    gotoXY(x, y + height - 1);

    cout << (char)192;

    for (int i = 0; i < width - 2; i++)
        cout << (char)196;

    cout << (char)217;
}

//==============================
// VE TIEU DE TRONG KHUNG
//==============================

void veTieuDe(
    int x,
    int y,
    int width,
    const char *title)
{

    int pos =
        x + (width - strlen(title)) / 2;

    gotoXY(
        pos,
        y + 1);

    setColor(11);

    cout << title;

    setColor(7);
}

//==============================
// VE DUONG NGAN TIEU DE
//==============================

void veKhungTieuDe(
    int x,
    int y,
    int width)
{

    gotoXY(
        x,
        y + 2);

    cout << (char)195;

    for (int i = 0; i < width - 2; i++)
        cout << (char)196;

    cout << (char)180;
}

//==============================
// HAM VE MAN HINH CHUNG
//==============================

void veKhungManHinh(
    int x,
    int y,
    int width,
    int height,
    const char *title)
{

    veKhung(
        x,
        y,
        width,
        height);

    veTieuDe(
        x,
        y,
        width,
        title);
    veKhungTieuDe(
        x,
        y,
        width);
}

//==============================
// KHUNG THONG BAO
//==============================

void veKhungThongBao(
    int x,
    int y,
    int width,
    int height)
{

    veKhung(
        x,
        y,
        width,
        height);

    gotoXY(
        x,
        y + 2);

    cout << (char)195;

    for (int i = 0; i < width - 2; i++)
        cout << (char)196;

    cout << (char)180;
}

//==============================
// IN THONG BAO
//==============================

void hienThongBao(
    int x,
    int y,
    const char *msg,
    bool thanhCong)
{

    gotoXY(
        x + 5,
        y + 1);

    if (thanhCong)
        setColor(10);
    else
        setColor(12);

    cout << msg;

    setColor(7);
}

//==============================
// CHO NHAN PHIM
//==============================

void choNhanPhim(
    int x,
    int y)
{

    gotoXY(
        x + 5,
        y);

    setColor(14);

    cout
        << "Nhan phim bat ky de tiep tuc...";

    setColor(7);

    _getch();
}

//==============================
// MENU
//==============================

int menuConsole(
    const char *title,
    const char *items[],
    int soLuong)
{

    int chon = 0;

    int x = 10;
    int y = 2;
    int w = 60;

    clearScreen();

    veKhungManHinh(
        x,
        y,
        w,
        soLuong + 6,
        title);

    while (true)
    {

        for (int i = 0; i < soLuong; i++)
        {

            gotoXY(
                x + 5,
                y + 4 + i);

            if (i == chon)
            {
                setColor(14);

                cout << "> ";
            }
            else
            {
                setColor(7);

                cout << "  ";
            }

            cout << items[i];
        }

        int key = _getch();

        if (key == 224)
        {
            key = _getch();

            if (key == 72)
            {
                chon--;

                if (chon < 0)
                    chon = soLuong - 1;
            }

            if (key == 80)
            {
                chon++;

                if (chon >= soLuong)
                    chon = 0;
            }
        }

        if (key == 13)
        {
            setColor(7);

            return chon;
        }
    }
}

//==============================
// XOA VUNG
//==============================

void clearArea(
    int x,
    int y,
    int width,
    int height)
{

    for (int i = 0; i < height; i++)
    {
        gotoXY(
            x,
            y + i);

        for (int j = 0; j < width; j++)
            cout << " ";
    }
}