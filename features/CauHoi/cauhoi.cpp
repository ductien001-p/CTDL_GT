#include "cauhoi.h"
#include "../../HamHoTro/hamhotro.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "../../struct/app_context.h"
#include "../struct/struct.h"
#include <iomanip>
#include <conio.h>
#include "decoration/decoration.h"
using namespace std;
bool themCauHoi(
    NodeBST *&root,
    const CauHoi &ch)
{
    if (root == nullptr)
    {
        root = taoNode(ch);
        return true;
    }

    if (ch.id < root->data.id)
    {
        return themCauHoi(
            root->trai,
            ch);
    }

    if (ch.id > root->data.id)
    {
        return themCauHoi(
            root->phai,
            ch);
    }

    return false;
}

NodeBST *timkiemCauHoi(
    NodeBST *root,
    int id)
{
    if (root == nullptr)
        return nullptr;

    if (id == root->data.id)
        return root;

    if (id < root->data.id)
    {
        return timkiemCauHoi(
            root->trai,
            id);
    }

    return timkiemCauHoi(
        root->phai,
        id);
}

bool xoaCauHoi(
    NodeBST *&root,
    int id)
{
    if (root == nullptr)
        return false;

    if (id < root->data.id)
    {
        return xoaCauHoi(
            root->trai,
            id);
    }

    if (id > root->data.id)
    {
        return xoaCauHoi(
            root->phai,
            id);
    }

    NodeBST *p = root;

    if (root->trai == nullptr)
    {
        root = root->phai;
    }
    else if (root->phai == nullptr)
    {
        root = root->trai;
    }
    else
    {
        NodeBST *q =
            root->phai;

        timNodeTheMang(
            p,
            q);
    }

    delete p;

    return true;
}
void luuLNR(
    NodeBST *root,
    ofstream &out)
{
    if (root == nullptr)
        return;

    luuLNR(
        root->trai,
        out);

    out
        << root->data.id << '|'
        << root->data.mamh << '|'
        << root->data.noidung << '|'
        << root->data.A << '|'
        << root->data.B << '|'
        << root->data.C << '|'
        << root->data.D << '|'
        << root->data.dapan << '|'
        << root->data.daXoa
        << '\n';

    luuLNR(
        root->phai,
        out);
}
int layIDMax(
    NodeBST *root)
{
    if (root == nullptr)
        return 0;

    while (root->phai)
    {
        root =
            root->phai;
    }

    return root->data.id;
}
int taoIDMoi(
    NodeBST *root)
{
    return layIDMax(root) + 1;
}

void hienThiCauHoiTheoMon(
    NodeBST *root,
    const char *maMH,
    int &y,
    int &dem)
{

    if (root == nullptr)
        return;

    hienThiCauHoiTheoMon(
        root->trai,
        maMH,
        y,
        dem);

    if (
        strcmp(
            root->data.mamh,
            maMH) == 0 &&
        root->data.daXoa == 0)
    {

        // neu het khung thi dung lai

        if (y >= 22)
        {
            gotoXY(5, 24);

            cout
                << "Nhan phim bat ky de xem tiep...";

            _getch();

            clearScreen();

            veKhungManHinh(
                2,
                1,
                120,
                28,
                "DANH SACH CAU HOI");

            y = 5;
        }

        CauHoi &ch =
            root->data;

        gotoXY(5, y++);

        cout
            << "ID: "
            << ch.id
            << "   Mon: "
            << ch.mamh;

        gotoXY(5, y++);

        cout
            << "Cau hoi: "
            << ch.noidung;

        gotoXY(8, y++);

        cout
            << "A. "
            << ch.A;

        gotoXY(8, y++);

        cout
            << "B. "
            << ch.B;

        gotoXY(8, y++);

        cout
            << "C. "
            << ch.C;

        gotoXY(8, y++);

        cout
            << "D. "
            << ch.D;

        gotoXY(8, y++);

        setColor(10);

        cout
            << "Dap an dung: "
            << ch.dapan;

        setColor(7);

        y += 1;

        dem++;
    }

    hienThiCauHoiTheoMon(
        root->phai,
        maMH,
        y,
        dem);
}
int demCauHoiTheoMon(
    NodeBST *root,
    const char *maMH)
{
    if (root == nullptr)
        return 0;

    int dem = 0;

    if (strcmp(
            root->data.mamh,
            maMH) == 0 &&
        root->data.daXoa == 0)
    {
        dem = 1;
    }

    return dem + demCauHoiTheoMon(root->trai, maMH) + demCauHoiTheoMon(root->phai, maMH);
}

// Ham ho tro
void LNR(
    NodeBST *root)
{
    if (root == nullptr)
        return;

    LNR(root->trai);

    cout
        << "ID: "
        << root->data.id
        << endl;

    cout
        << "Mon: "
        << root->data.mamh
        << endl;

    cout
        << root->data.noidung
        << endl;

    cout
        << "-----------------\n";

    LNR(root->phai);
}
void timNodeTheMang(
    NodeBST *&x,
    NodeBST *&y)
{
    if (y->trai)
    {
        timNodeTheMang(
            x,
            y->trai);
    }
    else
    {
        x->data = y->data;

        x = y;

        y = y->phai;
    }
}

NodeBST *taoNode(
    const CauHoi &ch)
{
    NodeBST *p =
        new NodeBST;

    p->data = ch;
    p->trai = nullptr;
    p->phai = nullptr;

    return p;
}
void chenCauHoiLoadfile(
    NodeBST *&root,
    const CauHoi &ch)
{
    if (root == nullptr)
    {
        root = new NodeBST;
        root->data = ch;
        root->trai = root->phai = nullptr;
        return;
    }

    if (ch.id < root->data.id)
        chenCauHoiLoadfile(root->trai, ch);
    else
        chenCauHoiLoadfile(root->phai, ch);
}
