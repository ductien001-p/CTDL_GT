#include "screen/include/menuGV.h"
#include "screen/include/menuLop.h"
#include "screen/include/menuQLSV.h"
#include "screen/include/menuMonHoc.h"
#include "screen/include/menuCauHoi.h"
#include "screen/include/menuBangDiem.h"
#include "screen/include/MenuDangNhap.h"

#include <cstdlib>
#include <iostream>
#include "../struct/app_context.h"
using namespace std;
//=========================================Menu Giao vien===========================//
void menuGV(AppContext &app)
{
    (void)app;
    int choice;

    do
    {
        system("cls");

        cout << "====================================\n";
        cout << "          MENU GIAO VIEN\n";
        cout << "====================================\n";
        cout << "1. Quan ly lop\n";
        cout << "2. Quan ly sinh vien\n";
        cout << "3. Quan ly mon hoc\n";
        cout << "4. Quan ly cau hoi\n";
        cout << "5. Bang diem\n";
        cout << "0. Dang xuat\n";
        cout << "------------------------------------\n";
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            menuLop(app);
            break;
        case 2:
            menuQuanLySinhVien(app);
            break;
        case 3:
            menuMonHoc(app);
            break;
        case 4:
            menuCauHoi(app);
            break;
        case 5:
            menuBangDiem(app);
            break;
        }

    } while (choice != 0);
}