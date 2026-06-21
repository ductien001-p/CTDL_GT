#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include "fileio.h"
#include "../features/Lop/lop.h"
#include "../features/MonHoc/monhoc.h"
#include "../features/SinhVien/sinhvien.h"
#include "../features/DiemThi/diemthi.h"
#include "../features/CauHoi/cauhoi.h"
#include "../HamHoTro/hamhotro.h"
#include "../struct/app_context.h"
#include "../struct/struct.h"
#include <limits>
#include <iostream>
using namespace std;

void saveMonHoc(const DSMonHoc &ds)
{
    ofstream out("data/monhoc.txt");

    for (int i = 0; i < ds.n; i++)
    {
        const MonHoc &mh = ds.ds[i];

        out << mh.mamh << "|"
            << mh.tenmh << "|"
            << mh.soTinChi << "|"
            << mh.daXoa
            << "\n";
    }
}
void loadMonHoc(DSMonHoc &ds)
{
    ifstream in("data/monhoc.txt");

    ds.n = 0;

    while (!in.eof())
    {
        MonHoc mh;

        in.getline(mh.mamh, LEN_MAMH, '|');
        if (in.eof())
            break;

        in.getline(mh.tenmh, LEN_TENMH, '|');
        in >> mh.soTinChi;
        in.ignore();
        in >> mh.daXoa;
        in.ignore();

        ds.ds[ds.n++] = mh;
    }
}
void saveLop(const DSLop &ds)
{
    ofstream out("data/lop.txt");

    for (int i = 0; i < ds.n; i++)
    {
        Lop *l = ds.ds[i];

        out << l->malop << "|"
            << l->tenlop << "|"
            << l->soSV << "\n";
    }
}
void loadLop(DSLop &ds)
{
    ifstream in("data/lop.txt");

    ds.n = 0;

    while (true)
    {
        Lop *l = new Lop;

        if (!in.getline(l->malop, LEN_MALOP, '|'))
        {
            delete l;
            break;
        }

        in.getline(l->tenlop, LEN_TENLOP, '|');
        in >> l->soSV;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        l->dsSV = nullptr;

        ds.ds[ds.n++] = l;
    }
}
void saveSinhVien(const DSLop &dsLop)
{
    ofstream out("data/sinhvien.txt");

    for (int i = 0; i < dsLop.n; i++)
    {
        Lop *lop = dsLop.ds[i];

        SinhVien *sv = lop->dsSV;

        while (sv)
        {
            out << lop->malop << "|"
                << sv->masv << "|"
                << sv->ho << "|"
                << sv->ten << "|"
                << sv->phai << "|"
                << sv->password << "\n";

            sv = sv->tiep;
        }
    }
}
void loadSinhVien(
    DSLop &dsLop)
{
    ifstream in(
        "data/sinhvien.txt");

    string line;

    while (getline(in, line))
    {
        stringstream ss(line);

        char maLop[LEN_MALOP];
        char maSV[LEN_MASV];
        char ho[LEN_HO];
        char ten[LEN_TEN];
        char phai[2];
        char pass[LEN_PASS];

        ss.getline(maLop, LEN_MALOP, '|');
        ss.getline(maSV, LEN_MASV, '|');
        ss.getline(ho, LEN_HO, '|');
        ss.getline(ten, LEN_TEN, '|');
        ss.getline(phai, 2, '|');
        ss.getline(pass, LEN_PASS);

        Lop *lop =
            timLop(dsLop, maLop);

        if (lop == nullptr)
            continue;

        SinhVien *sv =
            new SinhVien;

        strcpy(sv->masv, maSV);
        strcpy(sv->ho, ho);
        strcpy(sv->ten, ten);
        sv->phai = atoi(phai);
        strcpy(sv->password, pass);

        sv->dsDiem = nullptr;
        sv->tiep = nullptr;

        chenSinhVienVaoCuoiDSLK(
            lop->dsSV,
            sv);
    }
}

