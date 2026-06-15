#include <iostream>
#include "decoration/decoration.h"
#include "../struct/app_context.h"

#include "screen/include/MenuDangNhap.h"
#include "../../features/DangNhap/dangnhap.h"

using namespace std;

bool manHinhDangNhap(
    AppContext &app)
{

    while (true)
    {
        system("cls");

        const char *ds[] =
            {
                "Dang nhap",
                "Thoat"};

        int chon =
            menuConsole(
                "HE THONG THI TRAC NGHIEM",
                ds,
                2);

        switch (chon)
        {
        case 0:
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

        case 1:
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