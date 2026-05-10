
#include "auth.h"
#include <iostream>
#include <cstring>
#include "global.h"
using namespace std;

void themTaiKhoanGV(const char *username,
                    const char *password)
{
    if (soGiaoVien >= MAX_GIAO_VIEN)
    {
        cout << "Danh sach GV da day\n";
        return;
    }

    strcpy(dsGiaoVien[soGiaoVien].username,
           username);

    strcpy(dsGiaoVien[soGiaoVien].password,
           password);

    soGiaoVien++;
}

/* =============================================================
 * ĐĂNG NHẬP
 * ============================================================= */

bool dangNhap(const char *username,
              const char *password)
{
    /* ---------------------------------------------------------
     * 1. CHECK GIẢNG VIÊN
     * --------------------------------------------------------- */

    for (int i = 0; i < soGiaoVien; i++)
    {
        if (strcmp(dsGiaoVien[i].username,
                   username) == 0 &&

            strcmp(dsGiaoVien[i].password,
                   password) == 0)
        {
            isAdmin = ROLE_GIANGVIEN;

            svDangNhap = NULL;

            cout << "Dang nhap giang vien thanh cong\n";

            return true;
        }
    }

    /* ---------------------------------------------------------
     * 2. CHECK SINH VIÊN
     * --------------------------------------------------------- */

    SinhVien *sv = timSV(username);

    if (sv != NULL)
    {
        if (strcmp(sv->password,
                   password) == 0)
        {
            isAdmin = ROLE_SINHVIEN;

            svDangNhap = sv;

            cout << "Dang nhap sinh vien thanh cong\n";

            return true;
        }
    }

    /* ---------------------------------------------------------
     * 3. THẤT BẠI
     * --------------------------------------------------------- */

    cout << "Sai tai khoan hoac mat khau\n";

    return false;
}

/* =============================================================
 * ĐĂNG XUẤT
 * ============================================================= */

void dangXuat()
{
    isAdmin = ROLE_SINHVIEN;

    svDangNhap = NULL;

    cout << "Da dang xuat\n";
}

/* =============================================================
 * HIỂN THỊ USER ĐANG LOGIN
 * ============================================================= */

void hienThongTinDangNhap()
{
    if (isAdmin == ROLE_GIANGVIEN)
    {
        cout << "[GIANG VIEN]\n";
    }
    else
    {
        if (svDangNhap != NULL)
        {
            cout << "[SINH VIEN]\n";
            cout << "Ma SV: "
                 << svDangNhap->masv
                 << endl;

            cout << "Ho ten: "
                 << svDangNhap->ho
                 << " "
                 << svDangNhap->ten
                 << endl;
        }
        else
        {
            cout << "Chua dang nhap\n";
        }
    }
}
