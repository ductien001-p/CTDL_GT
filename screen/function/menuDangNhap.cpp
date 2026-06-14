#include <iostream>

#include "screen/include/MenuDangNhap.h"
#include "../../features/DangNhap/dangnhap.h"

using namespace std;

bool manHinhDangNhap(
    AppContext &app)
{
    int chon;

    while (true)
    {
        system("cls");

        cout << "\n";
        cout << "========================================\n";
        cout << "       HE THONG THI TRAC NGHIEM\n";
        cout << "========================================\n";

        cout << "\n";
        cout << "1. Dang nhap\n";
        cout << "0. Thoat\n";

        cout << "\nLua chon: ";
        cin >> chon;

        cin.ignore(
            1000,
            '\n');

        switch (chon)
        {
        case 1:
        {
            if (dangNhap(app))
            {
                cout
                    << "\nDang nhap thanh cong!\n";

                system("pause");

                return true;
            }

            cout
                << "\nSai tai khoan hoac mat khau!\n";

            system("pause");

            break;
        }

        case 0:
        {
            return false;
        }

        default:
        {
            cout
                << "\nLua chon khong hop le!\n";

            system("pause");
        }
        }
    }
}