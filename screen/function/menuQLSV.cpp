#include "screen/include/menuQLSV.h"
#include "features/SinhVien/sinhvien.h"
#include <cstdlib>
#include <iostream>
#include "../struct/app_context.h"
#include "../../Validator/input_validate.h"
#include "screen/include/MenuDangNhap.h"
using namespace std;

void uiThemSinhVien(
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
            << "\nKhong tim thay lop!\n";

        system("pause");
        return;
    }

    char masv[LEN_MASV];
    char ho[LEN_HO];
    char ten[LEN_TEN];
    char pass[LEN_PASS];

    int phai;

    cout << "Ma SV: ";

    nhap(masv, MASINHVIEN);

    cout
        << "Ho: ";

    nhap(ho, HOTEN);

    cout
        << "Ten: ";

    nhap(ten, HOTEN);

    cout << "Phai (0-Nam,1-Nu): ";
    cin >> phai;

    cin.ignore();

    cout << "Password: ";

    nhap(pass, MATKHAU);

    SinhVien *sv =
        taoSinhVien(
            masv,
            ho,
            ten,
            phai,
            pass);

    if (themSinhVien(
            lop,
            sv))
    {
        saveSinhVien(app.db.dsLop);
        saveLop(app.db.dsLop);
        cout
            << "\nThem thanh cong!\n";
    }
    else
    {
        delete sv;

        cout
            << "\nThem that bai!\n";
    }

    system("pause");
}

void uiTimSinhVien(
    AppContext &app)
{
    char masv[LEN_MASV];

    cout
        << "\nNhap ma SV: ";

    cin.getline(
        masv,
        LEN_MASV);

    SinhVien *sv =
        timSinhVien(
            app.db.dsLop,
            masv);

    if (sv == nullptr)
    {
        cout
            << "\nKhong tim thay!\n";
    }
    else
    {
        cout
            << "\nMa SV : "
            << sv->masv;

        cout
            << "\nHo    : "
            << sv->ho;

        cout
            << "\nTen   : "
            << sv->ten;

        cout
            << "\nPhai  : "
            << (sv->phai == PHAI_NAM
                    ? "Nam"
                    : "Nu");

        cout << "\n";
    }

    system("pause");
}

void uiXoaSinhVien(
    AppContext &app)
{
    char maLop[LEN_MALOP];

    cout
        << "\nNhap ma lop: ";

    cin.getline(
        maLop,
        LEN_MALOP);

    Lop *lop =
        timLop(
            app.db.dsLop,
            maLop);

    if (lop == nullptr)
    {
        cout
            << "\nKhong tim thay lop!\n";

        system("pause");
        return;
    }

    char masv[LEN_MASV];

    cout
        << "Nhap ma SV can xoa: ";

    cin.getline(
        masv,
        LEN_MASV);

    if (xoaSinhVien(
            lop,
            masv))
    {
        saveSinhVien(app.db.dsLop);
        saveLop(app.db.dsLop);
        cout
            << "\nXoa thanh cong!\n";
    }
    else
    {
        cout
            << "\nKhong tim thay SV!\n";
    }

    system("pause");
}

void uiInDSSinhVien(
    AppContext &app)
{
    char maLop[LEN_MALOP];

    cout
        << "\nNhap ma lop: ";

    cin.getline(
        maLop,
        LEN_MALOP);

    Lop *lop =
        timLop(
            app.db.dsLop,
            maLop);

    if (lop == nullptr)
    {
        cout
            << "\nKhong tim thay lop!\n";

        system("pause");
        return;
    }

    inDSSinhVien(lop);

    cout << "\n";

    system("pause");
}

void menuQuanLySinhVien(
    AppContext &app)
{
    int chon;

    do
    {
        system("cls");

        cout << "=========================\n";
        cout << "   QUAN LY SINH VIEN\n";
        cout << "=========================\n";

        cout << "1. Them sinh vien vao lop\n";
        cout << "2. Tim sinh vien\n";
        cout << "3. Xoa sinh vien\n";
        cout << "4. In DSSV theo lop\n";
        cout << "0. Quay lai\n";

        cout << "\nLua chon: ";

        cin >> chon;

        cin.ignore(
            1000,
            '\n');

        switch (chon)
        {
        case 1:
            uiThemSinhVien(app);
            break;

        case 2:
            uiTimSinhVien(app);
            break;

        case 3:
            uiXoaSinhVien(app);
            break;

        case 4:
            uiInDSSinhVien(app);
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