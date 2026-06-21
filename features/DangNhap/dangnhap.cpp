#include <iostream>

#include "dangnhap.h"
#include "../../struct/app_context.h"
#include "../SinhVien/sinhvien.h"
#include "../../HamHoTro/hamhotro.h"
#include "Validator/input_validate.h"

using namespace std;

bool kiemTraDangNhap(
    AppContext &app,
    const char *username,
    const char *password)
{
    if (soSanhChuoi(username, "GV") &&
        soSanhChuoi(password, "GV"))
    {
        app.session.username = "GV";
        app.session.giaovien = true;
        app.session.svHientai = nullptr;

        return true;
    }

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
    app.session.svHientai = sv;

    return true;
}

void dangXuat(
    AppContext &app)
{
    app.session.username = "";
    app.session.giaovien = false;
    app.session.svHientai = nullptr;
}