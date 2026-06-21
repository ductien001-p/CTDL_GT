#include "ketquabaithi.h"



KetQuaBaiThi* taoKetQua(
    int id,
    char tlSV,
    char dungSai)
{
    KetQuaBaiThi* kq =
        new KetQuaBaiThi;

    kq->idCauHoi = id;
    kq->tlSinhVien = tlSV;
    kq->tlDungSai = dungSai;
    kq->tiep = nullptr;

    return kq;
}

void themKetQua(
    DiemThi* dt,
    KetQuaBaiThi* kq)
{
    if(dt == nullptr ||
       kq == nullptr)
    {
        return;
    }

    if(dt->dsKetQua == nullptr)
    {
        dt->dsKetQua = kq;
        return;
    }

    KetQuaBaiThi* p =
        dt->dsKetQua;

    while(p->tiep)
    {
        p = p->tiep;
    }

    p->tiep = kq;
}