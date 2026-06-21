#include "screen/include/menuCauhoi.h"

#include "features/CauHoi/cauhoi.h"
#include "features/Thi/thi.h"
#include "features/MonHoc/monhoc.h"

#include "HamHoTro/hamhotro.h"
#include "decoration/decoration.h"

#include "../struct/app_context.h"
#include <conio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include "struct/struct.h"
#include <cstring>

using namespace std;

//================================================
// THEM CAU HOI
//================================================

void uiThemCauHoi(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        3,
        1,
        115,
        22,
        "THEM CAU HOI");

    CauHoi ch;

    ch.id =
        taoIDMoi(
            app.db.rootCH);

    gotoXY(8, 5);

    cout << "ID moi : "
         << ch.id;

    gotoXY(8, 7);
    cout << "Ma mon hoc : ";

    gotoXY(25, 7);

    cin.getline(
        ch.mamh,
        LEN_MAMH);

    gotoXY(8, 9);
    cout << "Noi dung : ";

    gotoXY(25, 9);

    cin.getline(
        ch.noidung,
        LEN_NOIDUNG);

    gotoXY(8, 11);
    cout << "A : ";

    gotoXY(25, 11);

    cin.getline(
        ch.A,
        LEN_LUACHON);

    gotoXY(8, 13);
    cout << "B : ";

    gotoXY(25, 13);

    cin.getline(
        ch.B,
        LEN_LUACHON);

    gotoXY(8, 15);
    cout << "C : ";

    gotoXY(25, 15);

    cin.getline(
        ch.C,
        LEN_LUACHON);

    gotoXY(8, 17);
    cout << "D : ";

    gotoXY(25, 17);

    cin.getline(
        ch.D,
        LEN_LUACHON);

    gotoXY(8, 19);

    cout << "Dap an dung : ";

    gotoXY(25, 19);

    cin >> ch.dapan;

    cin.ignore(
        1000,
        '\n');

    if (ch.dapan >= 'a' && ch.dapan <= 'z')
    {
        ch.dapan -= 32;
    }

    ch.daXoa = 0;

    bool kq =
        themCauHoi(
            app.db.rootCH,
            ch);

    veKhungThongBao(
        20,
        23,
        70,
        4);

    if (kq)
    {

        saveCauHoi(
            app.db.rootCH);

        hienThongBao(
            20,
            23,
            "Them cau hoi thanh cong!",
            true);
    }
    else
    {

        hienThongBao(
            20,
            23,
            "Them cau hoi that bai!",
            false);
    }

    choNhanPhim(
        20,
        25);
}

//================================================
// TIM CAU HOI
//================================================

void uiTimCauHoi(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        15,
        3,
        80,
        10,
        "TIM CAU HOI");

    int id;

    gotoXY(20, 7);

    cout << "Nhap ID : ";

    cin >> id;

    cin.ignore(
        1000,
        '\n');

    NodeBST *node =
        timkiemCauHoi(
            app.db.rootCH,
            id);

    if (node == nullptr ||
        node->data.daXoa)
    {

        veKhungThongBao(
            15,
            15,
            80,
            4);

        hienThongBao(
            15,
            15,
            "Khong tim thay cau hoi!",
            false);

        choNhanPhim(
            15,
            17);

        return;
    }

    CauHoi &ch =
        node->data;

    clearScreen();

    veKhungManHinh(
        2,
        1,
        120,
        24,
        "THONG TIN CAU HOI");

    gotoXY(5, 5);
    cout << "ID      : " << ch.id;

    gotoXY(5, 7);
    cout << "Mon hoc : " << ch.mamh;

    gotoXY(5, 9);
    cout << "Noi dung: " << ch.noidung;

    gotoXY(5, 12);
    cout << "A. " << ch.A;

    gotoXY(5, 14);
    cout << "B. " << ch.B;

    gotoXY(5, 16);
    cout << "C. " << ch.C;

    gotoXY(5, 18);
    cout << "D. " << ch.D;

    gotoXY(5, 21);

    cout << "Dap an dung : "
         << ch.dapan;

    choNhanPhim(
        5,
        23);
}

//================================================
// XOA CAU HOI
//================================================

void uiXoaCauHoi(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        15,
        3,
        80,
        10,
        "XOA CAU HOI");

    int id;

    gotoXY(20, 7);

    cout << "Nhap ID : ";

    cin >> id;

    cin.ignore(
        1000,
        '\n');

    bool kq =
        xoaCauHoi(
            app.db.rootCH,
            id);

    veKhungThongBao(
        15,
        15,
        80,
        4);

    if (kq)
    {

        saveCauHoi(
            app.db.rootCH);

        hienThongBao(
            15,
            15,
            "Xoa thanh cong!",
            true);
    }
    else
    {
        hienThongBao(
            15,
            15,
            "Khong tim thay!",
            false);
    }

    choNhanPhim(
        15,
        17);
}

