#ifndef LOP_H
#define LOP_H

#include "../../struct/struct.h"

void khoiTaoDSLop(
    DSLop &ds);

bool themLop(
    DSLop &ds,
    const char *maLop,
    const char *tenLop);

Lop *timLop(
    DSLop &ds,
    const char *maLop);

bool xoaLop(
    DSLop &ds,
    const char *maLop);

void inDSLop(
    const DSLop &ds);

void giaiPhongDSSV(
    SinhVien *head);

#endif