#include <iostream>

#include "dangnhap.h"
#include "../../struct/app_context.h"
#include "../SinhVien/sinhvien.h"
#include "../../HamHoTro/hamhotro.h"
#include "Validator/input_validate.h"

using namespace std;

bool dangNhap(AppContext &app)
{
    char username[LEN_MASV];
    char password[LEN_PASS];

    cout << "\n====================================\n";
    cout << "      HE THONG THI TRAC NGHIEM\n";
    cout << "====================================\n";

    cout << "Tai khoan: ";
    nhap(username, MASINHVIEN);

    cout << "Mat khau : ";
    nhap(password, MATKHAU);

    // Tai khoan giao vien

    if (soSanhChuoi(username, "GV") &&
        soSanhChuoi(password, "GV"))
    {
        app.session.username = "GV";
        app.session.giaovien = true;
        return true;
    }

    // Tai khoan sinh vien

    SinhVien *sv =
        timSinhVien(
            app.db.dsLop,
            username);

    if (sv == nullptr)
        return false;

    if (!soSanhChuoi(
            sv->password,
            password))
    {
        return false;
    }

    app.session.username = sv->masv;
    app.session.giaovien = false;

    return true;
}

void dangXuat(AppContext &app)
{
    app.session.username = "";
    app.session.giaovien = false;
    app.session.svHientai = nullptr;
}