#ifndef CAUHOI_H
#define CAUHOI_H
#include "../../struct/struct.h"
#include <fstream>
using namespace std;

NodeBST *taoNode(
    const CauHoi &ch);
bool themCauHoi(
    NodeBST *&root,
    const CauHoi &ch);
NodeBST *timkiemCauHoi(
    NodeBST *root,
    int id);
bool xoaCauHoi(
    NodeBST *&root,
    int id);
void LNR(
    NodeBST *root);

void luuLNR(
    NodeBST *root,
    ofstream &out);
int layIDMax(
    NodeBST *root);

int taoIDMoi(
    NodeBST *root);
void inCauHoiTheoMon(
    NodeBST *root,
    const char *maMH);
int demCauHoiTheoMon(
    NodeBST *root,
    const char *maMH);

void chenCauHoiLoadfile(
    NodeBST *&root,
    const CauHoi &ch);
// Ham ho tro
void timNodeTheMang(
    NodeBST *&x,
    NodeBST *&y);
#endif // CAUHOI_H