void saveDiemThi(const DSLop &dsLop)
{
    ofstream out("data/diemthi.txt");

    for (int i = 0; i < dsLop.n; i++)
    {
        Lop *lop = dsLop.ds[i];

        SinhVien *sv = lop->dsSV;

        while (sv)
        {
            DiemThi *dt = sv->dsDiem;

            while (dt)
            {
                out << sv->masv << "|"
                    << dt->mamh << "|"
                    << dt->diem << "|"
                    << dt->soCauDung << "|"
                    << dt->tongCau << "|"
                    << dt->soPhutThi << "|"
                    << dt->thoiGianThi
                    << "\n";

                dt = dt->tiep;
            }

            sv = sv->tiep;
        }
    }
}
void loadDiemThi(
    DSLop &dsLop)
{
    ifstream in(
        "data/diemthi.txt");

    string line;

    while (getline(in, line))
    {
        stringstream ss(line);

        string maSV;
        string maMH;
        string diemStr;

        getline(ss, maSV, '|');
        getline(ss, maMH, '|');
        getline(ss, diemStr);

        SinhVien *sv =
            timSinhVien(
                dsLop,
                maSV.c_str());

        if (sv == nullptr)
            continue;

        DiemThi *dt =
            new DiemThi;

        strcpy(dt->mamh, maMH.c_str());

        dt->diem =
            stof(diemStr);

        dt->dsKetQua = nullptr;
        dt->tiep = nullptr;

        themDiemThi(
            sv,
            dt);
    }
}
void saveNode(NodeBST *root,
              ofstream &out)
{
    if (root == nullptr)
        return;

    saveNode(root->trai, out);

    CauHoi &ch = root->data;

    out
        << ch.id << '|'
        << ch.mamh << '|'
        << ch.noidung << '|'
        << ch.A << '|'
        << ch.B << '|'
        << ch.C << '|'
        << ch.D << '|'
        << ch.dapan << '|'
        << ch.daXoa
        << '\n';

    saveNode(root->phai, out);
}
void saveCauHoi(NodeBST *root)
{
    ofstream out("data/cauhoi.txt");

    saveNode(root, out);
}
void loadCauHoi(NodeBST *&root)
{
    root = nullptr;

    std::ifstream in("data/cauhoi.txt");

    if (!in.is_open())
        return;

    while (true)
    {
        CauHoi ch;

        // đọc id trước
        if (!(in >> ch.id))
            break;

        in.ignore(); // bỏ '|'

        in.getline(ch.mamh, LEN_MAMH, '|');
        in.getline(ch.noidung, LEN_NOIDUNG, '|');
        in.getline(ch.A, LEN_LUACHON, '|');
        in.getline(ch.B, LEN_LUACHON, '|');
        in.getline(ch.C, LEN_LUACHON, '|');
        in.getline(ch.D, LEN_LUACHON, '|');

        in >>
            ch.dapan;
        in.ignore(); // bỏ '|'

        in >> ch.daXoa;

        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        chenCauHoiLoadfile(root, ch);
    }

    in.close();
}

void loadChiTietBaiThi(
    DSLop &dsLop)
{
    std::ifstream in(
        "data/chitietthi.txt");

    if (!in)
        return;

    std::string line;

    while (std::getline(
        in,
        line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(
            line);

        std::string masv;
        std::string mamh;
        std::string sid;
        std::string tl;
        std::string dungSai;

        std::getline(
            ss,
            masv,
            '|');

        std::getline(
            ss,
            mamh,
            '|');

        std::getline(
            ss,
            sid,
            '|');

        std::getline(
            ss,
            tl,
            '|');

        std::getline(
            ss,
            dungSai,
            '|');

        DiemThi *dt =
            timDiemThiTheoMaSV(
                dsLop,
                masv.c_str(),
                mamh.c_str());

        if (dt == nullptr)
            continue;

        KetQuaBaiThi *kq =
            new KetQuaBaiThi;

        kq->idCauHoi =
            atoi(
                sid.c_str());

        kq->tlSinhVien =
            tl.empty()
                ? '\0'
                : tl[0];

        kq->tlDungSai =
            atoi(
                dungSai.c_str());

        kq->tiep =
            nullptr;

        if (dt->dsKetQua ==
            nullptr)
        {
            dt->dsKetQua =
                kq;
        }
        else
        {
            KetQuaBaiThi *p =
                dt->dsKetQua;

            while (p->tiep)
                p = p->tiep;

            p->tiep = kq;
        }
    }

    in.close();
}

#include <fstream>

void saveChiTietBaiThi(
    const DSLop &dsLop)
{
    std::ofstream out(
        "data/chitietthi.txt");

    if (!out)
        return;

    for (int i = 0;
         i < dsLop.n;
         i++)
    {
        Lop *lop =
            dsLop.ds[i];

        SinhVien *sv =
            lop->dsSV;

        while (sv)
        {
            DiemThi *dt =
                sv->dsDiem;

            while (dt)
            {
                KetQuaBaiThi *kq =
                    dt->dsKetQua;

                while (kq)
                {
                    out
                        << sv->masv
                        << '|'
                        << dt->mamh
                        << '|'
                        << kq->idCauHoi
                        << '|'
                        << kq->tlSinhVien
                        << '|'
                        << (int)kq->tlDungSai
                        << '\n';

                    kq =
                        kq->tiep;
                }

                dt =
                    dt->tiep;
            }

            sv =
                sv->tiep;
        }
    }

    out.close();
}

void loadDatabase(AppContext &app)
{
    loadLop(app.db.dsLop);

    loadMonHoc(app.db.dsMH);

    loadSinhVien(app.db.dsLop);

    loadDiemThi(app.db.dsLop);

    loadChiTietBaiThi(app.db.dsLop);

    loadCauHoi(app.db.rootCH);
}
void saveDatabase(const AppContext &app)
{
    saveLop(app.db.dsLop);

    saveMonHoc(app.db.dsMH);

    saveSinhVien(app.db.dsLop);

    saveDiemThi(app.db.dsLop);

    saveChiTietBaiThi(app.db.dsLop);

    saveCauHoi(app.db.rootCH);
}