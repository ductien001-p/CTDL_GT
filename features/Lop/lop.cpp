#include <iostream>
#include <cstring>

#include "lop.h"
#include "../../HamHoTro/hamhotro.h"

using namespace std;

void khoiTaoDSLop(
    DSLop &ds)
{
    ds.n = 0;

    for (int i = 0; i < MAX_LOP; i++)
    {
        ds.ds[i] = nullptr;
    }
}

Lop *timLop(
    DSLop &ds,
    const char maLop[])
{
    for (int i = 0; i < ds.n; i++)
    {
        if (ds.ds[i] == nullptr)
            continue;

        if (soSanhChuoi(ds.ds[i]->malop, maLop))
            return ds.ds[i];
    }

    return nullptr;
}
bool themLop(
    DSLop &ds,
    const char maLop[],
    const char tenLop[])
{
    if (ds.n >= MAX_LOP)
        return false;

    if (timLop(ds, maLop) != nullptr)
        return false;

    Lop *lop = new Lop;

    saoChepChuoi(lop->malop, maLop);
    saoChepChuoi(lop->tenlop, tenLop);

    lop->soSV = 0;
    lop->dsSV = nullptr;

    ds.ds[ds.n] = lop;
    ds.n++;

    return true;
}
bool xoaLop(
    DSLop &ds,
    const char maLop[])
{
    int viTri = -1;

    for (int i = 0; i < ds.n; i++)
    {
        if (soSanhChuoi(ds.ds[i]->malop, maLop))
        {
            viTri = i;
            break;
        }
    }

    if (viTri == -1)
        return false;

    giaiPhongDSSV(ds.ds[viTri]->dsSV);

    delete ds.ds[viTri];

    for (int i = viTri; i < ds.n - 1; i++)
    {
        ds.ds[i] = ds.ds[i + 1];
    }

    ds.ds[ds.n - 1] = nullptr;

    ds.n--;

    return true;
}
void inDSLop(
    const DSLop &ds)
{
    if (ds.n == 0)
    {
        cout << "Danh sach lop rong!\n";
        return;
    }

    cout << "\n===== DANH SACH LOP =====\n";

    cout << "So lop: " << ds.n << "\n\n";

    for (int i = 0; i < ds.n; i++)
    {
        cout << "Ma lop  : "
             << ds.ds[i]->malop
             << "\n";

        cout << "Ten lop : "
             << ds.ds[i]->tenlop
             << "\n";

        cout << "So SV   : "
             << ds.ds[i]->soSV
             << "\n";

        cout << "-------------------------\n";
    }
}

// Ham ho tro giai phong danh sach sinh vien khi xoa lop
void giaiPhongDSSV(
    SinhVien *head)
{
    while (head)
    {
        SinhVien *temp = head;
        head = head->tiep;

        delete temp;
    }
}