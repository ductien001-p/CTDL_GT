#include "screen/include/menuBangDiem.h"

#include "features/DiemThi/diemthi.h"
#include "features/Thi/thi.h"
#include "features/DiemThi/ketquabaithi.h"
#include "features/Lop/lop.h"
#include "features/MonHoc/monhoc.h"

#include "HamHoTro/hamhotro.h"
#include "decoration/decoration.h"

#include "../struct/app_context.h"

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstring>
using namespace std;

//================================================
// IN BANG DIEM LOP
//================================================

#include <conio.h>

#include <conio.h>
#include <cstring>
#include <iomanip>

void uiBangDiem(
    AppContext &app)
{
    clearScreen();

    //=====================
    // NHAP THONG TIN
    //=====================

    veKhungManHinh(
        15,
        2,
        70,
        10,
        "BANG DIEM LOP");

    char maLop[LEN_MALOP];
    char maMH[LEN_MAMH];

    gotoXY(20, 6);

    cout << "Ma lop     : ";

    gotoXY(35, 6);

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
            20,
            14,
            70,
            4);

        hienThongBao(
            20,
            14,
            "Khong tim thay lop!",
            false);

        choNhanPhim(
            25,
            16);

        return;
    }

    gotoXY(20, 8);

    cout
        << "Ma mon hoc : ";

    gotoXY(35, 8);

    cin.getline(
        maMH,
        LEN_MAMH);

    //=====================
    // TAO DANH SACH DIEM
    //=====================

    struct DongDiem
    {
        char masv[LEN_MASV];

        float diem;

        int dung;

        int tong;
    };

    DongDiem ds[1000];

    int n = 0;

    SinhVien *sv =
        lop->dsSV;

    while (sv)
    {

        DiemThi *dt =
            sv->dsDiem;

        while (dt)
        {

            if (strcmp(
                    dt->mamh,
                    maMH) == 0)
            {

                strcpy(
                    ds[n].masv,
                    sv->masv);

                ds[n].diem =
                    dt->diem;

                ds[n].dung =
                    dt->soCauDung;

                ds[n].tong =
                    dt->tongCau;

                n++;
            }

            dt = dt->tiep;
        }

        sv = sv->tiep;
    }

    if (n == 0)
    {

        veKhungThongBao(
            15,
            15,
            80,
            4);

        hienThongBao(
            15,
            15,
            "Chua co diem mon nay!",
            false);

        choNhanPhim(
            20,
            17);

        return;
    }

    //=====================
    // HIEN THI CUON
    //=====================

    int offset = 0;

    while (true)
    {

        clearScreen();

        veKhungManHinh(
            3,
            1,
            100,
            20,
            "BANG DIEM LOP");

        gotoXY(5, 4);

        cout
            << "Lop: "
            << maLop;

        gotoXY(35, 4);

        cout
            << "Mon: "
            << maMH;

        gotoXY(5, 6);

        cout
            << left
            << setw(15)
            << "MASV"

            << setw(15)
            << "DIEM"

            << setw(15)
            << "SO DUNG"

            << setw(15)
            << "TONG";

        int y = 8;

        for (
            int i = offset;
            i < n &&
            i < offset + 7;
            i++)
        {

            gotoXY(
                5,
                y++);

            cout
                << left
                << setw(15)
                << ds[i].masv

                << setw(15)
                << ds[i].diem

                << setw(15)
                << ds[i].dung

                << setw(15)
                << ds[i].tong;
        }

        veKhungThongBao(
            3,
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

                if (offset + 7 < n)
                    offset++;
            }
        }
    }
}
//================================================
// MENU BANG DIEM
//================================================

void menuBangDiem(
    AppContext &app)
{

    const char *ds[] =
        {
            "In bang diem lop",
            "Quay lai"};

    while (true)
    {

        int chon =
            menuConsole(
                "BANG DIEM",
                ds,
                2);

        switch (chon)
        {

        case 0:

            uiBangDiem(app);

            break;

        case 1:

            return;
        }
    }
}