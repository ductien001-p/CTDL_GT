#include "features/Lop/lop.h"

#include <iostream>
#include <iomanip>

#include "screen/include/menuLop.h"

#include "HamHoTro/hamhotro.h"
#include "decoration/decoration.h"

#include "../struct/app_context.h"

using namespace std;

//================================================
// THEM LOP
//================================================

void uiThemLop(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        15,
        3,
        70,
        12,
        "THEM LOP");

    char maLop[LEN_MALOP];

    char tenLop[LEN_TENLOP];

    gotoXY(20, 7);

    cout << "Ma lop  : ";

    gotoXY(32, 7);

    cin.getline(
        maLop,
        LEN_MALOP);

    gotoXY(20, 9);

    cout << "Ten lop : ";

    gotoXY(32, 9);

    cin.getline(
        tenLop,
        LEN_TENLOP);

    bool kq =
        themLop(
            app.db.dsLop,
            maLop,
            tenLop);

    veKhungThongBao(
        15,
        16,
        70,
        4);

    if (kq)
    {

        saveLop(
            app.db.dsLop);

        hienThongBao(
            15,
            16,
            "Them lop thanh cong!",
            true);
    }
    else
    {

        hienThongBao(
            15,
            16,
            "Ma lop da ton tai!",
            false);
    }

    choNhanPhim(
        15,
        18);
}

//================================================
// TIM LOP
//================================================

void uiTimLop(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        15,
        3,
        70,
        10,
        "TIM LOP");

    char maLop[LEN_MALOP];

    gotoXY(20, 7);

    cout << "Nhap ma lop : ";

    gotoXY(35, 7);

    cin.getline(
        maLop,
        LEN_MALOP);

    Lop *lop =
        timLop(
            app.db.dsLop,
            maLop);

    if (lop == nullptr)
    {

        veKhungThongBao(
            15,
            14,
            70,
            4);

        hienThongBao(
            15,
            14,
            "Khong tim thay lop!",
            false);

        choNhanPhim(
            15,
            16);

        return;
    }

    clearScreen();

    veKhungManHinh(
        15,
        3,
        70,
        12,
        "THONG TIN LOP");

    gotoXY(20, 7);

    cout << "Ma lop : "
         << lop->malop;

    gotoXY(20, 8);

    cout << "Ten lop: "
         << lop->tenlop;

    gotoXY(20, 9);

    cout << "So SV  : "
         << lop->soSV;

    veKhungThongBao(
        15,
        15,
        70,
        4);

    hienThongBao(
        15,
        15,
        "Tim lop thanh cong!",
        true);

    choNhanPhim(
        15,
        17);
}

//================================================
// XOA LOP
//================================================

void uiXoaLop(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        15,
        3,
        70,
        10,
        "XOA LOP");

    char maLop[LEN_MALOP];

    gotoXY(20, 7);

    cout << "Nhap ma lop : ";

    gotoXY(35, 7);

    cin.getline(
        maLop,
        LEN_MALOP);

    bool kq =
        xoaLop(
            app.db.dsLop,
            maLop);

    veKhungThongBao(
        15,
        14,
        70,
        4);

    if (kq)
    {

        saveLop(
            app.db.dsLop);

        saveSinhVien(
            app.db.dsLop);

        hienThongBao(
            15,
            14,
            "Xoa lop thanh cong!",
            true);
    }
    else
    {

        hienThongBao(
            15,
            14,
            "Khong tim thay lop!",
            false);
    }

    choNhanPhim(
        15,
        16);
}

//================================================
// IN DS LOP
//================================================

#include <conio.h>

void uiInDSLop(
    AppContext &app)
{

    int offset = 0;

    const int soDong = 8;

    while (true)
    {

        clearScreen();

        veKhungManHinh(
            2,
            1,
            100,
            20,
            "DANH SACH LOP");

        gotoXY(5, 4);

        cout
            << left
            << setw(20)
            << "MA LOP"

            << setw(50)
            << "TEN LOP"

            << setw(10)
            << "SO SV";

        int y = 6;

        for (
            int i = offset;
            i < app.db.dsLop.n &&
            i < offset + soDong;
            i++)
        {

            Lop *lop =
                app.db.dsLop.ds[i];

            if (lop == nullptr)
                continue;

            gotoXY(
                5,
                y++);

            cout
                << left
                << setw(20)
                << lop->malop

                << setw(50)
                << lop->tenlop

                << setw(10)
                << lop->soSV;
        }

        veKhungThongBao(
            2,
            22,
            100,
            3);

        gotoXY(8, 23);

        cout
            << "UP/DOWN: Cuon | ESC: Thoat";

        int key =
            _getch();

        if (key == 27)
            break;

        if (key == 224)
        {

            key =
                _getch();

            // mui ten len

            if (key == 72)
            {
                if (offset > 0)
                    offset--;
            }

            // mui ten xuong

            if (key == 80)
            {
                if (offset + soDong < app.db.dsLop.n)
                    offset++;
            }
        }
    }
}

//================================================
// MENU
//================================================

void menuLop(
    AppContext &app)
{

    const char *ds[] =
        {
            "Them lop",
            "Tim lop",
            "Xoa lop",
            "In danh sach lop",
            "Quay lai"};

    while (true)
    {

        int chon =
            menuConsole(
                "QUAN LY LOP",
                ds,
                5);

        switch (chon)
        {

        case 0:
            uiThemLop(app);
            break;

        case 1:
            uiTimLop(app);
            break;

        case 2:
            uiXoaLop(app);
            break;

        case 3:
            uiInDSLop(app);
            break;

        case 4:
            return;
        }
    }
}