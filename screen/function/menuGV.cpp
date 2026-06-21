#include "screen/include/menuGV.h"
#include "screen/include/menuLop.h"
#include "screen/include/menuQLSV.h"
#include "screen/include/menuMonHoc.h"
#include "screen/include/menuCauHoi.h"
#include "screen/include/menuBangDiem.h"
#include "screen/include/MenuDangNhap.h"
#include "decoration/decoration.h"
#include <cstdlib>
#include <iostream>
#include "../struct/app_context.h"
#include "HamHoTro/hamhotro.h"
#include "decoration/decoration.h"
using namespace std;
//=========================================Menu Giao vien===========================//
void menuGV(AppContext &app)
{
    const char *ds[] =
        {
            "Quan ly lop",
            "Quan ly sinh vien",
            "Quan ly mon hoc",
            "Quan ly cau hoi",
            "Bang diem",
            "Dang xuat"};

    while (true)
    {
        int chon =
            menuConsole(
                "MENU GIAO VIEN",
                ds,
                6);

        switch (chon)
        {
        case 0:
            menuLop(app);
            break;

        case 1:
            menuQuanLySinhVien(app);
            break;

        case 2:
            menuMonHoc(app);
            break;

        case 3:
            menuCauHoi(app);
            break;

        case 4:
            menuBangDiem(app);
            break;

        case 5:
            return;
        }
    }
}