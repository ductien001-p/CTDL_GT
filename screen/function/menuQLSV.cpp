#include "screen/include/menuQLSV.h"
#include "features/SinhVien/sinhvien.h"
#include <cstdlib>
#include <iostream>
#include "HamHoTro/hamhotro.h"
#include "decoration/decoration.h"
#include "../struct/app_context.h"
#include "screen/include/MenuDangNhap.h"
#include <iomanip>
#include <conio.h>
using namespace std;
void uiThemSinhVien(
    AppContext &app)
{
    clearScreen();

    veKhungManHinh(
        10,
        2,
        90,
        18,
        "THEM SINH VIEN");

    char maLop[LEN_MALOP];

    gotoXY(15, 6);
    cout << "Ma lop : ";

    gotoXY(30, 6);

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
            10,
            22,
            90,
            5);

        hienThongBao(
            10,
            22,
            "Khong tim thay lop!",
            false);

        choNhanPhim(
            10,
            25);

        return;
    }

    char masv[LEN_MASV];
    char ho[LEN_HO];
    char ten[LEN_TEN];
    char pass[LEN_PASS];

    int phai;

    gotoXY(15, 8);
    cout << "Ma SV     : ";

    gotoXY(30, 8);

    cin.getline(
        masv,
        LEN_MASV);

    gotoXY(15, 10);
    cout << "Ho        : ";

    gotoXY(30, 10);

    cin.getline(
        ho,
        LEN_HO);

    gotoXY(15, 12);
    cout << "Ten       : ";

    gotoXY(30, 12);

    cin.getline(
        ten,
        LEN_TEN);

    gotoXY(15, 14);
    cout << "Phai (0/1): ";

    gotoXY(30, 14);

    cin >> phai;

    cin.ignore(
        1000,
        '\n');

    gotoXY(15, 16);
    cout << "Password  : ";

    gotoXY(30, 16);

    cin.getline(
        pass,
        LEN_PASS);

    SinhVien *sv =
        taoSinhVien(
            masv,
            ho,
            ten,
            phai,
            pass);

    if (
        themSinhVien(
            lop,
            sv))
    {

        saveSinhVien(
            app.db.dsLop);

        saveLop(
            app.db.dsLop);

        veKhungThongBao(
            10,
            22,
            90,
            5);

        hienThongBao(
            10,
            22,
            "Them sinh vien thanh cong!",
            true);

        choNhanPhim(
            10,
            25);
    }
    else
    {

        delete sv;

        veKhungThongBao(
            10,
            22,
            90,
            5);

        hienThongBao(
            10,
            22,
            "Ma sinh vien da ton tai!",
            false);

        choNhanPhim(
            10,
            25);
    }
}
void uiTimSinhVien(
    AppContext &app)
{
    clearScreen();

    veKhungManHinh(
        15,
        3,
        80,
        8,
        "TIM SINH VIEN");

    char masv[LEN_MASV];

    gotoXY(20, 7);

    cout << "Nhap ma SV : ";

    gotoXY(35, 7);

    cin.getline(
        masv,
        LEN_MASV);

    SinhVien *sv =
        timSinhVien(
            app.db.dsLop,
            masv);

    if (sv == nullptr)
    {

        veKhungThongBao(
            15,
            13,
            80,
            5);

        hienThongBao(
            15,
            13,
            "Khong tim thay sinh vien!",
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
        80,
        12,
        "THONG TIN SINH VIEN");

    gotoXY(20, 7);

    cout
        << "Ma SV : "
        << sv->masv;

    gotoXY(20, 8);

    cout
        << "Ho    : "
        << sv->ho;

    gotoXY(20, 9);

    cout
        << "Ten   : "
        << sv->ten;

    gotoXY(20, 10);

    cout
        << "Phai  : "
        << (sv->phai == PHAI_NAM
                ? "Nam"
                : "Nu");

    veKhungThongBao(
        15,
        17,
        80,
        5);

    hienThongBao(
        15,
        17,
        "Tim thay sinh vien!",
        true);

    choNhanPhim(
        15,
        20);
}
void uiXoaSinhVien(
    AppContext &app)
{
    clearScreen();

    veKhungManHinh(
        15,
        3,
        80,
        10,
        "XOA SINH VIEN");

    char maLop[LEN_MALOP];

    gotoXY(20, 7);

    cout << "Ma lop : ";

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
            80,
            5);

        hienThongBao(
            15,
            14,
            "Khong tim thay lop!",
            false);

        choNhanPhim(
            15,
            17);

        return;
    }

    char masv[LEN_MASV];

    gotoXY(20, 9);

    cout << "Ma SV  : ";

    gotoXY(35, 9);

    cin.getline(
        masv,
        LEN_MASV);

    if (
        xoaSinhVien(
            lop,
            masv))
    {

        saveSinhVien(
            app.db.dsLop);

        saveLop(
            app.db.dsLop);

        veKhungThongBao(
            15,
            14,
            80,
            5);

        hienThongBao(
            15,
            14,
            "Xoa sinh vien thanh cong!",
            true);

        choNhanPhim(
            15,
            17);
    }
    else
    {

        veKhungThongBao(
            15,
            14,
            80,
            5);

        hienThongBao(
            15,
            14,
            "Khong tim thay sinh vien!",
            false);

        choNhanPhim(
            15,
            17);
    }
}
void uiInDSSinhVien(
    AppContext &app)
{
    clearScreen();

    char maLop[LEN_MALOP];

    // khung nhập

    veKhungManHinh(
        15,
        2,
        70,
        8,
        "DANH SACH SINH VIEN");

    gotoXY(20, 6);

    cout << "Nhap ma lop : ";

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
            15,
            11,
            70,
            4);

        hienThongBao(
            18,
            12,
            "Khong tim thay lop!",
            false);

        choNhanPhim(
            20,
            14);

        return;
    }

    // lấy danh sách sinh viên

    SinhVien *ds[1000];

    int n = 0;

    SinhVien *p =
        lop->dsSV;

    while (p)
    {
        ds[n++] = p;
        p = p->tiep;
    }

    int start = 0;

    const int pageSize = 8;

    while (true)
    {

        clearScreen();

        veKhungManHinh(
            2,
            1,
            90,
            18,
            "DANH SACH SINH VIEN");

        gotoXY(5, 4);

        cout
            << left
            << setw(15)
            << "MASV"

            << setw(25)
            << "HO"

            << setw(20)
            << "TEN"

            << setw(10)
            << "PHAI";

        int y = 6;

        for (
            int i = start;
            i < n && i < start + pageSize;
            i++)
        {

            gotoXY(
                5,
                y++);

            cout
                << left
                << setw(15)
                << ds[i]->masv

                << setw(25)
                << ds[i]->ho

                << setw(20)
                << ds[i]->ten

                << setw(10)
                << (ds[i]->phai == PHAI_NAM
                        ? "Nam"
                        : "Nu");
        }

        // thanh huong dan

        veKhungThongBao(
            2,
            20,
            90,
            4);

        hienThongBao(
            5,
            21,
            "UP/DOWN: Cuon | ESC: Thoat",
            true);

        int key = _getch();

        if (key == 27)
            break;

        if (key == 224)
        {
            key = _getch();

            // len

            if (key == 72)
            {
                if (start > 0)
                    start--;
            }

            // xuong

            if (key == 80)
            {
                if (start + n < n &&
                    start + pageSize < n)
                    start++;
            }
        }
    }
}
void menuQuanLySinhVien(
    AppContext &app)
{
    const char *ds[] =
        {
            "Them sinh vien vao lop",
            "Tim sinh vien",
            "Xoa sinh vien",
            "In DSSV theo lop",
            "Quay lai"};

    while (true)
    {
        int chon =
            menuConsole(
                "QUAN LY SINH VIEN",
                ds,
                5);

        switch (chon)
        {
        case 0:
            uiThemSinhVien(app);
            break;

        case 1:
            uiTimSinhVien(app);
            break;

        case 2:
            uiXoaSinhVien(app);
            break;

        case 3:
            uiInDSSinhVien(app);
            break;

        case 4:
            return;
        }
    }
}