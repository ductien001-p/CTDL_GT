#include "screen/include/menuQL_Thi_SV.h"
#include "features/Lop/lop.h"
#include "features/MonHoc/monhoc.h"
#include "features/SinhVien/sinhvien.h"
#include "features/Thi/thi.h"
#include "features/DiemThi/diemthi.h"
#include <cstdlib>
#include <iostream>
#include "../struct/app_context.h"
#include "struct/struct.h"
#include "screen/include/MenuDangNhap.h"
using namespace std;

void uiThiTracNghiem(
    AppContext &app)
{
    SinhVien *sv =
        timSinhVien(
            app.db.dsLop,
            app.session.username.c_str());

    if (sv == nullptr)
    {
        cout
            << "\nKhong tim thay sinh vien!\n";

        system("pause");
        return;
    }

    char maMH[LEN_MAMH];

    cout
        << "\n===== THI TRAC NGHIEM =====\n";

    cout
        << "Ma mon hoc: ";

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
            << "\nMon hoc khong ton tai!\n";

        system("pause");
        return;
    }

    cout
        << "So cau hoi: ";

    cin >> mh->soCauHoiThi;

    cout
        << "So phut: ";

    cin >> mh->soPhutThi;

    cin.ignore();

    batDauThi(
        sv,
        app.db.rootCH,
        maMH,
        mh->soCauHoiThi,
        mh->soPhutThi);

    system("pause");
}

void uiXemDiem(
    AppContext &app)
{
    SinhVien *sv =
        timSinhVien(
            app.db.dsLop,
            app.session.username.c_str());

    if (sv == nullptr)
    {
        cout
            << "\nKhong tim thay sinh vien!\n";

        system("pause");
        return;
    }

    cout
        << "\n===== BANG DIEM =====\n";

    DiemThi *dt =
        sv->dsDiem;

    if (dt == nullptr)
    {
        cout
            << "\nChua co diem thi!\n";

        system("pause");
        return;
    }

    while (dt)
    {
        cout
            << "\nMon hoc : "
            << dt->mamh;

        cout
            << "\nDiem    : "
            << dt->diem;

        cout
            << "\nSo dung : "
            << dt->soCauDung
            << "/"
            << dt->tongCau;

        cout
            << "\n------------------";

        dt = dt->tiep;
    }

    cout << "\n";

    system("pause");
}

void uiChiTietBaiThi(
    AppContext &app)
{
    SinhVien *sv =
        timSinhVien(
            app.db.dsLop,
            app.session.username.c_str());

    if (sv == nullptr)
    {
        cout
            << "\nKhong tim thay sinh vien!\n";

        system("pause");
        return;
    }

    char maMH[LEN_MAMH];

    cout
        << "\nNhap ma mon hoc: ";

    cin.getline(
        maMH,
        LEN_MAMH);

    inChiTietBaiThi(
        sv,
        maMH,
        app.db.rootCH);

    system("pause");
}

void menuQuanLyThiSinhVien(
    AppContext &app)
{
    int chon;

    do
    {
        system("cls");

        cout << "=========================\n";
        cout << "       SINH VIEN\n";
        cout << "=========================\n";

        cout << "Dang nhap: "
             << app.session.username
             << "\n\n";

        cout << "1. Thi trac nghiem\n";
        cout << "2. Xem diem\n";
        cout << "3. Xem chi tiet bai thi\n";
        cout << "0. Dang xuat\n";

        cout << "\nLua chon: ";

        cin >> chon;

        cin.ignore(
            1000,
            '\n');

        switch (chon)
        {
        case 1:
            uiThiTracNghiem(app);
            break;

        case 2:
            uiXemDiem(app);
            break;

        case 3:
            uiChiTietBaiThi(app);
            break;

        case 0:
            app.session.username = "";
            break;

        default:
            cout
                << "\nLua chon khong hop le!\n";

            system("pause");
        }

    } while (chon != 0);
}