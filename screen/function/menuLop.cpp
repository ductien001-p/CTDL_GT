#include "features/Lop/lop.h"
#include <iostream>
#include <cstring>
#include "../../HamHoTro/hamhotro.h"
#include "../../Validator/input_validate.h"
#include "screen/include/menuLop.h"

using namespace std;

void uiThemLop(
    AppContext &app)
{
    char maLop[LEN_MALOP];
    char tenLop[LEN_TENLOP];

    cout << "\n===== THEM LOP =====\n";

    cout << "Ma lop: ";
    nhap(maLop, MALOP);

    cout << "Ten lop: ";

    nhap(tenLop, TENLOP);

    if (themLop(
            app.db.dsLop,
            maLop,
            tenLop))
    {
        saveLop(app.db.dsLop);
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

void uiTimLop(
    AppContext &app)
{
    char maLop[LEN_MALOP];

    cout << "\nNhap ma lop: ";

    nhap(maLop, MALOP);

    Lop *lop =
        timLop(
            app.db.dsLop,
            maLop);

    if (lop == nullptr)
    {
        cout
            << "\nKhong tim thay!\n";
    }
    else
    {
        cout
            << "\nMa lop : "
            << lop->malop;

        cout
            << "\nTen lop: "
            << lop->tenlop;

        cout
            << "\nSo SV  : "
            << lop->soSV
            << "\n";
    }

    system("pause");
}

void uiXoaLop(
    AppContext &app)
{
    char maLop[LEN_MALOP];

    cout
        << "\nNhap ma lop can xoa: ";

    nhap(maLop, MALOP);

    if (xoaLop(
            app.db.dsLop,
            maLop))
    {
        saveLop(app.db.dsLop);
        saveSinhVien(app.db.dsLop);
        cout
            << "\nXoa thanh cong!\n";
    }
    else
    {
        cout
            << "\nKhong tim thay lop!\n";
    }

    system("pause");
}

void uiInDSLop(
    AppContext &app)
{
    cout
        << "\n===== DANH SACH LOP =====\n";

    inDSLop(
        app.db.dsLop);

    cout << "\n";

    system("pause");
}

void menuLop(
    AppContext &app)
{
    int chon;

    do
    {
        system("cls");

        cout << "=====================\n";
        cout << "     QUAN LY LOP\n";
        cout << "=====================\n";

        cout << "1. Them lop\n";
        cout << "2. Tim lop\n";
        cout << "3. Xoa lop\n";
        cout << "4. In danh sach lop\n";
        cout << "0. Quay lai\n";

        cout << "\nLua chon: ";

        cin >> chon;

        cin.ignore(
            1000,
            '\n');

        switch (chon)
        {
        case 1:
            uiThemLop(app);
            break;

        case 2:
            uiTimLop(app);
            break;

        case 3:
            uiXoaLop(app);
            break;

        case 4:
            uiInDSLop(app);
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