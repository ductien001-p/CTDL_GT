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
#include <ctime>
#include "../struct/struct.h"

using namespace std;

int layCauHoiTheoMon(
    NodeBST *root,
    const char *maMH,
    CauHoi ds[],
    int toida)
{
    int count = 0;

    duyetLayCauHoi(
        root,
        maMH,
        ds,
        toida,
        count);

    return count;
}

void tronCauHoi(
    CauHoi ds[],
    int n)
{
    srand((unsigned)time(nullptr));

    for (int i = n - 1;
         i > 0;
         i--)
    {
        int j =
            rand() % (i + 1);

        CauHoi temp =
            ds[i];

        ds[i] =
            ds[j];

        ds[j] =
            temp;
    }
}

float chamDiem(
    CauHoi ds[],
    char dapAnSV[],
    int n)
{
    if (n <= 0)
        return 0;

    int dung = 0;

    for (int i = 0;
         i < n;
         i++)
    {
        if (toupper(dapAnSV[i]) ==
            toupper(ds[i].dapan))
        {
            dung++;
        }
    }

    return dung * 10.0f / n;
}

void batDauThi(
    SinhVien *sv,
    NodeBST *root,
    const char *maMH,
    int soCau,
    int soPhut)
{
    if (sv == nullptr)
        return;

    if (timDiemThi(
            sv,
            maMH))
    {
        cout
            << "\nDa thi mon nay!\n";

        return;
    }

    CauHoi ds[1000];

    int tong =
        layCauHoiTheoMon(
            root,
            maMH,
            ds,
            1000);

    if (tong == 0)
    {
        cout
            << "\nKhong co cau hoi!\n";

        return;
    }

    tronCauHoi(
        ds,
        tong);

    if (soCau > tong)
        soCau = tong;

    char dapAnSV[MAX_CAU_HOI_THI];

    for (int i = 0;
         i < soCau;
         i++)
    {
        cout
            << "\n==================\n";

        cout
            << "Cau "
            << i + 1
            << endl;

        cout
            << ds[i].noidung
            << endl;

        cout
            << "A. "
            << ds[i].A
            << endl;

        cout
            << "B. "
            << ds[i].B
            << endl;

        cout
            << "C. "
            << ds[i].C
            << endl;

        cout
            << "D. "
            << ds[i].D
            << endl;

        cout
            << "Tra loi: ";

        char dapAn[1];
        nhap(dapAn, DAPAN);
        dapAnSV[i] = dapAn[0];

        dapAnSV[i] =
            toupper(
                dapAnSV[i]);
    }

    int soDung = 0;

    for (int i = 0;
         i < soCau;
         i++)
    {
        if (dapAnSV[i] ==
            ds[i].dapan)
        {
            soDung++;
        }
    }

    float diem =
        chamDiem(
            ds,
            dapAnSV,
            soCau);

    DiemThi *dt =
        taoDiemThi(
            maMH,
            diem,
            soDung,
            soCau);

    dt->soPhutThi =
        soPhut;

    dt->thoiGianThi =
        time(nullptr);

    for (int i = 0;
         i < soCau;
         i++)
    {
        KetQuaBaiThi *kq =
            new KetQuaBaiThi;

        kq->idCauHoi =
            ds[i].id;

        kq->tlSinhVien =
            dapAnSV[i];

        kq->tlDungSai =
            (dapAnSV[i] ==
             ds[i].dapan);

        kq->tiep =
            dt->dsKetQua;

        dt->dsKetQua =
            kq;
    }

    themDiemThi(
        sv,
        dt);

    cout
        << "\nDiem: "
        << diem
        << endl;
}

void inChiTietBaiThi(
    SinhVien *sv,
    const char *maMH,
    NodeBST *root)
{
    if (sv == nullptr)
        return;

    DiemThi *dt =
        timDiemThi(
            sv,
            maMH);

    if (dt == nullptr)
    {
        cout
            << "\nChua thi!\n";

        return;
    }

    KetQuaBaiThi *kq =
        dt->dsKetQua;

    while (kq)
    {
        NodeBST *node =
            timCauHoiTheoID(
                root,
                kq->idCauHoi);

        if (node)
        {
            cout
                << "\n------------------\n";

            cout
                << node->data.noidung
                << endl;

            cout
                << "SV chon: "
                << kq->tlSinhVien
                << endl;

            cout
                << "Dap an : "
                << node->data.dapan
                << endl;

            cout
                << (kq->tlDungSai
                        ? "Dung"
                        : "Sai")
                << endl;
        }

        kq =
            kq->tiep;
    }
}

void inBangDiemLop(
    Lop *lop,
    const char *maMH)
{
    if (lop == nullptr)
        return;

    cout
        << "\n==============================\n";

    cout
        << "MASV\tHO TEN\t\tDIEM\n";

    SinhVien *sv =
        lop->dsSV;

    while (sv)
    {
        cout
            << sv->masv
            << "\t"
            << sv->ho
            << " "
            << sv->ten
            << "\t";

        DiemThi *dt =
            timDiemThi(
                sv,
                maMH);

        if (dt)
            cout
                << dt->diem;
        else
            cout
                << "Chua thi";

        cout
            << endl;

        sv =
            sv->tiep;
    }
}

NodeBST *timCauHoiTheoID(
    NodeBST *root,
    int id)
{
    if (root == nullptr)
        return nullptr;

    if (root->data.id == id)
        return root;

    if (id < root->data.id)
        return timCauHoiTheoID(
            root->trai,
            id);

    return timCauHoiTheoID(
        root->phai,
        id);
}

void duyetLayCauHoi(
    NodeBST *root,
    const char *maMH,
    CauHoi ds[],
    int max,
    int &count)
{
    if (root == nullptr ||
        count >= max)
        return;

    duyetLayCauHoi(
        root->trai,
        maMH,
        ds,
        max,
        count);

    if (root->data.daXoa == 0 &&
        strcmp(
            root->data.mamh,
            maMH) == 0)
    {
        ds[count++] =
            root->data;
    }

    duyetLayCauHoi(
        root->phai,
        maMH,
        ds,
        max,
        count);
}