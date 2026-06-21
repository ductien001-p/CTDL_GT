#include <iostream>

#include "decoration/decoration.h"
#include "../struct/app_context.h"

#include "HamHoTro/hamhotro.h"
#include "screen/include/MenuDangNhap.h"

#include "../../features/DangNhap/dangnhap.h"
#include "Validator/input_validate.h"

using namespace std;

bool manHinhDangNhap(
    AppContext &app)
{

    while (true)
    {

        clearScreen();

        // khung chính

        veKhungManHinh(
            15,
            3,
            70,
            14,
            "HE THONG THI TRAC NGHIEM");

        gotoXY(
            20,
            8);

        cout << "Tai khoan : ";

        gotoXY(
            20,
            10);

        cout << "Mat khau  : ";

        char username[LEN_MASV];
        char password[LEN_PASS];

        gotoXY(
            33,
            8);

        nhap(
            username,
            MASINHVIEN);

        gotoXY(
            33,
            10);

        nhap(
            password,
            MATKHAU);

        // khung thong bao

        veKhungThongBao(
            15,
            12,
            70,
            4);

        if (
            kiemTraDangNhap(
                app,
                username,
                password))
        {

            hienThongBao(
                15,
                12,
                "Dang nhap thanh cong!",
                true);

            choNhanPhim(
                15,
                14);

            return true;
        }

        hienThongBao(
            15,
            12,
            "Sai tai khoan hoac mat khau!",
            false);

        choNhanPhim(
            15,
            14);
    }
}

bool manHinhBatDau(
    AppContext &app)
{

    const char *ds[] =
        {
            "Dang nhap",
            "Thoat"};

    while (true)
    {

        int chon =
            menuConsole(
                "HE THONG THI TRAC NGHIEM",
                ds,
                2);

        switch (chon)
        {

        case 0:

            if (
                manHinhDangNhap(app))
            {
                return true;
            }

            break;

        case 1:

            return false;
        }
    }
}