#include "screen/include/menuQL_Thi_SV.h"
#include "features/Lop/lop.h"
#include "features/MonHoc/monhoc.h"
#include "features/SinhVien/sinhvien.h"
#include "features/Thi/thi.h"
#include "features/DiemThi/diemthi.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "../struct/app_context.h"
#include "struct/struct.h"
#include "screen/include/MenuDangNhap.h"
#include "HamHoTro/hamhotro.h"
#include "decoration/decoration.h"
#include "features/DangNhap/dangnhap.h"
#include "features/CauHoi/cauhoi.h"
#include <conio.h>
#include <cstring>
using namespace std;

//==================================================
// THI TRAC NGHIEM
//==================================================

void uiThiTracNghiem(
    AppContext &app)
{
    SinhVien *sv =
        app.session.svHientai;

    if (sv == nullptr)
    {
        hienThongBao(
            15,
            10,
            "Khong tim thay sinh vien!",
            false);

        choNhanPhim(
            15,
            12);

        return;
    }

    char maMH[LEN_MAMH];

    clearScreen();

    veKhungManHinh(
        15,
        3,
        70,
        12,
        "THI TRAC NGHIEM");

    gotoXY(20, 7);
    cout << "Ma mon hoc : ";

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
        hienThongBao(
            15,
            10,
            "Mon hoc khong ton tai!",
            false);

        choNhanPhim(
            15,
            12);

        return;
    }

    batDauThi(
        sv,
        app.db.rootCH,
        maMH,
        mh->soCauHoiThi,
        mh->soPhutThi);

    hienThongBao(
        15,
        10,
        "Da nop bai!",
        true);

    choNhanPhim(
        15,
        12);
}

//==================================================
// XEM DIEM
//==================================================

#include <conio.h>

void uiXemDiem(
    AppContext &app)
{

    SinhVien *sv =
        app.session.svHientai;

    if (sv == nullptr)
    {

        hienThongBao(
            15,
            10,
            "Khong tim thay sinh vien!",
            false);

        choNhanPhim(
            15,
            12);

        return;
    }

    //====================
    // dem so diem
    //====================

    int n = 0;

    DiemThi *tmp =
        sv->dsDiem;

    while (tmp)
    {
        n++;
        tmp = tmp->tiep;
    }

    int offset = 0;

    const int soDong = 8;

    while (true)
    {

        clearScreen();

        veKhungManHinh(
            3,
            1,
            100,
            20,
            "BANG DIEM");

        gotoXY(5, 4);

        cout
            << "Sinh vien: "
            << sv->masv;

        gotoXY(5, 6);

        cout
            << left
            << setw(20)
            << "MON HOC"

            << setw(15)
            << "DIEM"

            << setw(15)
            << "SO DUNG"

            << setw(15)
            << "TONG CAU";

        // đi tới vị trí offset

        DiemThi *dt =
            sv->dsDiem;

        int skip = 0;

        while (dt && skip < offset)
        {
            dt = dt->tiep;
            skip++;
        }

        int y = 8;

        int dem = 0;

        while (
            dt &&
            dem < soDong)
        {

            gotoXY(
                5,
                y++);

            cout
                << left
                << setw(20)
                << dt->mamh

                << setw(15)
                << dt->diem

                << setw(15)
                << dt->soCauDung

                << setw(15)
                << dt->tongCau;

            dt = dt->tiep;

            dem++;
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

            // lên

            if (key == 72)
            {

                if (offset > 0)
                    offset--;
            }

            // xuống

            if (key == 80)
            {

                if (offset + soDong < n)
                    offset++;
            }
        }
    }
}

//==================================================
// CHI TIET BAI THI
//==================================================
void uiChiTietBaiThi(
    AppContext &app)
{

    SinhVien *sv =
        app.session.svHientai;

    if (sv == nullptr)
    {
        hienThongBao(
            15,
            10,
            "Khong tim thay sinh vien!",
            false);

        choNhanPhim(
            15,
            12);

        return;
    }

    char maMH[LEN_MAMH];

    clearScreen();

    veKhungManHinh(
        15,
        3,
        70,
        8,
        "CHI TIET BAI THI");

    gotoXY(20, 6);

    cout
        << "Nhap ma MH : ";

    gotoXY(35, 6);

    cin.getline(
        maMH,
        LEN_MAMH);

    // tim diem cua mon

    DiemThi *dt =
        sv->dsDiem;

    while (dt)
    {

        if (strcmp(
                dt->mamh,
                maMH) == 0)

            break;

        dt = dt->tiep;
    }

    if (dt == nullptr)
    {

        veKhungThongBao(
            15,
            13,
            70,
            4);

        hienThongBao(
            15,
            13,
            "Chua thi mon nay!",
            false);

        choNhanPhim(
            20,
            15);

        return;
    }

    //========================
    // DEM SO CAU
    //========================

    int n = 0;

    KetQuaBaiThi *p =
        dt->dsKetQua;

    while (p)
    {
        n++;
        p = p->tiep;
    }

    int offset = 0;

    const int soDong = 6;

    while (true)
    {

        clearScreen();

        veKhungManHinh(
            2,
            1,
            115,
            22,
            "CHI TIET BAI THI");

        gotoXY(5, 4);

        cout
            << "Mon hoc: "
            << maMH;

        gotoXY(5, 6);

        cout
            << left
            << setw(8)
            << "ID"

            << setw(75)
            << "NOI DUNG"

            << setw(15)
            << "TRA LOI"

            << setw(10)
            << "KQ";

        // bo qua offset node

        p =
            dt->dsKetQua;

        int skip = 0;

        while (
            p &&
            skip < offset)
        {
            p = p->tiep;
            skip++;
        }

        int y = 8;

        int dem = 0;

        while (
            p &&
            dem < soDong)
        {

            NodeBST *node =
                timkiemCauHoi(
                    app.db.rootCH,
                    p->idCauHoi);
            gotoXY(
                5,
                y++);

            if (node)
            {
                CauHoi *ch =
                    &node->data;

                cout
                    << left
                    << setw(8)
                    << ch->id

                    << setw(75)
                    << ch->noidung

                    << setw(15)
                    << p->tlSinhVien

                    << setw(10)
                    << (p->tlDungSai
                            ? "Dung"
                            : "Sai");
            }
            else
            {

                cout
                    << "Khong tim thay cau hoi";
            }

            p = p->tiep;

            dem++;
        }

        veKhungThongBao(
            2,
            24,
            115,
            3);

        gotoXY(8, 25);

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
                if (offset + soDong < n)
                    offset++;
            }
        }
    }
}

//==================================================
// MENU SINH VIEN
//==================================================

void menuQuanLyThiSinhVien(
    AppContext &app)
{

    const char *ds[] =
        {
            "Thi trac nghiem",
            "Xem diem",
            "Xem chi tiet bai thi",
            "Dang xuat"};

    while (true)
    {

        int chon =
            menuConsole(
                "MENU SINH VIEN",
                ds,
                4);

        switch (chon)
        {

        case 0:
            uiThiTracNghiem(app);
            break;

        case 1:
            uiXemDiem(app);
            break;

        case 2:
            uiChiTietBaiThi(app);
            break;

        case 3:

            dangXuat(app);

            return;
        }
    }
}