
#include "auth.h"
#include "struct/global.h"
#include <cstdio>
#include <cstring>
#include <ctime> /* std::strftime, std::localtime */
#include <iostream>

using namespace std;

static void ghiNhatKyDangNhapVaFile(const char *tenHienThi,
                                    bool laGiangVien)
{
    FILE *f = fopen(FILE_NHATKY_DANGNHAP, "a");
    if (!f)
        return;

    time_t t = time(nullptr);
    struct tm *local = std::localtime(&t);
    char thoiDiem[64];

    if (local)
        std::strftime(thoiDiem, sizeof(thoiDiem), "%Y-%m-%d %H:%M:%S", local);
    else
        thoiDiem[0] = '\0';

    fprintf(f, "[%s] %s: %s\n", thoiDiem, laGiangVien ? "GIANG_VIEN"
                                                   : "SINH_VIEN",
            tenHienThi ? tenHienThi : "?");

    fclose(f);
}

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

            ghiNhatKyDangNhapVaFile(username,
                                    true);

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

            ghiNhatKyDangNhapVaFile(sv->masv,
                                    false);

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
