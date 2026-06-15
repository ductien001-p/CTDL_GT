#include "screen/include/menuBangDiem.h"
#include "features/DiemThi/diemthi.h"
#include "features/Thi/thi.h"
#include "features/DiemThi/ketquabaithi.h"
#include "features/Lop/lop.h"
#include "features/MonHoc/monhoc.h"
#include "screen/include/MenuDangNhap.h"
#include <cstdlib>
#include <iostream>
#include "../struct/app_context.h"
#include "screen/include/MenuDangNhap.h"
using namespace std;
void uiBangDiem(
    AppContext &app)
{
    char maLop[LEN_MALOP];
    char maMH[LEN_MAMH];

    cout << "Ma lop: ";
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
            << "Khong tim thay lop!\n";

        return;
    }

    cout << "Ma mon hoc: ";
    cin.getline(
        maMH,
        LEN_MAMH);

    inBangDiemLop(
        lop,
        maMH);
}
void menuBangDiem(
    AppContext &app)
{
    int chon;

    do
    {
        system("cls");

        cout << "=========================\n";
        cout << "       BANG DIEM\n";
        cout << "=========================\n";

        cout << "1. In bang diem lop\n";
        cout << "0. Quay lai\n";

        cout << "\nLua chon: ";

        cin >> chon;

        cin.ignore(
            1000,
            '\n');

        switch (chon)
        {
        case 1:
            uiBangDiem(app);
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