#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include "../../struct/struct.h"
#include "diemthi.h"
#include "../../HamHoTro/hamhotro.h"
using namespace std;
DiemThi *taoDiemThi(
    const char *maMH,
    float diem,
    int soDung,
    int tongCau)
{
    DiemThi *dt = new DiemThi;

    saoChepChuoi(dt->mamh, maMH);

    dt->diem = diem;

    dt->soCauDung = soDung;
    dt->tongCau = tongCau;

    dt->soPhutThi = 0;

    dt->thoiGianThi = time(nullptr);

    dt->dsKetQua = nullptr;

    dt->tiep = nullptr;

    return dt;
}
DiemThi *timDiemThi(
    SinhVien *sv,
    const char *maMH)
{
    if (sv == nullptr)
        return nullptr;

    DiemThi *p = sv->dsDiem;

    while (p)
    {
        if (strcmp(p->mamh, maMH) == 0)
            return p;

        p = p->tiep;
    }

    return nullptr;
}

DiemThi *timDiemThiTheoMaSV(
    DSLop &dsLop,
    const char *masv,
    const char *maMH)
{
    for (int i = 0; i < dsLop.n; i++)
    {
        SinhVien *sv =
            timSinhVien(
                dsLop,
                masv);

        if (sv == nullptr)
            continue;

        DiemThi *dt =
            timDiemThi(
                sv,
                maMH);

        if (dt)
            return dt;
    }

    return nullptr;
}

void themDiemThi(
    SinhVien *sv,
    DiemThi *dt)
{
    if (sv == nullptr || dt == nullptr)
        return;

    if (timDiemThi(
            sv,
            dt->mamh))
    {
        return;
    }

    if (sv->dsDiem == nullptr)
    {
        sv->dsDiem = dt;
        return;
    }

    DiemThi *p = sv->dsDiem;

    while (p->tiep)
    {
        p = p->tiep;
    }

    p->tiep = dt;
}
bool capNhatDiemThi(
    SinhVien *sv,
    const char *maMH,
    float diemMoi)
{
    DiemThi *dt =
        timDiemThi(
            sv,
            maMH);

    if (dt == nullptr)
        return false;

    dt->diem = diemMoi;

    return true;
}
void inDSDiemThi(
    const SinhVien *sv)
{
    if (sv == nullptr)
        return;

    cout
        << "\n===== BANG DIEM =====\n";

    cout
        << sv->masv
        << " - "
        << sv->ho
        << " "
        << sv->ten
        << "\n\n";

    DiemThi *p = sv->dsDiem;

    while (p)
    {
        inMotDiemThi(p);

        p = p->tiep;
    }
}
void giaiPhongDiemThi(
    DiemThi *head)
{
    while (head)
    {
        DiemThi *temp = head;

        head = head->tiep;

        giaiPhongKetQua(
            temp->dsKetQua);

        delete temp;
    }
}
float tinhDiem(
    int soDung,
    int tongCau)
{
    if (tongCau == 0)
        return 0;

    return (float)soDung * 10.0f / tongCau;
}

void chenDiemThiVaoCuoiDSLK(
    DiemThi *&head,
    DiemThi *p)
{
    if (head == nullptr)
    {
        head = p;
        return;
    }

    DiemThi *q = head;

    while (q->tiep)
        q = q->tiep;

    q->tiep = p;
}

// Ham in chi tiet mot diem thi
void inMotDiemThi(
    const DiemThi *dt)
{
    cout
        << "Mon hoc     : "
        << dt->mamh
        << "\n";

    cout
        << "So cau dung : "
        << dt->soCauDung
        << "/"
        << dt->tongCau
        << "\n";

    cout
        << "Diem        : "
        << dt->diem
        << "\n";

    cout
        << "------------------\n";
}
// Ham ho tro giai phong danh sach ket qua bai thi
void giaiPhongKetQua(
    KetQuaBaiThi *head)
{
    while (head)
    {
        KetQuaBaiThi *temp = head;

        head = head->tiep;

        delete temp;
    }
}