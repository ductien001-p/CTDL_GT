#ifndef THI_H
#define THI_H

#include "../../struct/struct.h"
// Lay ngau nhien n cau hoi theo mon
int layCauHoiTheoMon(
    NodeBST *root,
    const char *maMH,
    CauHoi ds[],
    int max);
// Tron ngau nhien n cau hoi
void tronCauHoi(
    CauHoi ds[],
    int n);

void batDauThi(
    SinhVien *sv,
    NodeBST *root,
    const char *maMH,
    int soCau,
    int soPhut);

float chamDiem(
    CauHoi ds[],
    char dapAnSV[],
    int n);

void inChiTietBaiThi(
    SinhVien *sv,
    const char *maMH,
    NodeBST *root);
void inBangDiemLop(
    Lop *lop,
    const char *maMH);

// Ham ho tro
NodeBST *timCauHoiTheoID(
    NodeBST *root,
    int id);
void duyetLayCauHoi(
    NodeBST *root,
    const char *maMH,
    CauHoi ds[],
    int max,
    int &count);
#endif