#include "screen/include/menuMonhoc.h"

#include "features/MonHoc/monhoc.h"

#include "../struct/app_context.h"

#include "HamHoTro/hamhotro.h"
#include "decoration/decoration.h"

#include <iostream>
#include <iomanip>

using namespace std;

//====================================
// THEM MON HOC
//====================================

void uiThemMonHoc(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        15,
        3,
        70,
        14,
        "THEM MON HOC");

    MonHoc mh;

    gotoXY(20, 7);
    cout << "Ma mon hoc : ";

    gotoXY(35, 7);

    cin.getline(
        mh.mamh,
        LEN_MAMH);

    gotoXY(20, 9);

    cout << "Ten mon hoc: ";

    gotoXY(35, 9);

    cin.getline(
        mh.tenmh,
        LEN_TENMH);

    gotoXY(20, 11);

    cout << "So tin chi : ";

    gotoXY(35, 11);

    cin >> mh.soTinChi;

    cin.ignore(
        1000,
        '\n');

    mh.daXoa = 0;

    bool kq =
        themMonHoc(
            app.db.dsMH,
            mh);

    veKhungThongBao(
        15,
        17,
        70,
        4);

    if (kq)
    {

        saveMonHoc(
            app.db.dsMH);

        hienThongBao(
            15,
            17,
            "Them mon hoc thanh cong!",
            true);
    }
    else
    {

        hienThongBao(
            15,
            17,
            "Ma mon hoc da ton tai!",
            false);
    }

    choNhanPhim(
        15,
        19);
}

//====================================
// TIM MON HOC
//====================================

void uiTimMonHoc(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        15,
        3,
        70,
        10,
        "TIM MON HOC");

    char maMH[LEN_MAMH];

    gotoXY(20, 7);

    cout << "Nhap ma MH : ";

    gotoXY(35, 7);

    cin.getline(
        maMH,
        LEN_MAMH);

    MonHoc *mh =
        timMonHoc(
            app.db.dsMH,
            maMH);

    if (mh == nullptr)
    {

        veKhungThongBao(
            15,
            14,
            70,
            4);

        hienThongBao(
            15,
            14,
            "Khong tim thay mon hoc!",
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
        "THONG TIN MON HOC");

    gotoXY(20, 7);

    cout << "Ma MH      : "
         << mh->mamh;

    gotoXY(20, 8);

    cout << "Ten MH     : "
         << mh->tenmh;

    gotoXY(20, 9);

    cout << "So tin chi : "
         << mh->soTinChi;

    veKhungThongBao(
        15,
        15,
        70,
        4);

    hienThongBao(
        15,
        15,
        "Tim mon hoc thanh cong!",
        true);

    choNhanPhim(
        15,
        17);
}

//====================================
// SUA MON HOC
//====================================

void uiSuaMonHoc(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        15,
        3,
        70,
        14,
        "SUA MON HOC");

    char maMH[LEN_MAMH];

    gotoXY(20, 7);

    cout << "Nhap ma MH : ";

    gotoXY(35, 7);

    cin.getline(
        maMH,
        LEN_MAMH);

    MonHoc *cu =
        timMonHoc(
            app.db.dsMH,
            maMH);

    if (cu == nullptr)
    {

        veKhungThongBao(
            15,
            17,
            70,
            4);

        hienThongBao(
            15,
            17,
            "Khong tim thay mon hoc!",
            false);

        choNhanPhim(
            15,
            19);

        return;
    }

    MonHoc moi = *cu;

    gotoXY(20, 9);

    cout << "Ten moi    : ";

    gotoXY(35, 9);

    cin.getline(
        moi.tenmh,
        LEN_TENMH);

    gotoXY(20, 11);

    cout << "So tin chi : ";

    gotoXY(35, 11);

    cin >> moi.soTinChi;

    cin.ignore(
        1000,
        '\n');

    bool kq =
        suaMonHoc(
            app.db.dsMH,
            maMH,
            moi);

    veKhungThongBao(
        15,
        17,
        70,
        4);

    if (kq)
    {

        saveMonHoc(
            app.db.dsMH);

        hienThongBao(
            15,
            17,
            "Cap nhat thanh cong!",
            true);
    }
    else
    {

        hienThongBao(
            15,
            17,
            "Cap nhat that bai!",
            false);
    }

    choNhanPhim(
        15,
        19);
}

//====================================
// XOA MON HOC
//====================================

void uiXoaMonHoc(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        15,
        3,
        70,
        10,
        "XOA MON HOC");

    char maMH[LEN_MAMH];

    gotoXY(20, 7);

    cout << "Nhap ma MH : ";

    gotoXY(35, 7);

    cin.getline(
        maMH,
        LEN_MAMH);

    bool kq =
        xoaMonHoc(
            app.db.dsMH,
            maMH);

    veKhungThongBao(
        15,
        14,
        70,
        4);

    if (kq)
    {

        saveMonHoc(
            app.db.dsMH);

        hienThongBao(
            15,
            14,
            "Xoa mon hoc thanh cong!",
            true);
    }
    else
    {

        hienThongBao(
            15,
            14,
            "Khong tim thay mon hoc!",
            false);
    }

    choNhanPhim(
        15,
        16);
}

//====================================
// IN DANH SACH
//====================================

#include <conio.h>

void uiInDSMonHoc(
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
            "DANH SACH MON HOC");

        gotoXY(5, 4);

        cout
            << left
            << setw(20)
            << "MA MH"

            << setw(50)
            << "TEN MON HOC"

            << setw(10)
            << "TIN CHI";

        int y = 6;

        int dem = 0;

        for (
            int i = offset;
            i < app.db.dsMH.n &&
            dem < soDong;
            i++)
        {

            if (app.db.dsMH.ds[i].daXoa)
                continue;

            gotoXY(
                5,
                y++);

            cout
                << left
                << setw(20)
                << app.db.dsMH.ds[i].mamh

                << setw(50)
                << app.db.dsMH.ds[i].tenmh

                << setw(10)
                << app.db.dsMH.ds[i].soTinChi;

            dem++;
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

            // len

            if (key == 72)
            {
                if (offset > 0)
                    offset--;
            }

            // xuong

            if (key == 80)
            {

                int demConLai = 0;

                for (
                    int i = offset;
                    i < app.db.dsMH.n;
                    i++)
                {

                    if (!app.db.dsMH.ds[i].daXoa)
                        demConLai++;
                }

                if (demConLai > soDong)
                    offset++;
            }
        }
    }
}
//====================================
// MENU
//====================================

void menuMonHoc(
    AppContext &app)
{

    const char *ds[] =
        {
            "Them mon hoc",
            "Tim mon hoc",
            "Sua mon hoc",
            "Xoa mon hoc",
            "In danh sach mon hoc",
            "Quay lai"};

    while (true)
    {

        int chon =
            menuConsole(
                "QUAN LY MON HOC",
                ds,
                6);

        switch (chon)
        {

        case 0:
            uiThemMonHoc(app);
            break;

        case 1:
            uiTimMonHoc(app);
            break;

        case 2:
            uiSuaMonHoc(app);
            break;

        case 3:
            uiXoaMonHoc(app);
            break;

        case 4:
            uiInDSMonHoc(app);
            break;

        case 5:
            return;
        }
    }
}