/**
 * Chương trình minh hoạ: đăng nhập (GV / SV) + đọc/ghi tài khoản GV từ .txt +
 * ghi nhật ký đăng nhập thành công vào file text.
 */

#include "features/Auth/auth.h"
#include "Fileio/fileio.h"
#include "struct/global.h"
#include "struct/struct.h"
#include <cstring>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <string>
#include "features/Lop/lop.h"
#include "Validator/input_validate.h"

using namespace std;

namespace fs = std::filesystem;

static void tatMacDinhNeuChuaCoTaiLieuTxt(void)
{
    int doc = docDsGiaoVienTuTxt(FILE_GV_TXT);
    int docLop = taiDsLop(FILE_LOP_TXT);
    (void)docLop;
    if (!(doc == FILE_OK && soGiaoVien > 0))
    {
        cout << "(Chua doc duoc ds GV hoac file trong — tao tai khoan mac dinh GV / admin)"
             << "\n";

        soGiaoVien = 0;
        soLop = 0;
        strncpy(dsGiaoVien[0].username,
                "GV",
                LEN_MASV - 1);

        dsGiaoVien[0].username[LEN_MASV - 1] = '\0';

        strncpy(dsGiaoVien[0].password,
                "admin",
                LEN_PASS - 1);

        dsGiaoVien[0].password[LEN_PASS - 1] = '\0';

        soGiaoVien = 1;

        if (luuDsGiaoVienRaTxt(FILE_GV_TXT) == FILE_OK)
            cout << "Da ghi tai khoan mac dinh vao: "
                 << FILE_GV_TXT
                 << "\n";
    }
}

static void inMenuGiangVien(void)
{
    cout << "\n--- Menu Giang Vien ---\n"
         << "1. Them lop\n"
         << "2. Them sinh vien vao lop\n"
         << "3. Xem danh sach lop\n"
         << "4. Xem danh sach sinh vien trong lop\n"
         << "5. Ghi lai danh sach tai khoan GV ra file .txt\n"
         << "6. Dang xuat\n"
         << "0. Thoat chuong trinh\n"
         << "Chon: ";
}

static void inMenuSinhVien(void)
{
    cout << "\n--- Menu Sinh Vien ---\n"
         << "1. Xem diem thi\n"
         << "2. Xem ket qua thi chi tiet\n"
         << "3. Lam bai thi\n"
         << "4. Dang xuat\n"
         << "0. Thoat chuong trinh\n"
         << "Chon: ";
}

static void choNhanEnterDeTiepTuc()
{
    cout << "\nNhan Enter de quay lai menu...";
    string dummy;
    getline(std::cin, dummy);
}

