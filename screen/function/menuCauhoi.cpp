#include "screen/include/menuCauhoi.h"
#include "features/CauHoi/cauhoi.h"
#include "features/Lop/lop.h"
#include "features/Thi/thi.h"
#include "features/MonHoc/monhoc.h"
#include "screen/include/MenuDangNhap.h"
#include <cstdlib>
#include <iostream>
#include "../struct/app_context.h"
#include "screen/include/MenuDangNhap.h"
using namespace std;

void uiThemCauHoi(
    AppContext &app)
{
    CauHoi ch;

    ch.id =
        taoIDMoi(
            app.db.rootCH);

    cout
        << "\nID moi: "
        << ch.id
        << "\n";

    cout
        << "Ma mon hoc: ";

    cin.getline(
        ch.mamh,
        LEN_MAMH);

    cout
        << "Noi dung: ";

    cin.getline(
        ch.noidung,
        LEN_NOIDUNG);

    cout << "A: ";
    cin.getline(
        ch.A,
        LEN_LUACHON);

    cout << "B: ";
    cin.getline(
        ch.B,
        LEN_LUACHON);

    cout << "C: ";
    cin.getline(
        ch.C,
        LEN_LUACHON);

    cout << "D: ";
    cin.getline(
        ch.D,
        LEN_LUACHON);

    cout
        << "Dap an dung (A/B/C/D): ";

    cin >> ch.dapan;

    cin.ignore();

    if (ch.dapan >= 'a' &&
        ch.dapan <= 'z')
    {
        ch.dapan -= 32;
    }

    ch.daXoa = 0;

    if (themCauHoi(
            app.db.rootCH,
            ch))
    {
        cout
            << "\nThem thanh cong!\n";
    }
    else
    {
        cout
            << "\nThem that bai!\n";
    }

    system("pause");
}

void uiTimCauHoi(
    AppContext &app)
{
    int id;

    cout
        << "\nNhap ID: ";

    cin >> id;

    cin.ignore();

    NodeBST *node =
        timkiemCauHoi(
            app.db.rootCH,
            id);

    if (node == nullptr ||
        node->data.daXoa)
    {
        cout
            << "\nKhong tim thay!\n";

        system("pause");
        return;
    }

    CauHoi &ch =
        node->data;

    cout
        << "\nID      : "
        << ch.id;

    cout
        << "\nMon hoc : "
        << ch.mamh;

    cout
        << "\nNoi dung: "
        << ch.noidung;

    cout
        << "\nA. "
        << ch.A;

    cout
        << "\nB. "
        << ch.B;

    cout
        << "\nC. "
        << ch.C;

    cout
        << "\nD. "
        << ch.D;

    cout
        << "\nDap an : "
        << ch.dapan
        << "\n";

    system("pause");
}

void uiXoaCauHoi(
    AppContext &app)
{
    int id;

    cout
        << "\nNhap ID can xoa: ";

    cin >> id;

    cin.ignore();

    if (xoaCauHoi(
            app.db.rootCH,
            id))
    {
        cout
            << "\nXoa thanh cong!\n";
    }
    else
    {
        cout
            << "\nKhong tim thay!\n";
    }

    system("pause");
}
void uiInCauHoiTheoMon(
    AppContext &app)
{
    char maMH[LEN_MAMH];

    cout
        << "\nNhap ma MH: ";

    cin.getline(
        maMH,
        LEN_MAMH);

    cout
        << "\n===== DANH SACH CAU HOI =====\n";

    inCauHoiTheoMon(
        app.db.rootCH,
        maMH);

    cout << "\n";

    system("pause");
}
void uiDemCauHoi(
    AppContext &app)
{
    char maMH[LEN_MAMH];

    cout
        << "\nNhap ma MH: ";

    cin.getline(
        maMH,
        LEN_MAMH);

    CauHoi ds[1000];

    int n =
        layCauHoiTheoMon(
            app.db.rootCH,
            maMH,
            ds,
            1000);

    cout
        << "\nTong so cau hoi: "
        << n
        << "\n";

    system("pause");
}
void menuCauHoi(
    AppContext &app)
{
    int chon;

    do
    {
        system("cls");

        cout << "=========================\n";
        cout << "    QUAN LY CAU HOI\n";
        cout << "=========================\n";

        cout << "1. Them cau hoi\n";
        cout << "2. Tim cau hoi\n";
        cout << "3. Xoa cau hoi\n";
        cout << "4. In cau hoi theo mon\n";
        cout << "5. Dem so cau hoi theo mon\n";
        cout << "0. Quay lai\n";

        cout << "\nLua chon: ";

        cin >> chon;

        cin.ignore(
            1000,
            '\n');

        switch (chon)
        {
        case 1:
            uiThemCauHoi(app);
            break;

        case 2:
            uiTimCauHoi(app);
            break;

        case 3:
            uiXoaCauHoi(app);
            break;

        case 4:
            uiInCauHoiTheoMon(app);
            break;

        case 5:
            uiDemCauHoi(app);
            break;

        case 0:
            break;

        default:
            cout
                << "\nLua chon khong hop le!\n";

            system("pause");
        }

    } while (chon != 0);
}