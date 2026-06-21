#include <iostream>
#include <cstring>

#include "monhoc.h"
#include "../../HamHoTro/hamhotro.h"

using namespace std;

void khoiTaoDSMonHoc(
    DSMonHoc &ds)
{
    ds.n = 0;
}

MonHoc taoMonHoc(
    const char *maMH,
    const char *tenMH,
    int soCauHoiThi,
    int soPhutThi,
    int soTC)
{
    MonHoc mh;

    // validator
    if (maMH == nullptr || tenMH == nullptr)
        return mh;

    if (chuoiRong(maMH) || chuoiRong(tenMH))
        return mh;

    if (chiToanKhoangTrang(maMH) || chiToanKhoangTrang(tenMH))
        return mh;

    if (soTC <= 0)
        return mh;

    saoChepChuoi(
        mh.mamh,
        maMH);

    saoChepChuoi(
        mh.tenmh,
        tenMH);

    mh.soTinChi = soTC;
    mh.soCauHoiThi = soCauHoiThi;
    mh.soPhutThi = soPhutThi;

    mh.daXoa = 0;

    return mh;
}

MonHoc *timMonHoc(
    DSMonHoc &ds,
    const char *maMH)
{
    for (int i = 0; i < ds.n; i++)
    {
        if (ds.ds[i].daXoa)
            continue;

        if (soSanhChuoi(
                ds.ds[i].mamh,
                maMH) == 0)
        {
            return &ds.ds[i];
        }
    }

    return nullptr;
}

bool themMonHoc(
    DSMonHoc &ds,
    const MonHoc &mh)
{
    if (ds.n >= MAX_MON_HOC)
        return false;

    if (timMonHoc(ds, mh.mamh))
        return false;

    ds.ds[ds.n] = mh;

    ds.ds[ds.n].daXoa = 0;

    ds.n++;

    return true;
}
bool xoaMonHoc(
    DSMonHoc &ds,
    const char *maMH)
{
    MonHoc *mh =
        timMonHoc(
            ds,
            maMH);

    if (mh == nullptr)
        return false;

    mh->daXoa = 1;

    return true;
}
bool suaMonHoc(
    DSMonHoc &ds,
    const char *maMH,
    const MonHoc &moi)
{
    MonHoc *mh =
        timMonHoc(
            ds,
            maMH);

    if (mh == nullptr)
        return false;

    saoChepChuoi(
        mh->tenmh,
        moi.tenmh);

    mh->soTinChi =
        moi.soTinChi;

    return true;
}
void inDSMonHoc(
    const DSMonHoc &ds)
{
    cout
        << "\n===== DANH SACH MON HOC =====\n";

    cout
        << "Tong so mon: "
        << ds.n
        << "\n\n";

    cout
        << "Ma MH\tTen MH\tSo TC\tSo Cau Hoi\tSo Phut Thi\n";

    for (int i = 0; i < ds.n; i++)
    {
        if (ds.ds[i].daXoa)
            continue;

        inMotMonHoc(
            ds.ds[i]);
    }
}

// Ham ho tro in ds mon hoc
void inMotMonHoc(
    const MonHoc &mh)
{
    cout
        << mh.mamh
        << "\t";

    cout
        << mh.tenmh
        << "\t";

    cout
        << mh.soTinChi
        << "\n";
}