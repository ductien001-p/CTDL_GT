#include <iostream>

#include "dangnhap.h"
#include "../../struct/app_context.h"
#include "../SinhVien/sinhvien.h"
#include "../../HamHoTro/hamhotro.h"

using namespace std;

bool dangNhap(AppContext &app)
{
    char username[LEN_MASV];
    char password[LEN_PASS];

    cout << "\n====================================\n";
    cout << "      HE THONG THI TRAC NGHIEM\n";
    cout << "====================================\n";

    cout << "Tai khoan: ";
    cin.getline(username, LEN_MASV);

    cout << "Mat khau : ";
    cin.getline(password, LEN_PASS);

    // Tai khoan giao vien

    if (soSanhChuoi(username, "GV") == 0 &&
        soSanhChuoi(password, "GV") == 0)
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

    if (soSanhChuoi(
            sv->password,
            password) != 0)
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