//================================================
// IN THEO MON
//================================================

void layDSCauHoi(
    NodeBST *root,
    const char *maMH,
    vector<CauHoi *> &ds)
{
    if (root == nullptr)
        return;

    layDSCauHoi(
        root->trai,
        maMH,
        ds);

    if (strcmp(
            root->data.mamh,
            maMH) == 0 &&
        root->data.daXoa == 0)
    {
        ds.push_back(
            &root->data);
    }

    layDSCauHoi(
        root->phai,
        maMH,
        ds);
}

void uiInCauHoiTheoMon(
    AppContext &app)
{

    clearScreen();

    // nhập môn

    veKhungManHinh(
        15,
        2,
        70,
        8,
        "IN CAU HOI THEO MON");

    char maMH[LEN_MAMH];

    gotoXY(20, 6);

    cout
        << "Ma mon hoc : ";

    gotoXY(35, 6);

    cin.getline(
        maMH,
        LEN_MAMH);

    vector<CauHoi *> ds;

    layDSCauHoi(
        app.db.rootCH,
        maMH,
        ds);

    int trang = 0;

    const int soDong = 2;

    while (true)
    {

        clearScreen();

        veKhungManHinh(
            2,
            1,
            110,
            22,
            "DANH SACH CAU HOI");

        gotoXY(5, 4);

        cout
            << "Mon hoc: "
            << maMH;

        int start =
            trang * soDong;

        int y = 6;

        for (
            size_t i = start;
            i < start + soDong &&
            i < ds.size();
            i++)
        {

            CauHoi *ch =
                ds[i];

            gotoXY(5, y++);

            cout
                << "ID: "
                << ch->id;

            gotoXY(5, y++);

            cout
                << "Cau hoi: "
                << ch->noidung;

            gotoXY(8, y++);

            cout
                << "A. "
                << ch->A;

            gotoXY(8, y++);

            cout
                << "B. "
                << ch->B;

            gotoXY(8, y++);

            cout
                << "C. "
                << ch->C;

            gotoXY(8, y++);

            cout
                << "D. "
                << ch->D;

            gotoXY(8, y++);

            setColor(10);

            cout
                << "Dap an dung: "
                << ch->dapan;

            setColor(7);

            y += 1;
        }

        veKhungThongBao(
            2,
            24,
            110,
            3);

        gotoXY(5, 25);

        cout
            << "Trang "
            << trang + 1
            << "/"
            << ((ds.size() + soDong - 1) / soDong);

        gotoXY(45, 25);

        cout
            << "UP/DOWN: Cuon   ESC: Thoat";

        int key =
            _getch();

        if (key == 27)
            break;

        if (key == 224)
        {
            key = _getch();

            // len

            if (key == 72)
            {
                if (trang > 0)
                    trang--;
            }

            // xuong

            if (key == 80)
            {
                if (
                    (trang + 1) * soDong < ds.size())
                    trang++;
            }
        }
    }
}

void uiDemCauHoi(
    AppContext &app)
{

    clearScreen();

    veKhungManHinh(
        15,
        3,
        80,
        10,
        "DEM CAU HOI");

    char maMH[LEN_MAMH];

    gotoXY(20, 7);

    cout << "Ma mon hoc : ";

    gotoXY(33, 7);
    cin.getline(maMH, LEN_MAMH);
    cout << maMH << endl;
    int n = demCauHoiTheoMon(
        app.db.rootCH,
        maMH);

    gotoXY(20, 9);

    cout << "Tong so cau hoi : "
         << n;

    choNhanPhim(
        20,
        11);
}

//================================================
// MENU
//================================================

void menuCauHoi(
    AppContext &app)
{

    const char *ds[] =
        {
            "Them cau hoi",
            "Tim cau hoi",
            "Xoa cau hoi",
            "In cau hoi theo mon",
            "Dem so cau hoi",
            "Quay lai"};

    while (true)
    {

        int chon =
            menuConsole(
                "QUAN LY CAU HOI",
                ds,
                6);

        switch (chon)
        {

        case 0:
            uiThemCauHoi(app);
            break;

        case 1:
            uiTimCauHoi(app);
            break;

        case 2:
            uiXoaCauHoi(app);
            break;

        case 3:
            uiInCauHoiTheoMon(app);
            break;

        case 4:
            uiDemCauHoi(app);
            break;

        case 5:
            return;
        }
    }
}