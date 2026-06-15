#include "screen/include/menuMonhoc.h"
#include "features/MonHoc/monhoc.h"
#include <cstdlib>
#include <iostream>
#include "../struct/app_context.h"
#include "screen/include/MenuDangNhap.h"
using namespace std;

void uiThemMonHoc(
    AppContext &app)
{
    MonHoc mh;

    cout << "\n===== THEM MON HOC =====\n";

    cout << "Ma MH: ";
    cin.getline(
        mh.mamh,
        LEN_MAMH);

    cout << "Ten MH: ";
    cin.getline(
        mh.tenmh,
        LEN_TENMH);

    cout << "So tin chi: ";
    cin >> mh.soTinChi;

    cin.ignore();

    mh.daXoa = 0;

    if (themMonHoc(
            app.db.dsMH,
            mh))
    {
        cout
            << "\nThem thanh cong!\n";
    }
    else
    {
        cout
            << "\nMon hoc da ton tai!\n";
    }

    system("pause");
}

void uiTimMonHoc(
    AppContext &app)
{
    char maMH[LEN_MAMH];

    cout << "\nNhap ma MH: ";

    cin.getline(
        maMH,
        LEN_MAMH);

    MonHoc *mh =
        timMonHoc(
            app.db.dsMH,
            maMH);

    if (mh == nullptr)
    {
        cout
            << "\nKhong tim thay!\n";
    }
    else
    {
        cout
            << "\nMa MH     : "
            << mh->mamh;

        cout
            << "\nTen MH    : "
            << mh->tenmh;

        cout
            << "\nSo tin chi: "
            << mh->soTinChi
            << "\n";
    }

    system("pause");
}
void uiSuaMonHoc(
    AppContext &app)
{
    char maMH[LEN_MAMH];

    cout
        << "\nNhap ma MH can sua: ";

    cin.getline(
        maMH,
        LEN_MAMH);

    MonHoc *cu =
        timMonHoc(
            app.db.dsMH,
            maMH);

    if (cu == nullptr)
    {
        cout
            << "\nKhong tim thay!\n";

        system("pause");
        return;
    }

    MonHoc moi = *cu;

    cout
        << "Ten moi: ";

    cin.getline(
        moi.tenmh,
        LEN_TENMH);

    cout
        << "So tin chi moi: ";

    cin >> moi.soTinChi;

    cin.ignore();

    if (suaMonHoc(
            app.db.dsMH,
            maMH,
            moi))
    {
        cout
            << "\nCap nhat thanh cong!\n";
    }
    else
    {
        cout
            << "\nCap nhat that bai!\n";
    }

    system("pause");
}

void uiXoaMonHoc(
    AppContext &app)
{
    char maMH[LEN_MAMH];

    cout
        << "\nNhap ma MH can xoa: ";

    cin.getline(
        maMH,
        LEN_MAMH);

    if (xoaMonHoc(
            app.db.dsMH,
            maMH))
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

void uiInDSMonHoc(
    AppContext &app)
{
    cout
        << "\n===== DANH SACH MON HOC =====\n";

    inDSMonHoc(
        app.db.dsMH);

    cout << "\n";

    system("pause");
}

void menuMonHoc(
    AppContext &app)
{
    int chon;

    do
    {
        system("cls");

        cout << "=========================\n";
        cout << "    QUAN LY MON HOC\n";
        cout << "=========================\n";

        cout << "1. Them mon hoc\n";
        cout << "2. Tim mon hoc\n";
        cout << "3. Sua mon hoc\n";
        cout << "4. Xoa mon hoc\n";
        cout << "5. In danh sach mon hoc\n";
        cout << "0. Quay lai\n";

        cout << "\nLua chon: ";

        cin >> chon;

        cin.ignore(
            1000,
            '\n');

        switch (chon)
        {
        case 1:
            uiThemMonHoc(app);
            break;

        case 2:
            uiTimMonHoc(app);
            break;

        case 3:
            uiSuaMonHoc(app);
            break;

        case 4:
            uiXoaMonHoc(app);
            break;

        case 5:
            uiInDSMonHoc(app);
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
