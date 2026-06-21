#include <iostream>
#include <cstring>

#include "sinhvien.h"
#include "../DiemThi/diemthi.h"
#include "../../HamHoTro/hamhotro.h"

using namespace std;

SinhVien *taoSinhVien(
    const char *masv,
    const char *ho,
    const char *ten,
    int phai,
    const char *pass)
{
    SinhVien *sv = new SinhVien;

    if (masv[0] == '\0' || ho[0] == '\0' || ten[0] == '\0' || (phai < 0) || phai > 1 || pass[0] == '\0')
    {
        return nullptr;
    }

    saoChepChuoi(sv->masv, masv);
    saoChepChuoi(sv->ho, ho);
    saoChepChuoi(sv->ten, ten);

    sv->phai = phai;

    saoChepChuoi(sv->password, pass);

    sv->dsDiem = nullptr;
    sv->tiep = nullptr;

    return sv;
}

SinhVien *timSinhVien(
    DSLop &dsLop,
    const char *masv)
{
    for (int i = 0; i < dsLop.n; i++)
    {
        SinhVien *p = dsLop.ds[i]->dsSV;

        while (p != nullptr)
        {
            if (soSanhChuoi(p->masv, masv))
                return p;

            p = p->tiep;
        }
    }

    return nullptr;
}

bool themSinhVien(
    Lop *lop,
    SinhVien *sv)
{
    if (lop == nullptr || sv == nullptr)
    {
        cout << "nullptr";
        return false;
    }

    SinhVien *p = lop->dsSV;

    while (p)
    {
        if (soSanhChuoi(p->masv, sv->masv))
        {
            cout << "trung masv";
            return false;
        }

        p = p->tiep;
    }

    if (lop->dsSV == nullptr)
    {
        lop->dsSV = sv;
    }
    else
    {
        SinhVien *last = lop->dsSV;

        while (last->tiep)
            last = last->tiep;

        last->tiep = sv;
    }

    lop->soSV++;

    return true;
}

bool xoaSinhVien(
    Lop *lop,
    const char *masv)
{
    if (lop == nullptr)
        return false;

    SinhVien *truoc = nullptr;
    SinhVien *hienTai = lop->dsSV;

    while (hienTai)
    {
        if (soSanhChuoi(hienTai->masv, masv) == 0)
        {
            if (truoc == nullptr)
            {
                lop->dsSV = hienTai->tiep;
            }
            else
            {
                truoc->tiep = hienTai->tiep;
            }

            giaiPhongDiemThi(
                hienTai->dsDiem);

            delete hienTai;

            lop->soSV--;

            return true;
        }

        truoc = hienTai;
        hienTai = hienTai->tiep;
    }

    return false;
}

void inDSSinhVien(
    const Lop *lop)
{
    if (lop == nullptr)
        return;

    cout << "\n===== DANH SACH SINH VIEN =====\n";

    cout << "Ma lop  : "
         << lop->malop
         << "\n";

    cout << "Ten lop : "
         << lop->tenlop
         << "\n";

    cout << "So SV   : "
         << lop->soSV
         << "\n\n";

    SinhVien *p = lop->dsSV;

    while (p)
    {
        inMotSinhVien(p);

        p = p->tiep;
    }
}

void chenSinhVienVaoCuoiDSLK(
    SinhVien *&head,
    SinhVien *sv)
{
    if (head == nullptr)
    {
        head = sv;
        return;
    }

    SinhVien *p = head;

    while (p->tiep)
        p = p->tiep;

    p->tiep = sv;
}
// Ham ho tro in ds sinh vien
void inMotSinhVien(
    const SinhVien *sv)
{
    cout << "MASV : "
         << sv->masv
         << "\n";

    cout << "HO   : "
         << sv->ho
         << "\n";

    cout << "TEN  : "
         << sv->ten
         << "\n";

    cout << "PHAI : "
         << (sv->phai == PHAI_NAM
                 ? "Nam"
                 : "Nu")
         << "\n";

    cout << "------------------\n";
}