int main()
{
    try
    {
        fs::create_directories("data");
    }
    catch (...)
    {
    }

    cout << "=== He thong thi trac nghiem — dang nhap ===\n"
         << "(Tai khoan GV trong file \""
         << FILE_GV_TXT
         << "\"; sinh vien dang nhap bang ma SV khi DB lop trong bo nho sau nay).\n";

    tatMacDinhNeuChuaCoTaiLieuTxt();
    taiDsSinhVien(FILE_SV_TXT);

    for (;;)
    {
        cout << "\n--- Dang nhap ---\n"
             << "(de trong ten de thoat muc nay)\n"
             << "Ten dang nhap / ma SV: ";

        string user;

        user = nhap(ALPHANUMERIC);

        if (user.empty())
            break;

        std::cout << "Mat khau: ";

        std::string pass;

        std::getline(std::cin,
                     pass);

        if (!dangNhap(user.c_str(),
                      pass.c_str()))
            continue;

        bool session = true;

        while (session)
        {
            if (isAdmin == ROLE_GIANGVIEN)
                inMenuGiangVien();
            else
                inMenuSinhVien();

            std::string choice;

            std::getline(std::cin,
                         choice);

            if (isAdmin == ROLE_GIANGVIEN && choice == "1")
            {
                std::cout << "Nhap ma lop: ";
                std::string malop;
                std::getline(std::cin, malop);
                std::cout << "Nhap ten lop: ";
                std::string tenlop;
                std::getline(std::cin, tenlop);
                std::cout << "Nhap so sinh vien: ";
                std::string soSVText;
                std::getline(std::cin, soSVText);

                int soSV = 0;
                try
                {
                    soSV = std::stoi(soSVText);
                }
                catch (...)
                {
                    std::cout << "So sinh vien khong hop le.\n";
                    choNhanEnterDeTiepTuc();
                    continue;
                }

                if (malop.empty() || tenlop.empty() || soSV < 0)
                {
                    std::cout << "Du lieu lop khong hop le.\n";
                    choNhanEnterDeTiepTuc();
                    continue;
                }

                if (timLop(malop.c_str()) >= 0)
                {
                    std::cout << "Them lop that bai: ma lop da ton tai.\n";
                    choNhanEnterDeTiepTuc();
                    continue;
                }

                int soLopTruoc = soLop;
                themLop(malop.c_str(), tenlop.c_str(), soSV);
                if (soLop == soLopTruoc)
                {
                    std::cout << "Them lop that bai: khong du bo nho hoac du lieu khong hop le.\n";
                    choNhanEnterDeTiepTuc();
                    continue;
                }

                int kq = luuDsLop(FILE_LOP_TXT);
                if (kq == FILE_OK)
                    std::cout << "Them lop thanh cong. Da luu vao \""
                              << FILE_LOP_TXT
                              << "\"\n";
                else
                    std::cerr << "Them lop xong nhung loi luu file (ma "
                              << kq
                              << ")\n";
                Indanhsachlop();
                choNhanEnterDeTiepTuc();
            }
            else if (isAdmin == ROLE_GIANGVIEN && choice == "2")
            {
                std::cout << "Nhap ma lop: ";
                std::string malop;
                std::getline(std::cin, malop);

                std::cout << "Nhap ma sinh vien: ";
                std::string masv;
                std::getline(std::cin, masv);

                std::cout << "Nhap ho: ";
                std::string ho;
                std::getline(std::cin, ho);

                std::cout << "Nhap ten: ";
                std::string ten;
                std::getline(std::cin, ten);

                std::cout << "Nhap phai (0=Nam, 1=Nu): ";
                std::string phaiText;
                std::getline(std::cin, phaiText);

                std::cout << "Nhap mat khau: ";
                std::string password;
                std::getline(std::cin, password);

                int phai = -1;
                try
                {
                    phai = std::stoi(phaiText);
                }
                catch (...)
                {
                    std::cout << "Phai khong hop le.\n";
                    choNhanEnterDeTiepTuc();
                    continue;
                }

                bool ok = themSinhVienVaoLop(malop.c_str(),
                                             masv.c_str(),
                                             ho.c_str(),
                                             ten.c_str(),
                                             phai,
                                             password.c_str());

                if (!ok)
                {
                    std::cout << "Them sinh vien that bai (lop khong ton tai, ma SV trung, hoac du lieu khong hop le).\n";
                    choNhanEnterDeTiepTuc();
                    continue;
                }

                int kqLop = luuDsLop(FILE_LOP_TXT);
                int kqSv = luuDsSinhVien(FILE_SV_TXT);

                if (kqLop == FILE_OK && kqSv == FILE_OK)
                    std::cout << "Them sinh vien thanh cong va da luu du lieu.\n";
                else
                    std::cout << "Them sinh vien thanh cong nhung co loi khi luu file (lop="
                              << kqLop
                              << ", sinhvien="
                              << kqSv
                              << ").\n";
                choNhanEnterDeTiepTuc();
            }
            else if (isAdmin == ROLE_GIANGVIEN && choice == "3")
            {
                Indanhsachlop();
                choNhanEnterDeTiepTuc();
            }
            else if (isAdmin == ROLE_GIANGVIEN && choice == "4")
            {
                std::cout << "Nhap ma lop can xem: ";
                std::string malop;
                std::getline(std::cin, malop);
                InDanhSachSinhVienTrongLop(malop.c_str());
                choNhanEnterDeTiepTuc();
            }
            else if (isAdmin == ROLE_GIANGVIEN && choice == "5")
            {
                int kq = luuDsGiaoVienRaTxt(FILE_GV_TXT);

                if (kq == FILE_OK)
                    std::cout << "Da luu tai khoan GV vao \""
                              << FILE_GV_TXT
                              << "\"\n";
                else
                    std::cerr << "Loi luu file (ma "
                              << kq
                              << ")\n";
                choNhanEnterDeTiepTuc();
            }
            else if (isAdmin == ROLE_GIANGVIEN && choice == "6")
            {
                dangXuat();
                session = false;
            }
            else if (isAdmin == ROLE_SINHVIEN && choice == "1")
            {
                /* TODO: Xem diem thi sinh vien dang nhap */
            }
            else if (isAdmin == ROLE_SINHVIEN && choice == "2")
            {
                /* TODO: Xem ket qua thi chi tiet sinh vien dang nhap */
            }
            else if (isAdmin == ROLE_SINHVIEN && choice == "3")
            {
                /* TODO: Lam bai thi cho sinh vien dang nhap */
            }
            else if (isAdmin == ROLE_SINHVIEN && choice == "4")
            {
                dangXuat();
                session = false;
            }
            else if (choice == "0")
            {
                dangXuat();
                return 0;
            }
            else
            {
                std::cout << "Khong hop le.\n";
            }
        }
    }

    std::cout << "Tam biet.\n";
    return 0;
}
