#include "thi.h"
#include "../../HamHoTro/hamhotro.h"
#include "../../features/SinhVien/sinhvien.h"
#include "../../features/DiemThi/diemthi.h"
#include "../../features/CauHoi/cauhoi.h"
#include "../../struct/app_context.h"
#include "../../features/DiemThi/ketquabaithi.h"
#include "../../Validator/input_validate.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <atomic>
#include <ctime>
#include <conio.h>
#define WIN32_LEAN_AND_MEAN

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <time.h>
#include "../struct/struct.h"

using namespace std;

std::atomic<bool> hetGio(false);

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void thoiGianDemNguoc(int soPhut)
{
    int giay = soPhut * 60;
    while (giay > 0 && !hetGio)
    {
        // CÃ³ thá»ƒ in thá»i gian ra gÃ³c mÃ n hÃ¬nh táº¡i Ä‘Ã¢y báº±ng gotoxy
        gotoxy(60, 0);
        cout << "Thoi gian con lai: " << giay / 60 << ":" << (giay % 60 < 10 ? "0" : "") << giay % 60 << "   ";
        Sleep(1000);
        giay--;
    }
    if (hetGio == 0)
    {
        system("cls");
        cout << "Het thoi gian lam bai, nhan phim bat ky de xem diem!";
    }
    hetGio = true; // Háº¿t giá»
}

int layCauHoiTheoMon(NodeBST *root, const char *maMH, CauHoi ds[], int toida)
{
    int count = 0;
    duyetLayCauHoi(root, maMH, ds, toida, count);
    return count;
}

void tronCauHoi(CauHoi ds[], int n)
{
    srand((unsigned)time(nullptr));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        CauHoi temp = ds[i];
        ds[i] = ds[j];
        ds[j] = temp;
    }
}

float chamDiem(CauHoi ds[], char dapAnSV[], int n)
{
    if (n <= 0)
        return 0;

    int dung = 0;
    for (int i = 0; i < n; i++)
    {
        if (toupper(dapAnSV[i]) == toupper(ds[i].dapan))
        {
            dung++;
        }
    }
    return dung * 10.0f / n;
}

void batDauThi(SinhVien *sv, NodeBST *root, const char *maMH, int soCau, int soPhut)
{
    if (sv == nullptr)
        return;

    if (timDiemThi(sv, maMH))
    {
        cout << "\nDa thi mon nay!\n";
        return;
    }

    CauHoi ds[1000];
    int tong = layCauHoiTheoMon(root, maMH, ds, 1000);

    if (tong == 0)
    {
        cout << "\nKhong co cau hoi!\n";
        return;
    }

    tronCauHoi(ds, tong);
    if (soCau > tong)
        soCau = tong;

    char dapAnSV[MAX_CAU_HOI_THI];
    // Ráº¤T QUAN TRá»ŒNG: GÃ¡n toÃ n bá»™ máº£ng thÃ nh '0' Ä‘á»ƒ trÃ¡nh dá»¯ liá»‡u rÃ¡c náº¿u háº¿t giá» giá»¯a chá»«ng
    memset(dapAnSV, '0', sizeof(dapAnSV));

    hetGio = false;
    std::thread timer(thoiGianDemNguoc, soPhut);
    // Khá»Ÿi táº¡o luá»“ng Ä‘áº¿m ngÆ°á»£c

    // cin.ignore(10000, '\n');
    int cau = 0;
    char da;
    while (!hetGio)
    {
        system("cls");
        cout << "\n==================\n";
        cout << "Nhap 'j' de quay lai cau truoc." << endl;
        cout << "Nhap 'l' de quay lai cau sau." << endl;
        cout << "Nhap 'ESC' de nop." << endl;
        cout << "Cau " << cau + 1 << endl;
        cout << ds[cau].noidung << endl;
        cout << "A. " << ds[cau].A << endl;
        cout << "B. " << ds[cau].B << endl;
        cout << "C. " << ds[cau].C << endl;
        cout << "D. " << ds[cau].D << endl;
        if (dapAnSV[cau] != '0')
            cout << "Tra loi: " << dapAnSV[cau];
        else
            cout << "Tra loi: ";

        da = getch();
        if (da == 'J')
        {
            if (cau == 0)
                cau = soCau - 1;
            else
                cau--;
        }
        if (da == 'L')
        {
            if (cau == soCau - 1)
                cau = 0;
            else
                cau++;
        }
        if (da == 'A' || da == 'B' || da == 'C' || da == 'D')
        {
            gotoxy(9, 12);

            cout << da;
            dapAnSV[cau] = da;
        }
        if (da == 13)
        {
            if (cau == soCau - 1)
                cau = 0;
            else
                cau++;
        }
        if (da == 27)
            hetGio = true;
    }

    timer.join();
    system("cls");
    if (hetGio && da == 27)
    {
        cout << "\nBan Da Nop Bai!!";
    }

    int soDung = 0;
    for (int i = 0; i < soCau; i++)
    {
        if (dapAnSV[i] == ds[i].dapan)
        {
            soDung++;
        }
    }

    float diem = chamDiem(ds, dapAnSV, soCau);
    DiemThi *dt = taoDiemThi(maMH, diem, soDung, soCau);

    dt->soPhutThi = soPhut;
    dt->thoiGianThi = time(nullptr);

    for (int i = 0; i < soCau; i++)
    {
        KetQuaBaiThi *kq = new KetQuaBaiThi;
        kq->idCauHoi = ds[i].id;
        kq->tlSinhVien = dapAnSV[i];
        kq->tlDungSai = (dapAnSV[i] == ds[i].dapan);
        kq->tiep = dt->dsKetQua;
        dt->dsKetQua = kq;
    }

    themDiemThi(sv, dt);
    cout << "\nDiem: " << diem << endl;
}

