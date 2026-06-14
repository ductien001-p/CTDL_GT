#ifndef DIEMTHI_H
#define DIEMTHI_H

#include "../../struct/struct.h"
#include "../../HamHoTro/hamhotro.h"
#include "../../features/SinhVien/sinhvien.h"

DiemThi *taoDiemThi(
    const char *maMH,
    float diem,
    int soDung,
    int tongCau);

void themDiemThi(
    SinhVien *sv,
    DiemThi *dt);

DiemThi *timDiemThi(
    SinhVien *sv,
    const char *maMH);

// Ham ho tro chen diem thi de load diem thi tu file
void chenDiemThiVaoCuoiDSLK(
    DiemThi *&head,
    DiemThi *dt);

void giaiPhongKetQua(
    KetQuaBaiThi *head);

void giaiPhongDiemThi(
    DiemThi *head);

void inMotDiemThi(
    const DiemThi *dt);

#endif