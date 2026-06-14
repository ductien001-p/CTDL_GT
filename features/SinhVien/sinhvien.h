#ifndef SINHVIEN_H
#define SINHVIEN_H

#include "../../struct/struct.h"

SinhVien* taoSinhVien(
    const char* masv,
    const char* ho,
    const char* ten,
    int phai,
    const char* pass);

bool themSinhVien(
    Lop* lop,
    SinhVien* sv);

SinhVien* timSinhVien(
    DSLop& dsLop,
    const char* masv);

bool xoaSinhVien(
    Lop* lop,
    const char* masv);

void inDSSinhVien(
    const Lop* lop);

//Ham ho tro cho load sinh vien tu file
void chenSinhVienVaoCuoiDSLK(
    SinhVien*& head,
    SinhVien* sv);

void giaiPhongDiemThi(
    DiemThi* head);

void inMotSinhVien(
    const SinhVien* sv);

#endif