void inChiTietBaiThi(SinhVien *sv, const char *maMH, NodeBST *root)
{
    if (sv == nullptr)
        return;

    DiemThi *dt = timDiemThi(sv, maMH);

    if (dt == nullptr)
    {
        cout << "\nChua thi!\n";
        return;
    }

    KetQuaBaiThi *kq = dt->dsKetQua;

    while (kq)
    {
        NodeBST *node = timCauHoiTheoID(root, kq->idCauHoi);

        if (node)
        {
            cout << "\n------------------\n";
            cout << node->data.noidung << endl;
            cout << "SV chon: " << kq->tlSinhVien << endl;
            cout << "Dap an : " << node->data.dapan << endl;
            cout << (kq->tlDungSai ? "Dung" : "Sai") << endl;
        }

        kq = kq->tiep;
    }
}

void inBangDiemLop(Lop *lop, const char *maMH)
{
    if (lop == nullptr)
        return;

    cout << "\n==============================\n";
    cout << "MASV\tHO TEN\t\tDIEM\n";

    SinhVien *sv = lop->dsSV;

    while (sv)
    {
        cout << sv->masv << "\t" << sv->ho << " " << sv->ten << "\t";

        DiemThi *dt = timDiemThi(sv, maMH);

        if (dt)
            cout << dt->diem;
        else
            cout << "Chua thi";

        cout << endl;
        sv = sv->tiep;
    }
}

NodeBST *timCauHoiTheoID(NodeBST *root, int id)
{
    if (root == nullptr)
        return nullptr;

    if (root->data.id == id)
        return root;

    if (id < root->data.id)
        return timCauHoiTheoID(root->trai, id);

    return timCauHoiTheoID(root->phai, id);
}

void duyetLayCauHoi(NodeBST *root, const char *maMH, CauHoi ds[], int max, int &count)
{
    if (root == nullptr || count >= max)
        return;

    duyetLayCauHoi(root->trai, maMH, ds, max, count);

    if (!root->data.daXoa && strcmp(root->data.mamh, maMH) == 0)
    {
        ds[count++] = root->data;
    }

    duyetLayCauHoi(root->phai, maMH, ds, max, count);
}